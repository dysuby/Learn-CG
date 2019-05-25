#include <cstdio>
#include <cstdlib>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"


const int HEIGHT = 600;
const int WIDTH = 800;

bool running = false;
double running_t = 0.0f;

std::vector<glm::vec2> points;

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
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !running) {
        running = true;
        running_t = 0.0f;
    }
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
    // stop when running animation
    if (running) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //getting cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // normalize
        points.push_back(glm::vec2((float(xpos) / float(WIDTH) * 2.0f) - 1, -((float(ypos) / float(HEIGHT) * 2.0f) - 1)));
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        points.pop_back();
    }
}


// Binomial coefficient C(n,K)
int binom(int n, int k) {
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    int result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

// B(t)
glm::vec2 bezier(double t) {
    int order = points.size() - 1;

    double y = 0;
    double x = 0;

    double p1 = glm::pow(1 - t, order);
    double p2 = 1;

    for (int i = 0; i <= order; i++) {
        x += binom(order, i) * p1 * p2 * points[i].x;
        y += binom(order, i) * p1 * p2 * points[i].y;
        p1 /= 1 - t;
        p2 *= t;
    }

    return glm::vec2(x, y);
}

void drawTrack(std::vector<glm::vec2> &nodes, double t) {
    if (nodes.size() < 2) return;

    std::vector<glm::vec2> next;
    for (int i = 1; i < nodes.size(); ++i) {
        float raw_p[]{
            nodes[i - 1].x, nodes[i - 1].y, 0.0f, 1.0f, 1.0f, 1.0f,
            nodes[i].x,     nodes[i].y,     0.0f, 1.0f, 1.0f, 1.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(raw_p), raw_p, GL_STATIC_DRAW);
        glDrawArrays(GL_LINES, 0, 2);

        glm::vec2 nextPoint;
        nextPoint.x = (nodes[i] - nodes[i - 1]).x * t;
        nextPoint.y = (nodes[i] - nodes[i - 1]).y * t;
        next.push_back(nextPoint);
    }
    drawTrack(next, t);
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
    glfwSetMouseButtonCallback(window, mouseCallback);
    
    Shader shader("shader.vs", "shader.fs");

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.use();

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        shader.use();

        glPointSize(10.0f);
        std::vector<float> renderPoints;
        for (int i = 0; i < points.size(); ++i) {
            std::vector<float> p{
              points[i].x, points[i].y, 0.0f, 1.0f, 1.0f, 1.0f
            };

            renderPoints.insert(renderPoints.end(), p.begin(), p.end());

            if (i > 0) {
                float *ptr = renderPoints.data() + (i - 1) * 6;
                glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), ptr, GL_STATIC_DRAW);
                glDrawArrays(GL_LINES, 0, 2);
            }
        }

        float *ptr = renderPoints.data();
        glBufferData(GL_ARRAY_BUFFER, renderPoints.size() * sizeof(float), ptr, GL_STATIC_DRAW);

        glDrawArrays(GL_POINTS, 0, points.size());

        if (points.size() > 2) {
            glPointSize(1.0f);
            std::vector<float> bezierPoints;
            int count = 0;
            for (double t = 0.0f; t < 1.0f; t += 0.0005) {
                glm::vec2 point(bezier(t));
                std::vector<float> p{
                    point.x, point.y, 0.0f, 1.0f, 1.0f, 1.0f
                };
                bezierPoints.insert(bezierPoints.end(), p.begin(), p.end());

                if (count > 0) {
                    float *ptr = bezierPoints.data() + (count - 1) * 6;
                    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), ptr, GL_STATIC_DRAW);
                    glDrawArrays(GL_LINES, 0, 2);
                }
                ++count;

            }

            if (running) {
                // use loop instead of recursive
                std::vector<glm::vec2> nodes(points);
                while (nodes.size() > 1) {
                    std::vector<glm::vec2> next;
                    for (int i = 1; i < nodes.size(); ++i) {
                        // draw line
                        float raw_p[]{
                            nodes[i - 1].x, nodes[i - 1].y, 0.0f, 1.0f, 1.0f, 0.0f,
                            nodes[i].x,     nodes[i].y,     0.0f, 1.0f, 1.0f, 0.0f
                        };

                        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), raw_p, GL_STATIC_DRAW);
                        glDrawArrays(GL_LINES, 0, 2);

                        // cacluate next level
                        glm::vec2 nextPoint;
                        nextPoint.x = nodes[i].x * running_t + nodes[i - 1].x * (1 - running_t);
                        nextPoint.y = nodes[i].y * running_t + nodes[i - 1].y * (1 - running_t);
                        next.push_back(nextPoint);
                    }
                    nodes = next;
                }
                
                running_t += 0.01;
                if (running_t >= 1.0f)
                    running = false;
            }
        } else {
            running = false;
        }

        // Render
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}