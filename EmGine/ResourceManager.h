#pragma once

#include <string>
#include "TextureCache.h"

namespace EmGine{

class ResourceManager{

public:
	static GLTexture getTexture(std::string texturePath);

private:
	static TextureCache m_textureCache;
};

}