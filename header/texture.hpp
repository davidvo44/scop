#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <iostream>
#include <vector>

class Texture
{
public:
	Texture(std::string fileName);
	~Texture();


private:
    unsigned int _texture;
    void loadTextute(std::string fileName);
};

#endif