#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

#include <vector>

class Triangle
{
public:
	Triangle(const float argVertices[9]);
	~Triangle();
    unsigned int  getVBO();
    unsigned int  getVAO();


private:
	void initTriangle();
    float _vertices[9];
    unsigned int _VBO; //Vertex array Object Name
    unsigned int _VAO; //Buffer Object Name
    unsigned int _EBO;
};

#endif