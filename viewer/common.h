#include <stdlib.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

namespace so {
class common {
 public:
	common();
	~common();
	void shutdown();

	GLFWwindow* window;
};
} // namespace so