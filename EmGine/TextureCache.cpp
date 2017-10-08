#include "TextureCache.h"

namespace EmGine{

TextureCache::TextureCache(){}

TextureCache::~TextureCache(){}

GLTexture TextureCache::getTexture(std::string texturePath){

	std::map<std::string, GLTexture>::iterator mit = m_textureMap.find(texturePath);
	if (m_textureMap.end() == mit){

		GLTexture newTexture = ImageLoader::Instance()->loadPNG(texturePath);
		m_textureMap.insert(make_pair(texturePath, ImageLoader::Instance()->loadPNG(texturePath)));
		return newTexture;
	}
	return mit->second;
}

}