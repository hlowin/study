#include "common.h"

namespace so {
common::common() {
  if (!glfwInit()) exit(-1);

  if (!gl3wInit()) exit(-1);

  window = glfwCreateWindow(800, 600, "sample", NULL, NULL);

  glfwMakeContextCurrent(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // imgui init
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

common::~common() {}

void common::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  ;

  glfwTerminate();
}
}  // namespace so