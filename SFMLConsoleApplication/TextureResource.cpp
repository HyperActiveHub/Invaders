#include "TextureResource.h"



TextureResource::TextureResource(std::string filename, sf::Texture texture) : 
	mTexture(texture),
	mFilename(filename)
{

}

Texture& TextureResource::getTexture()
{
	return mTexture;
}

string TextureResource::getFilename()	//Unused?
{
	return mFilename;
}

TextureResource::~TextureResource()
{

}
