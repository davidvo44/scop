#include "../header/mesh.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices)
{
    _vertices = vertices;
    _indices = indices;
    initMesh();
}

Mesh::~Mesh()
{
}

unsigned int  Mesh::getVBO()
{
    return _VBO;
}

unsigned int  Mesh::getVAO()
{
    return _VAO;
}

unsigned int  Mesh::getEBO()
{
    return _EBO;
}

void Mesh::initMesh()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    // 1. bind Vertex Array Object
glBindVertexArray(_VAO);
// 2. copy our vertices array in a vertex buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, _VBO);
glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
// 3. copy our index array in a element buffer for OpenGL to use
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);
// 4. then set the vertex attributes pointers

//position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);  


//color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);

}


/*
    VBO est essentiellement un tableau de données stockées pour chaque sommet. 
    EBO est un tableau de données qui décrit comment chaque élément (c'est-à-dire un triangle) est construit.
    VAO regroupent tous ces tampons (comme un conteneur de pointeurs) et vous permettent de les utiliser plus facilement. 

    Les VBO ne sont pas nécessairement de simples triangles, si vous le souhaitez, vous pouvez stocker plusieurs maillages dans un seul VBO 
    et définir les indices corrects pour le dessin et ils auront la même apparence que plusieurs VBO séparés. 
*/