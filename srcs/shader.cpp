#include "../header/shader.hpp"
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include "../header/scop.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
}


Shader* Shader::getInstance()
{
	if (!_instanceServ)
	{
		_instanceServ = new Shader();
	}
	return _instanceServ;
}


bool Shader::compileShader(const char *vertexShaderSource, const char *fragmentShaderSource)
{

	std::string vertexCode = loadFile(vertexShaderSource);
	std::string fragmentCode = loadFile(fragmentShaderSource);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
    	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else
		std::cout << "Compilation Shader: Success" << std::endl;


    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
    	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else
		std::cout << "Compilation Fragment Shader: Success" << std::endl;

    _shader = glCreateProgram();
	glAttachShader(_shader, vertexShader);
	glAttachShader(_shader, fragmentShader);
	glLinkProgram(_shader);
    glGetProgramiv(_shader, GL_LINK_STATUS, &success);
    if (!success)
	{
        glGetProgramInfoLog(_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;

    }
	else
		std::cout << "Shader linking: Success" << std::endl;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
    
}

unsigned int Shader::getShader()
{
	return _shader;
}

void Shader::use() 
{ 
    glUseProgram(_shader);
}

std::string Shader::loadFile(const char* path)
{

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "error to open file: " << path << std::endl;
		return "error";
	}
	std::stringstream shaderStream;
	shaderStream << file.rdbuf();
	file.close();
	return shaderStream.str();
}