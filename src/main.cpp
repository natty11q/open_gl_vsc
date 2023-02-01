#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "global.hpp"
#include "shaders.hpp"

// buffers
/*
*/

// vertex shaders & fragment shaders

/* 

    shaders:

        * draw call -> vertex shader -> fragment shader -> visual output

        * vertex shader code get called for each vertex that is created
        * vertex tell where the vertex should be rendered in the window
        * can pass data/attributes into the next stage

        * fragment shader : called once for every pixel that gets  [ rastered ]

        * calculations / critical operations should be done in the vertex shader get called for each vertex
        * however in the fragment shader it will get called for each pixel
        * unless its things like lighting, each pixels colour value will vary so that should be valvulated in the fragment shader
        * fragment shader, runs to calculate the colour of each pixel

*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

unsigned int SCREEN_WIDTH  = 1000;
unsigned int SCREEN_HEIGHT = 450;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";


GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
bool fullscreen = false;

int main(int argc,const char* argv[]) {

    std::cout << "begin?" << std::endl;


    // inits ------------------------------------------------------- //

    glfwInit();                                                      // initialise glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                   // tell glfw what version of OpenGL is being used (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   // tell glfw that CORE profile is being used [only modern functions]
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // verticies for triangle -------------------------------------- //

    GLfloat verticies[] =
    {
        -0.5f , -0.5f * float(sqrt(3)) / 3  , 0.0f,
        0.5f  , -0.5f * float(sqrt(3)) / 3  , 0.0f,
        0.0f  ,  0.5f * float(sqrt(3)) * 2/3, 0.0f,
    };

    // init the window --------------------------------------------- //
    
    GLFWwindow* window;

    if (!fullscreen){window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_WIDTH, "Enumeration praime", NULL, NULL);}  // create the window
    else {window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_WIDTH, "Enumeration praime", primary_monitor, NULL);}  // <- if fullscreen

    
    if (window == NULL) {                                            // check if the window is made sucsessfully
        std::cout << "fat fail , No window D: !" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                  // add window to current context

    // load glad --------------------------------------------------- //

    gladLoadGL();



    glViewport(0 ,0 , SCREEN_WIDTH, SCREEN_WIDTH); // x,y,x,y // specify veiwport



    GLuint Vertex_Shader = glCreateShader(GL_VERTEX_SHADER);         // crete vertex shader 
    glShaderSource(Vertex_Shader, 1, &vertexShaderSource, NULL);
    glCompileShader(Vertex_Shader);                                  // compile the code to be understood by gpu

    GLuint Fragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);     // create fragment shader
    glShaderSource(Fragment_Shader, 1, &fragmentShaderSource, NULL);
    glCompileShader(Fragment_Shader);                                // compile

    GLuint shaderProgram = glCreateProgram();                        // wrap the shaders into shaderprogram so that they can be used

    glAttachShader(shaderProgram, Vertex_Shader);
    glAttachShader(shaderProgram, Fragment_Shader);
    glLinkProgram(shaderProgram);

    glDeleteShader(Vertex_Shader);
    glDeleteShader(Fragment_Shader);


    GLuint VAO, VBO;

    glGenVertexArrays(1 , &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // specify bg colour
    glClearColor(col_Blue[0],col_Blue[1],col_Blue[2],1.0f);   // r,g,b,a // BG colour
    glClear(GL_COLOR_BUFFER_BIT);                             // clear the back buffer and assgn the new colour

    glfwSwapBuffers(window);                                  // swap the back buffer with the front buffer




    // main game loop ------------------------------------------------ //
    while(!glfwWindowShouldClose(window)) {


        glClearColor(col_Blue[0],col_Blue[1],col_Blue[2],1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 , 3);

        glfwSwapBuffers(window);

        glfwPollEvents(); // handles main GLFW events

    }
    
    std::cout<< "ending" <<std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout<< "press enter to quit" <<std::endl;
    std::cin.get();

    return 0;
}