#pragma once
#include "SFML\Graphics.hpp"
#include <string>

using namespace sf;
using namespace std;

class TextureResource
{
public:
	TextureResource(std::string filename, Texture texture);
	Texture& getTexture();
	string getFilename();
private:
	Texture mTexture;
	string mFilename;
};

