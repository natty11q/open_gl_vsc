#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <iostream>
#include <vector>
#include "global.hpp"

#include "../header_files/shaderClass.h"
#include "../header_files/VAO.h"
#include "../header_files/VBO.h"
#include "../header_files/EBO.h"
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

const int SCREEN_WIDTH  = 450;
const int SCREEN_HEIGHT = 450;


GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
bool fullscreen = false;

std::vector<int> manageWindow(GLFWwindow *window ,int last_w, int last_h)
{   
    int W,H;
    glfwGetWindowSize(window,&W,&H);

    if (last_w != W and last_h != H) {
        std::cout << "width  : " << W << std::endl;
        std::cout << "hwight : " << H << "\n" <<std::endl;
        glViewport(0, 0, W, H);
    }
    std::vector<int> return_arr = {W,H};

    if (W < 300){W = 300;}
    if (H < 300){H = 300;}

    return return_arr;
}

int main(int argc,const char* argv[]) 
{

    // inits ------------------------------------------------------- //

    glfwInit();                                                      // initialise glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                   // tell glfw what version of OpenGL is being used (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   // tell glfw that CORE profile is being used [only modern functions]
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    // verticies for triangle -------------------------------------- //

    float vertices[] =
    {
        -0.5f  , -0.5f * float(sqrt(3)) / 3  , 0.0f,   // lower left
        0.5f  , -0.5f * float(sqrt(3)) / 3  , 0.0f,   // lower right
        0.0f  ,  0.5f * float(sqrt(3)) * 2/3, 0.0f,  // upper corner
        -0.5f / 2  , 0.5f * float(sqrt(3)) / 6  , 0.0f, // inner left
        0.5f / 2  , 0.5f * float(sqrt(3)) / 6  , 0.0f, // inner right
        0.0f  , -0.5f * float(sqrt(3)) / 3, 0.0f      // inner bottow
    };
    std::cout << "Created verticies" << std::endl;

    GLuint indices[] = {
        0,3,5, // L Left triangle
        3,2,4, // L Right triangle
        5,4,1  // U triangle
    };
    std::cout << "created indicies" << std::endl;

    // init the window --------------------------------------------- //
    
    GLFWwindow* window;

    if (!fullscreen){window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_WIDTH, "Enumeration praime updt", NULL, NULL);}  // create the window
    else {window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_WIDTH, "Enumeration praime", primary_monitor, NULL);}  // <- if fullscreen

    
    if (window == NULL) {                                            // check if the window is made sucsessfully
        std::cout << "fat fail , No window D: !" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); 
    std::cout << "created window" << std::endl;                                 // add window to current context


    // load glad --------------------------------------------------- //

    gladLoadGL();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }




    glViewport(0 ,0 , SCREEN_WIDTH, SCREEN_WIDTH); // x,y,x,y // specify veiwport
     
    std::cout << "generating shader objects" << std::endl;
    // Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("/Users/natty22q/codestuffs/Cpp/games/11q_combat_simulator/recources/shaders/default.vert"
    ,"/Users/natty22q/codestuffs/Cpp/games/11q_combat_simulator/recources/shaders/default.frag");

    std::cout << "generated shader objects" << std::endl;


    std::cout << "generate vetex arr obj" << std::endl;
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
    std::cout << "generated vertex arr obj" << std::endl;

    std::cout << "VBO start" << std::endl;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
    std::cout << "VBO gen end" << std::endl;
    std::cout << "EBO start" << std::endl;
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
    std::cout << "EBO gen end" << std::endl;

    
	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
    std::cout << "linked VBO to VAO" << std::endl;
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
    std::cout << "VAO UNBINDED" << std::endl;
	VBO1.Unbind();
    std::cout << "VBO UNBINDED" << std::endl;
	EBO1.Unbind();
    std::cout << "EBO UNBINDED" << std::endl;


    std::cout << "going to main loop" << std::endl;
    // main game loop ------------------------------------------------ //
    std::vector<int> sizearr = {SCREEN_WIDTH,SCREEN_HEIGHT};
    while(!glfwWindowShouldClose(window)) {

        processInput(window);
        sizearr = manageWindow(window,sizearr[0],sizearr[1]);


        // specify bg colour
        glClearColor(col_Blue[0],col_Blue[1],col_Blue[2],1.0f);   // r,g,b,a // BG colour
        glClear(GL_COLOR_BUFFER_BIT);                             // clear the back buffer and assgn the new colour


        // Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices

        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT ,0);
        // glBindVertexArray(0);

        glfwSwapBuffers(window);

        glfwPollEvents(); // handles main GLFW events

    }
    
    std::cout<< "ending" <<std::endl;
    VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();

    // std::cout<< "press enter to quit" <<std::endl;
    // std::cin.get();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);}
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        glfwSetWindowSize(window,300,300);}
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    if (width < 300){width = 300;}
    if (height < 300){height = 300;}

    std::cout << "width  : " << width << std::endl;
    std::cout << "hwight : " << height << std::endl;
    glViewport(0, 0, width, height);
}