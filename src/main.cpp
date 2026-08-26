#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
  GLFWwindow* window = nullptr;

  if (!glfwInit()) {
    std::cerr << "Failed to load GLFW." << std::endl;
    return -1;
  }

  window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    std::cerr << "Failed to GLAD." << std::endl;
    glfwTerminate();
    return -1;
  }

  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
