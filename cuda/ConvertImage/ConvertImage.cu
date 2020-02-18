#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <iostream>

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

__global__
void GrayscaleKernel(
  uchar* img_src,
  uchar* img_dst,
	const int width,
	const int height
) {
  const int i = blockIdx.x * blockDim.x + threadIdx.x;
  const int x = i % width;
  const int y = i / width;

  const int img_pos = x * 3 + y * 3 * width;
  const uchar img_gs = (img_src[img_pos + 0] + img_src[img_pos + 1] + img_src[img_pos + 2]) / 3;
  img_dst[img_pos + 0] = img_gs;
  img_dst[img_pos + 1] = img_gs;
  img_dst[img_pos + 2] = img_gs;
}

__global__
void CopyKernel(
  uchar* img_src,
  uchar* img_dst,
	const int width,
	const int height
) {
  const int i = blockIdx.x * blockDim.x + threadIdx.x;
  const int x = i % width;
  const int y = i / width;

  const int img_pos = x * 3 + y * 3 * width;
  img_dst[img_pos + 0] = img_src[img_pos + 0];
  img_dst[img_pos + 1] = img_src[img_pos + 1];
  img_dst[img_pos + 2] = img_src[img_pos + 2];
}

int main() {
	rs2::config cfg;
	const int width = 640;
	const int height = 480;
	const int array_size = width * height;
	cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_BGR8, 30);

	rs2::pipeline pipe;
	pipe.start(cfg);

	cv::Mat color(cv::Size(width, height), CV_8UC3);
	// cv::Mat color = cv::imread("../exit.png");
	
	cv::Size size = color.size();

	cv::Mat img_result(size, CV_8UC3);

	uchar *img_color_device;
	cudaMalloc(&img_color_device, array_size * 3 * sizeof(uchar));

	uchar *img_result_device;
	cudaMalloc(&img_result_device, array_size * 3 * sizeof(uchar));

	const int thread = 128;
	const int block = (size.width * size.height) / thread;

	while (cv::waitKey(1) != 'q') {
		rs2::frameset frames = pipe.wait_for_frames();
		rs2::frame color_frame = frames.get_color_frame();
		std::memcpy(color.data, color_frame.get_data(), array_size * 3 * sizeof(uchar));

		cudaMemcpy(img_color_device, color.data, array_size * 3 * sizeof(uchar), cudaMemcpyHostToDevice);
		GrayscaleKernel<<<block, thread>>>(img_color_device, img_result_device, size.width, size.height);
    cudaMemcpy(img_result.data, img_result_device, array_size * 3 * sizeof(uchar), cudaMemcpyDeviceToHost);

		cv::namedWindow("color", cv::WINDOW_AUTOSIZE);
		cv::imshow("color", color);

		cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
		cv::imshow("result", img_result);
	}
	cv::destroyAllWindows();
	cudaFree(img_color_device);
	cudaFree(img_result_device);

	return 0;
}
