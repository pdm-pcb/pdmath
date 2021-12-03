#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "GLDebugger.hpp"

#include "pdmath/Camera.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

constexpr int window_x = 1920;
constexpr int window_y = 1080;

constexpr GLfloat square[] = {
    // world coordinates   texture coordinates
    -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,    // top left
     0.5f,  0.5f, 0.0f,    1.0f, 1.0f,    // top right
     0.5f, -0.5f, 0.0f,    1.0f, 0.0f,    // bottom right
    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f     // bottom left
};

constexpr GLuint indices[] = {
    0, 1, 2,    // upper triangle
    0, 2, 3     // lower triangle
};

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // create GLFW window
    GLFWwindow* window = glfwCreateWindow(window_x, window_y,
                                          "Learn OpenGL",
                                          nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // let GLAD sort it out for us
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    Renderer renderer(window_x, window_y);

    // Enable debug output
    GLDebugger debugger;

    // buffers
    VertexArray va;
    VertexBuffer vb(square, sizeof(square));
    vb.set_layout({
        { "world_coordinates",   GL_FLOAT, 3, GL_FALSE },
        { "texture_coordinates", GL_FLOAT, 2, GL_FALSE }
    });
    va.add_buffer(vb);
    IndexBuffer ib(indices, 6);

    // shaders!
    Shader crate0_shader("../../demo/shaders/crate.vert",
                         "../../demo/shaders/crate0.frag");

    // textures!
    Texture crate0_texture("../../demo/resources/textures/crate0/crate0.png");
    crate0_texture.bind();
    crate0_shader.set_uniform1i("texture_slot", crate0_texture.texture_slot());

    pdm::Camera camera;
    camera.set_ortho(-2.0f, 2.0f,   // width
                     -1.5f, 1.5f,   // height
                     -1.0f, 1.0f,   // frustum depth
                      window_x, window_y,
                      1.0f);        // z-depth

    crate0_shader.set_uniform_mat4f("ortho_proj", camera.ortho_ndc());

    // Dear ImGUI -------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
    ImFont *font =
        ImGui::GetIO().Fonts->AddFontFromFileTTF(
            "../../demo/resources/fonts/OpenSans.ttf", 24.0f);
    assert(font != nullptr && "ImGUI couldn't find font.");
    //-------------------------------------------
   
    while(!glfwWindowShouldClose(window)) {
        renderer.viewport(window_x, window_y);

        process_input(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            // Create a window called "Hello, world!" and append into it.
            ImGui::Begin("Hello, world!");

            // Display some text (you can use a format strings too)
            ImGui::Text("This is some useful text.");

            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

            // Buttons return true when clicked (most widgets return true when
            // edited/activated)
            if(ImGui::Button("Button")) {
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        crate0_texture.bind();
        renderer.draw(va, ib, crate0_shader);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
  
    return 0;
}

void process_input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}