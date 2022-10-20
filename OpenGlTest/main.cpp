//
//  main.cpp
//  OpenGlTest
//
//  Created by 박동제 on 2022/10/18.
//

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main()
{
    // -------------------------------- INIT ------------------------------- //

    // Init GLFW
    if (glfwInit() != GL_TRUE) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    
    // Create a rendering window with OpenGL 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };  
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);
    

    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    const char* vertexSource = "#version 330 core \n layout (location = 0) in vec3 aPos; void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); } ";
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char* fragmentShaderSource = "#version 330 core \n out vec4 FragColor; void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); } ";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "FragColor");
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::GL_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    
    
    while(!glfwWindowShouldClose(window))
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        
        //
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //렌더링
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // use shader Program
        glUseProgram(shaderProgram);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    // Terminate GLFW
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  
    glfwTerminate();

    return 0;
}


// ----------------------------- RESOURCES ----------------------------- //
//// Create Vertex Array Object
//GLuint vao;
//glGenVertexArrays(1, &vao);
//glBindVertexArray(vao);
//
//// Create a Vertex Buffer Object and copy the vertex data to it
//GLuint vbo;
//glGenBuffers(1, &vbo);
//glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//float vertices[] = {
//     0.0f,  0.5f, // Vertex 1 (X, Y)
//     0.5f, -0.5f, // Vertex 2 (X, Y)
//    -0.5f, -0.5f  // Vertex 3 (X, Y)
//};
//
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//// Create and compile the vertex shader
//const char* vertexSource = GLSL(
//    in vec2 position;
//    
//    void main() {
//        gl_Position = vec4(position, 0.0, 1.0);
//    }
//);
//
//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//glShaderSource(vertexShader, 1, &vertexSource, NULL);
//glCompileShader(vertexShader);
//
//// Create and compile the fragment shader
//const char* fragmentSource = GLSL(
//    out vec4 outColor;
//    
//    void main() {
//        outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    }
//);
//
//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
//glCompileShader(fragmentShader);
//
//// Link the vertex and fragment shader into a shader program
//GLuint shaderProgram = glCreateProgram();
//glAttachShader(shaderProgram, vertexShader);
//glAttachShader(shaderProgram, fragmentShader);
//glBindFragDataLocation(shaderProgram, 0, "outColor");
//glLinkProgram(shaderProgram);
//glUseProgram(shaderProgram);
//
//// Specify the layout of the vertex data
//GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
//glEnableVertexAttribArray(posAttrib);
//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//// ---------------------------- RENDERING ------------------------------ //
//
//while(!glfwWindowShouldClose(window))
//{
//    // Clear the screen to black
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    // Draw a triangle from the 3 vertices
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//
//    // Swap buffers and poll window events
//    glfwSwapBuffers(window);
//    glfwPollEvents();
//}
//
//// ---------------------------- CLEARING ------------------------------ //
//
//// Delete allocated resources
//glDeleteProgram(shaderProgram);
//glDeleteShader(fragmentShader);
//glDeleteShader(vertexShader);
//glDeleteBuffers(1, &vbo);
//glDeleteVertexArrays(1, &vao);
//
//// ---------------------------- TERMINATE ----------------------------- //
