#include "ImageLoader.h"

namespace EmGine{

ImageLoader* ImageLoader::m_pInstance = NULL;

ImageLoader* ImageLoader::Instance(){

	if (!m_pInstance){

		m_pInstance = new ImageLoader;
	}
	return m_pInstance;
}

GLTexture ImageLoader::loadPNG(std::string filePath){

	GLTexture texture = {};
	std::vector<unsigned char> in,
		out;
	unsigned long width,
		height;
	if (!IOManager::Instance()->readFileToBuffer(filePath, in)){

		fatalError("Failed to load PNG file to buffer");
	}
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (0 != errorCode){

		fatalError("decodePNG failed with error: " + std::to_string(errorCode));
	}

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;
	return texture;
}

}