#include "../header_files/shaderClass.h"
#include <iostream>


// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::cout << "generating shader objects [inside get_file_contents]" << std::endl;
	std::ifstream in(filename, std::ios::binary);
	if (in.is_open()) {
		try {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			std::cout << "generating shader objects {no errors thrown gathering : "<< filename << " }" << std::endl;
			return(contents);
		} 
		catch(...) {
		std::cout << "generating shader objects { error thrown gathering : "<< filename << " }"  << std::endl;
		return "";
		}
	}
	return "failed";
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{


	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::cout << "got the vertex code!!\n\n" << vertexCode << "\n\n" << std::endl;
	std::string fragmentCode = get_file_contents(fragmentFile); 
	std::cout << "got the fragment code!!\n\n" << fragmentCode << "\n\n" << std::endl;

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	std::cout << "converted the vertex code \n\n" << vertexSource << "\n\n" << std::endl;
	const char* fragmentSource = fragmentCode.c_str();
	std::cout << "converted the fragment code \n\n" << fragmentSource << "\n\n" << std::endl;

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::cout << "created vertexShader " << std::endl;
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	std::cout << "attatched vertexShader source to the Vertex Shader Object" << std::endl;
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	std::cout << "compiled vertexShader " << std::endl;

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::cout << "created fragmentShader " << std::endl;
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	std::cout << "attatched fragmentShader source to the Fragment Shader Object" << std::endl;
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	std::cout << "compiled fragmentShader " << std::endl;

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	std::cout << "creted sheader program object" << std::endl;
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	std::cout << "attatched vertexShader to shader program" << std::endl;
	glAttachShader(ID, fragmentShader);
	std::cout << "attatched fragmentShader to shader program" << std::endl;
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	std::cout << "Linked shaders together to Shader Program" << std::endl;

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	std::cout << "Deleted Vertex and Fragment Shader objects" << std::endl;

}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}