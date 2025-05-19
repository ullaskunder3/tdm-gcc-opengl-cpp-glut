#include <glad/glad.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

GLuint VAO, VBO, shaderProgram;
float angle = 0.0f;
bool rotating = true;
int direction = 1;
float color[3] = {0.2f, 0.7f, 1.0f};

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
uniform float angle;
void main() {
    float s = sin(angle);
    float c = cos(angle);
    mat3 rot = mat3(
        c, -s, 0.0,
        s,  c, 0.0,
        0.0, 0.0, 1.0
    );
    gl_Position = vec4(rot * aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 uColor;
void main() {
    FragColor = vec4(uColor, 1.0);
}
)";

void compileShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void setupTriangle() {
    float vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "angle"), angle);
    glUniform3f(glGetUniformLocation(shaderProgram, "uColor"), color[0], color[1], color[2]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}

void update(int value) {
    if (rotating) {
        angle += 0.01f * direction;
        if (angle > 2 * 3.14159f) angle -= 2 * 3.14159f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
        case ' ':
            rotating = !rotating;
            break;
        case 'd':
            direction *= -1;
            break;
        case 'r':
            color[0] = 1.0f; color[1] = 0.2f; color[2] = 0.2f;
            break;
        case 'g':
            color[0] = 0.2f; color[1] = 1.0f; color[2] = 0.2f;
            break;
        case 'b':
            color[0] = 0.2f; color[1] = 0.7f; color[2] = 1.0f;
            break;
    }
}

void init() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(1);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    compileShaders();
    setupTriangle();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("GLAD + FreeGLUT Rotating Triangle");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
