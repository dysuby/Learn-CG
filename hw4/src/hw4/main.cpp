#define _USE_MATH_DEFINES

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Shader.h"

const int HEIGHT = 600;
const int WIDTH = 800;

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

void bonus1(const Shader &shader, int nums) {
    glm::mat4 view = glm::mat4(1.0f);
    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("view", view);

    // render boxes
    for (unsigned int i = 0; i < nums; ++i) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
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
    
    glEnable(GL_DEPTH_TEST);

    Shader shader("shader.vs", "shader.fs");

    float vertices[] = {
    -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
     2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
     2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
     2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
    -2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
    -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,

    -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
     2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 1.0f,
     2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
     2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
    -2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 1.0f,
    -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,

    -2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 1.0f,
    -2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
    -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
    -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
    -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
    -2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 1.0f,

     2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
     2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
     2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
     2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
     2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 1.0f,
     2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,

    -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
     2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,
     2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 1.0f,
     2.0f, -2.0f,  2.0f, 1.0f, 0.0f, 1.0f,
    -2.0f, -2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
    -2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f,

    -2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
     2.0f,  2.0f, -2.0f, 1.0f, 1.0f, 0.0f,
     2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
     2.0f,  2.0f,  2.0f, 0.0f, 0.0f, 1.0f,
    -2.0f,  2.0f,  2.0f, 0.0f, 1.0f, 1.0f,
    -2.0f,  2.0f, -2.0f, 0.0f, 1.0f, 0.0f
    };

    int type = 0;
    float trans[2] = { 0 };
    float rotate = 1;
    float scaling = 1;
    bool depth = true, auto_hor = false, auto_ver = false, auto_rotate = false, auto_scaling = false, auto_all = false;
    
    int bonus1_count = 8;

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::SetNextWindowContentSize(ImVec2(263.0f, 325.0f));

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.use();

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window)) {
        // Process the input
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        if (depth) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);

        if (type == 0) {
            // create transformations
            glm::mat4 model(1.0f);
            glm::mat4 view(1.0f);

            // adjust
            model = glm::rotate(model, 0.5f, glm::vec3(0.5f, 0.0f, 0.0f));

            if (auto_all || auto_hor) trans[0] = sin(glfwGetTime()) * 2;

            if (auto_all || auto_ver) trans[1] = cos(glfwGetTime()) * 2;

            if (auto_all || auto_scaling) scaling = cos(glfwGetTime()) + 1.01f;

            if (auto_all || auto_rotate) rotate = fmod((float)glfwGetTime(), 2 * M_PI);

            model = glm::rotate(model, rotate, glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, glm::vec3(trans[0], trans[1], -25.0f));
            view = glm::scale(view, glm::vec3(scaling, scaling, scaling)); 

            shader.setMat4("model", model);
            shader.setMat4("view", view);

            // render cube
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        } else if (type == 1) {
            bonus1(shader, bonus1_count);
        }

        // Draw the menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Menu");

        ImGui::RadioButton("Basic", &type, 0);
        ImGui::RadioButton("Bonus 1", &type, 1);
        ImGui::Checkbox("Depth Test", &depth);
        if (type == 0) {
            ImGui::SetWindowSize(ImVec2(263.0f, 325.0f));
            ImGui::Checkbox("Auto", &auto_all);

            if (!auto_all) {
                ImGui::Checkbox("Auto Horizontal", &auto_hor);
                ImGui::Checkbox("Auto Vertical", &auto_ver);
                ImGui::Checkbox("Auto Rotate", &auto_rotate);
                ImGui::Checkbox("Auto Scaling", &auto_scaling);
                if (!auto_hor) ImGui::SliderFloat("Horizontal", trans, -2, 2);
                if (!auto_ver) ImGui::SliderFloat("Vertical", trans + 1, -2, 2);
                if (!auto_rotate) ImGui::SliderAngle("Rotate", &rotate, 0.0f, 360.0f);
                if (!auto_scaling) ImGui::SliderFloat("Scaling", &scaling, 0.01, 2.01);
            }
        } else if (type == 1) {
            ImGui::SetWindowSize(ImVec2(263.0f, 150.0f));
            ImGui::SliderInt("Count of Cube", &bonus1_count, 1, 16);
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