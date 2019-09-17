#include "viewer.h"

int main() {

    if (!glfwInit()) return -1;

    if (!gl3wInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "sample", NULL, NULL);

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // imgui init
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // gui
        {
            ImGui::Begin("Test Window");

            ImGui::Text("Hello, world %d", 123);

            if (ImGui::Button("OK")) {
                std::cout << "Button" << std::endl;
            }

            static char buf[256] = "aaa";
            if (ImGui::InputText("string", buf, 256)) {
                std::cout << "InputText" << std::endl;
            }

            static float f = 0.0f;
            if (ImGui::SliderFloat("float", &f, 0.0f, 1.0f)) {
                std::cout << "SliderFloat" << std::endl;
            }
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();;

    glfwTerminate();

    return 0;
}