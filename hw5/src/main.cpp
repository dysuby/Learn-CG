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
const float PI = glm::pi<float>();

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    bool bonus = false;
    int p_or_o = 0;
    float orth[6] = { -10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f };
    float fov = glm::radians(45.0f), ratio = (float)WIDTH / (float)HEIGHT;
    float p_near = 0.1f, p_far = 60.0f;

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

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

    while (!glfwWindowShouldClose(window)) {
        float current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        // Process the input
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        if (type == 0) {
            // create transformations
            glm::mat4 model(1.0f);
            glm::mat4 view(1.0f);
            glm::mat4 projection(1.0f);

            // adjust
            model = glm::translate(model, glm::vec3(-1.5f, 0.5f, -1.5f));

            if (!bonus)
                view = glm::lookAt(glm::vec3(0.0, 0.0, 30.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            else 
                view = camera.GetViewMatrix();

            if (p_or_o) {
                projection = glm::ortho(orth[0], orth[1], orth[2], orth[3], orth[4], orth[5]);
            } else {
                model = glm::rotate(model, 1.0f, glm::vec3(0.5f, 0.5f, 0.5f));
                projection = glm::perspective(fov, ratio, p_near, p_far);
            }

            shader.setMat4("model", model);
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
        } else if (type == 1) {
            // create transformations
            glm::mat4 model(1.0f);
            glm::mat4 view(1.0f);
            glm::mat4 projection(1.0f);

            model = glm::rotate(model, 1.0f, glm::vec3(0.5f, 0.5f, 0.5f));

            float radius = 20.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
            
            projection = glm::perspective(fov, ratio, p_near, p_far);
            
            shader.setMat4("model", model);
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
        }

        // render cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw the menu
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Menu");

        ImGui::RadioButton("Basic 1", &type, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Basic 2", &type, 1);

        if (type == 0) {
            ImGui::Checkbox("Bonus", &bonus);

            ImGui::RadioButton("Perspective", &p_or_o, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Orthographic", &p_or_o, 1);
            if (!p_or_o) {
                ImGui::SliderAngle("fov", &fov, 1.0f, 360.0f);
                ImGui::SliderFloat("aspect_ratio", &ratio, 0.1f, 2.0f);
                ImGui::SliderFloat("p_near", &p_near, 0.1f, 60.0f);
                ImGui::SliderFloat("p_far", &p_far, 0.1f, 60.0f);
            } else {
                ImGui::SliderFloat("left", orth, -10.0f, 10.0f);
                ImGui::SliderFloat("right", orth + 1, -10.0f, 10.0f);
                ImGui::SliderFloat("bottom", orth + 2, -10.0f, 10.0f);
                ImGui::SliderFloat("up", orth + 3, -10.0f, 10.0f);
                ImGui::SliderFloat("o_near", orth + 4, 0.1f, 100.0f);
                ImGui::SliderFloat("o_far", orth + 5, 0.1f, 100.0f);
            }
        } else if (type == 1) {
            ImGui::SliderAngle("fov", &fov, 1.0f, 360.0f);
            ImGui::SliderFloat("aspect_ratio", &ratio, 0.1f, 2.0f);
            ImGui::SliderFloat("p_near", &p_near, 0.1f, 60.0f);
            ImGui::SliderFloat("p_far", &p_far, 0.1f, 60.0f);
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