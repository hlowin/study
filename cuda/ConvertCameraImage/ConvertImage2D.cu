#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <iostream>

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

__global__
void GrayscaleKernel(
	uchar3* img_src,
	const size_t src_pitch,
	uchar3* result,
	const size_t dst_pitch,
	const int width,
	const int height
) {
	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;

	if(x < width && y < height) {
		int i = x + y * src_pitch / sizeof(uchar3);
		const uchar3 col = img_src[i];
		const uchar gs = (col.x + col.y + col.z) / 3;
		i = x + y * dst_pitch / sizeof(uchar3);
		result[i] = {gs, gs, gs};
	}
}

__global__
void CopyKernel(
	uchar3* img_src,
	const size_t src_pitch,
	uchar3* result,
	const size_t dst_pitch,
	const int width,
	const int height
) {
	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;

	if(x < width && y < height) {
		const int i = x + y * src_pitch / sizeof(uchar3);
		const uchar3 col = img_src[i];
		result[i] = {col.x, col.y, col.z};
	}
}

int main() {
	rs2::config cfg;
	const int width = 640;
	const int height = 480;
	cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_BGR8, 30);

	rs2::pipeline pipe;
	pipe.start(cfg);

	cv::Mat color(cv::Size(width, height), CV_8UC3);
	// cv::Mat color = cv::imread("../exit.png");
	
	cv::Size size = color.size();

	cv::Mat img_result(size, CV_8UC3);

	uchar3 *img_color_device;
	size_t color_pitch_device;
	cudaMallocPitch(&img_color_device, &color_pitch_device, size.width * sizeof(uchar3), size.height);

	uchar3 *img_result_device;
	size_t result_pitch_device;
	cudaMallocPitch(&img_result_device, &result_pitch_device, size.width * sizeof(uchar3), size.height);

	// dim3 dimBlock(32, 32);
	dim3 dimBlock(16, 16);
	dim3 dimGrid(size.width / dimBlock.x, size.height / dimBlock.y);

	while (cv::waitKey(1) != 'q') {
		rs2::frameset frames = pipe.wait_for_frames();
		rs2::frame color_frame = frames.get_color_frame();
		std::memcpy(color.data, color_frame.get_data(), width * height * sizeof(uchar3));

		cudaMemcpy2D(img_color_device, color_pitch_device, color.data, color.step,
			size.width * sizeof(uchar3), size.height, cudaMemcpyDefault);
		CopyKernel<<<dimGrid, dimBlock>>>(img_color_device, color_pitch_device,
			img_result_device, result_pitch_device, size.width, size.height);
		cudaMemcpy2D(img_result.data, img_result.step, img_result_device, result_pitch_device,
			size.width * sizeof(uchar3), size.height, cudaMemcpyDefault);

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
