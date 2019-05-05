#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Shader.h"
#include "Bresenham.h"

const int HEIGHT = 1000;
const int WIDTH = 1000;
int border = 600;

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(const char *title, int width, int height) {
    GLFWwindow *ret = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!ret) {
        printf("Can't not create window!");
        glfwTerminate();
        exit(-1);
    }
    return ret;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    //border *= width / WIDTH;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    init();

    // create the window and viewport
    GLFWwindow *window = createWindow("triangle", WIDTH, HEIGHT);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Can't initialize glad!");
        exit(-1);
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glPointSize(2.0f);

    Shader shader("shader.vs", "shader.fs");

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    int type = 0;
    bool fill = false;
    int vertices[3][2] = {{ -400, 0 }, { 400, 0 }, { 0, 400 }};
    int center[2] = { 0 };
    int radius = 0;
    bool changed = true;
    std::vector<float> p;

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {
        // Process the input
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (changed) {
            p.clear();

            // Compute points
            if (type == 0) {
                // Triangle
                auto line1 = BresenhamLine(vertices[0][0], vertices[0][1], vertices[1][0], vertices[1][1]);
                auto line2 = BresenhamLine(vertices[0][0], vertices[0][1], vertices[2][0], vertices[2][1]);
                auto line3 = BresenhamLine(vertices[1][0], vertices[1][1], vertices[2][0], vertices[2][1]);
                p.insert(p.end(), line1.begin(), line1.end());
                p.insert(p.end(), line2.begin(), line2.end());
                p.insert(p.end(), line3.begin(), line3.end());
                if (fill) {
                    // Rasterization
                    auto inside = rasterize(vertices);
                    p.insert(p.end(), inside.begin(), inside.end());
                }
            } else {
                // Circle
                auto c = BresenhamCircle(center[0], center[1], radius);
                p.insert(p.end(), c.begin(), c.end());
            }

            // Normalize
            for (int i = 0; i < p.size(); i += 3) {
                p[i] /= (float)WIDTH;
                p[i + 1] /= (float)HEIGHT;
            }

            changed = false;
        }

        // VAO & VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, p.size() * sizeof(float), p.data(), GL_DYNAMIC_DRAW);

        // postion
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Activate: glUseProgram(shaderProgram);
        shader.use();
        glDrawArrays(GL_POINTS, 0, p.size() / 3);

        // Draw the menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Menu");

        changed |= ImGui::RadioButton("Triangle", &type, 0);
        changed |= ImGui::RadioButton("CIrcle", &type, 1);
        if (type == 0) {
            changed |= ImGui::SliderInt2("Angle 1", vertices[0], -border, border);
            changed |= ImGui::SliderInt2("Angle 2", vertices[1], -border, border);
            changed |= ImGui::SliderInt2("Angle 3", vertices[2], -border, border);
            changed |= ImGui::Checkbox("Rasterization", &fill);
        } else {
            changed |= ImGui::SliderInt2("Center", center, -border, border);
            changed |= ImGui::SliderInt("Radius", &radius, 0, border);
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Render
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}