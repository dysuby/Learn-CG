#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Shader.h"
#include "Camera.h"

const int HEIGHT = 600;
const int WIDTH = 800; 

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool mouse = false;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// light
glm::vec3 lightPos(4.0f, 0.0f, 2.0f);

const float movementSpeed = 5.0f;
const float mouseSensitivity = 0.1f;

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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float velocity = deltaTime * movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, velocity);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, velocity);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, velocity);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, velocity);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!mouse) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset * mouseSensitivity, yoffset * mouseSensitivity);
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
    glfwSetCursorPosCallback(window, mouseCallback);
    
    glEnable(GL_DEPTH_TEST);
    Shader phongLightingShader("phong_lighting.vs", "phong_lighting.fs");
    Shader gouraudLightingShader("gouraud_lighting.vs", "gouraud_lighting.fs");

    float vertices[] = {
        -2.0f, -2.0f, -2.0f,  0.0f,  0.0f, -1.0f,
         2.0f, -2.0f, -2.0f,  0.0f,  0.0f, -1.0f,
         2.0f,  2.0f, -2.0f,  0.0f,  0.0f, -1.0f,
         2.0f,  2.0f, -2.0f,  0.0f,  0.0f, -1.0f,
        -2.0f,  2.0f, -2.0f,  0.0f,  0.0f, -1.0f,
        -2.0f, -2.0f, -2.0f,  0.0f,  0.0f, -1.0f,

        -2.0f, -2.0f,  2.0f,  0.0f,  0.0f,  1.0f,
         2.0f, -2.0f,  2.0f,  0.0f,  0.0f,  1.0f,
         2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  1.0f,
         2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  1.0f,
        -2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  1.0f,
        -2.0f, -2.0f,  2.0f,  0.0f,  0.0f,  1.0f,

        -2.0f,  2.0f,  2.0f, -1.0f,  0.0f,  0.0f,
        -2.0f,  2.0f, -2.0f, -1.0f,  0.0f,  0.0f,
        -2.0f, -2.0f, -2.0f, -1.0f,  0.0f,  0.0f,
        -2.0f, -2.0f, -2.0f, -1.0f,  0.0f,  0.0f,
        -2.0f, -2.0f,  2.0f, -1.0f,  0.0f,  0.0f,
        -2.0f,  2.0f,  2.0f, -1.0f,  0.0f,  0.0f,

         2.0f,  2.0f,  2.0f,  1.0f,  0.0f,  0.0f,
         2.0f,  2.0f, -2.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f, -2.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f, -2.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f,  2.0f,  1.0f,  0.0f,  0.0f,
         2.0f,  2.0f,  2.0f,  1.0f,  0.0f,  0.0f,

        -2.0f, -2.0f, -2.0f,  0.0f, -1.0f,  0.0f,
         2.0f, -2.0f, -2.0f,  0.0f, -1.0f,  0.0f,
         2.0f, -2.0f,  2.0f,  0.0f, -1.0f,  0.0f,
         2.0f, -2.0f,  2.0f,  0.0f, -1.0f,  0.0f,
        -2.0f, -2.0f,  2.0f,  0.0f, -1.0f,  0.0f,
        -2.0f, -2.0f, -2.0f,  0.0f, -1.0f,  0.0f,

        -2.0f,  2.0f, -2.0f,  0.0f,  1.0f,  0.0f,
         2.0f,  2.0f, -2.0f,  0.0f,  1.0f,  0.0f,
         2.0f,  2.0f,  2.0f,  0.0f,  1.0f,  0.0f,
         2.0f,  2.0f,  2.0f,  0.0f,  1.0f,  0.0f,
        -2.0f,  2.0f,  2.0f,  0.0f,  1.0f,  0.0f,
        -2.0f,  2.0f, -2.0f,  0.0f,  1.0f,  0.0f
    };

    int type = 0;
    bool bonus = false;
    float ambient = 0.1f;
    float diff = 1.0f;
    float specular = 0.5f;
    int shininess = 32;

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        float current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        // Process the input
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader lightingShader = type ? gouraudLightingShader : phongLightingShader;

        glm::mat4 view = camera.GetViewMatrix();

        if (bonus) {
            lightPos.x = glm::sin(glfwGetTime()) * 6.0;
            lightPos.y = glm::cos(glfwGetTime()) * 5.0;
            lightPos.z = 2.0f;
        }

        // lighting
        lightingShader.use();

        lightingShader.setFloat("ambientStrength", ambient);    // ambient 因子
        lightingShader.setFloat("diffStrength", diff);          // diffuse 因子
        lightingShader.setFloat("specularStrength", specular);  // specular 因子
        lightingShader.setInt("shininess", shininess);          // 反光度因子

        lightingShader.setVec3("objectColor", glm::vec3(0.3f, 0.3f, 1.0f));  // 物体颜色
        lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));    // 光照颜色
        lightingShader.setVec3("lightPos", lightPos);                         // 光源位置
        lightingShader.setVec3("viewPos", camera.getPosition());              // 观察者坐标

        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        // 旋转调整角度
        model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.5, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0, 0.5, 0.0));
        lightingShader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw the menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Menu");

        ImGui::RadioButton("Phong", &type, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Gouraud", &type, 1);
        ImGui::Checkbox("Mouse Move", &mouse);

        ImGui::Checkbox("Bonus", &bonus);

        ImGui::SliderFloat("ambient", &ambient, 0.1f, 2.0f);
        ImGui::SliderFloat("diffuse", &diff, 0.1f, 2.0f);
        ImGui::SliderFloat("specular", &specular, 0.1f, 2.0f);
        ImGui::SliderInt("shininess", &shininess, 2, 256);

        if (!bonus) {
            ImGui::SliderFloat("Light X", &lightPos.x, -10.0, 10.0f);
            ImGui::SliderFloat("Light Y", &lightPos.y, -10.0, 10.0f);
            ImGui::SliderFloat("Light Z", &lightPos.z, -10.0, 10.0f);
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