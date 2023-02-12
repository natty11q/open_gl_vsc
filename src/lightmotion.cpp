#include "../header_files/lightmotion.h"
#include <iostream>

void ChangeLightPos(GLFWwindow* window, float* X_pos, float* Y_pos ,float* Z_pos)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS or 
    glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS or
    glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS or
    glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS or
    glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS or
    glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS or
    glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS )
    {

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            *X_pos = *X_pos - 0.04f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            *X_pos = *X_pos + 0.04f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            *Z_pos = *Z_pos + 0.04f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            *Z_pos = *Z_pos - 0.04f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
        {
            *Y_pos = *Y_pos - 0.04f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
        {
            *Y_pos = *Y_pos + 0.04f;
        }
        
        std::cout << "X : " << *X_pos << "\nY : " << *Y_pos << "\nZ : " << *Z_pos << "\n" << std::endl;
    }
}