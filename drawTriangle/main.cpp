#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Shader.h"

const int HEIGHT = 1000;
const int WIDTH = 1000;

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

    glPointSize(10.0f);
    glLineWidth(5.0f);

    Shader shader("shader.vs", "shader.fs");

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    
    // triangle indices
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    ImVec4 topRightColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 topLeftColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 bottomRightColor = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
    ImVec4 bottomLeftColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    bool imgui = true;
    int type = 0;

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    while (!glfwWindowShouldClose(window)) {
        // Process the input
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        float vertices[] = {
            0.5f, 0.5f, 0.0f, topRightColor.x, topRightColor.y, topRightColor.z,
            0.5f, -0.5f, 0.0f, bottomRightColor.x, bottomRightColor.y, bottomRightColor.z,
            -0.5f, -0.5f, 0.0f, bottomLeftColor.x, bottomLeftColor.y, bottomLeftColor.z,
            -0.5f, 0.5f, 0.0f, topLeftColor.x, topLeftColor.y, topLeftColor.z
        };

        // VAO & VBO
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // postion
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Activate: glUseProgram(shaderProgram);
        shader.use();

        // Draw the graphics
        glBindVertexArray(VAO);
        if (type == 0) {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        } else if (type == 1) {
            // only line at front and back
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawArrays(GL_LINE_STRIP, 2, 2);
        } else if (type == 2) {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_POINTS, 0, 4);
        }

        // Draw the menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Edit color", &imgui, ImGuiWindowFlags_MenuBar);

        // Bind the color
        ImGui::ColorEdit3("Top right color", (float*)&topRightColor);
        ImGui::ColorEdit3("Top left color", (float*)&topLeftColor);
        ImGui::ColorEdit3("Bottom right color", (float*)&bottomRightColor);
        ImGui::ColorEdit3("Bottom left color", (float*)&bottomLeftColor);

        // Bind the type
        ImGui::RadioButton("Draw triangle", &type, 0);
        ImGui::RadioButton("Draw line", &type, 1);
        ImGui::RadioButton("Draw rectangle", &type, 2);
        ImGui::RadioButton("Draw point", &type, 3);
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