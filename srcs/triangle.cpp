#include "../header/triangle.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

Triangle::Triangle(const float argVertices[9])
{
    for (int i = 0; i < 9; i++)
    {
        _vertices[i] = argVertices[i];
    }
    initTriangle();
}

Triangle::~Triangle()
{
}

unsigned int  Triangle::getVBO()
{
    return _VBO;
}

unsigned int  Triangle::getVAO()
{
    return _VAO;
}

void Triangle::initTriangle()
{
    glGenVertexArrays(1, &_VAO);  //Create Vertex array Object Name
	glGenBuffers(1, &_VBO);  // Create Buffer Object Name
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO); //bind a named buffer object (GL_ARRAY_BUFFER:Vertex attributes)
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW); //creates and initializes a buffer object's data store

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //define an array of generic vertex attribute data

    glEnableVertexAttribArray(0);
    
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}