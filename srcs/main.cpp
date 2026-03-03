#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "initgl.cpp"
#include "../header/shader.hpp"
#include "../header/triangle.hpp"
#include "../header/mesh.hpp"
#include <map>
#include <vector>
#include <cmath>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loopWindow(GLFWwindow* window, Mesh *mesh);

std::map<int, Triangle *> triangle();
Shader* Shader::_instanceServ = NULL;

int main ()	
{
	GLFWwindow* window = initGl();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	Shader *shader = Shader::getInstance();
	shader->compileShader("./shader/multiColor.vert", "./shader/multiColor.frag");
	if (shader == 0) return 1;
	// const float vertices[] = {
    // -0.5f, -0.5f, 0.0f,
    //  0.5f, -0.5f, 0.0f,
    //  0.0f,  0.5f, 0.0f
	// };
	// Triangle *triangle1 = new Triangle(vertices);

	std::vector <float> vertices = {
	 0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f // top 
	};

	std::vector <unsigned int> indices = { // note that we start from 0!
		0, 1, 3,  // first triangle
		1,2,3 
	};
	
	float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};


	Mesh *mesh1 = new Mesh(vertices, indices);

	loopWindow(window, mesh1);
	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

void loopWindow(GLFWwindow* window, Mesh *mesh)
{
	Shader *shader = Shader::getInstance();
	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//render
		glClearColor(0.f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw triangle
		shader->use();
		//Update Color
		float timeValue = glfwGetTime();
    	float greenValue = sin(timeValue) / 2.0f + 0.5f;
    	int vertexColorLocation = glGetUniformLocation(shader->getShader(), "ourColor");
    	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    	glfwSwapBuffers(window);
    	glfwPollEvents();
	}
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Vertices → VBO → VAO → Shader → glDrawArrays → écran