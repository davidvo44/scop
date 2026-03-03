#ifndef MESH_HPP
# define MESH_HPP

#include <vector>

class Mesh
{
public:
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
	~Mesh();
    unsigned int  getVBO();
    unsigned int  getVAO();
    unsigned int  getEBO();


private:
	void initMesh();
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
    unsigned int _VBO; //Vertex array Object Name
    unsigned int _VAO; //Buffer Object Name
    unsigned int _EBO;
};

#endif