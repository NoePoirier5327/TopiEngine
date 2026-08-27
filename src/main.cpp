#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
  GLFWwindow* window = nullptr;

  if (!glfwInit()) {
    std::cerr << "Failed to load GLFW." << std::endl;
    return -1;
  }

  // Option de fonctionnement du GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    std::cerr << "Failed to GLAD." << std::endl;
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 640, 480);

  // Position du triangle à afficher.
  float vertices[] = {
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f
  };

  // On compile le shader de vertex (il est responsable pour la liaison des vertices).
  const char* vertex_shader_source = R"glsl(
    #version 150 core

    in vec2 position;

    void main() {
      gl_Position = vec4(position, 0.0, 1.0);
    }
  )glsl";

  GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr);
  glCompileShader(vertex_shader_id);

  // On gère les erreurs de compilation du shader de vertex
  GLint status;
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    char buffer[512];
    glGetShaderInfoLog(vertex_shader_id, 512, nullptr, buffer);

    std::cerr << "Vertex shader failed to compile : " << buffer << std::endl;

    glfwTerminate();
    return -1;
  }

  // On compile le shader de fragment (il est responsable pour la couleur d'affichage).
  const char* fragment_shader_source = R"glsl(
    #version 150 core

    out vec4 out_color;

    void main() {
      out_color = vec4(1.0, 1.0, 1.0, 1.0);
    }
  )glsl";

  GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr);
  glCompileShader(fragment_shader_id);

  // On gère les erreurs de compilation du vecteur 
  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    char buffer[512];
    glGetShaderInfoLog(fragment_shader_id, 512, nullptr, buffer);

    std::cerr << "Fragment shader failed to compile : " << buffer << std::endl;

    glfwTerminate();
    return -1;
  }

  // On combine les shaders précédent dans un même shader.
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader_id);
  glAttachShader(shader_program, fragment_shader_id);
  glBindFragDataLocation(shader_program, 0, "out_color");
  glLinkProgram(shader_program);
  glUseProgram(shader_program);

  // On créer un vao pour modifier les vertices du triangle de manière dynamique.
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Ajout des vertices du triangle dans le bugger de la carte graphique.
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // On lie les vertices et les attribues des shaders.
  GLint pos_attribute = glGetAttribLocation(shader_program, "position");
  glVertexAttribPointer(pos_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(pos_attribute);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
