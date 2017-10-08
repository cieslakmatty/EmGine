#pragma once

#include <map>
#include <iostream>
#include "GLTexture.h"
#include "ImageLoader.h"

namespace EmGine{

class TextureCache{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string texturePath);

private:
	std::map<std::string, GLTexture> m_textureMap;
};

}