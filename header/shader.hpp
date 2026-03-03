#ifndef SHADER_HPP
# define SHADER_HPP

#include <iostream>

class Shader
{
public:
	Shader();
	~Shader();
    void use();
    static Shader* getInstance();
    unsigned int getShader();
	bool compileShader(const char *vertexShaderSource, const char *fragmentShaderSource);
private:
    std::string loadFile(const char* path);
    unsigned int _shader;
    static Shader* _instanceServ;
};

#endif
