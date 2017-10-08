#pragma once

#include <string>
#include "GLTexture.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "MyErrors.h"

namespace EmGine{

class ImageLoader{
public:
	static ImageLoader* Instance();
	GLTexture loadPNG(std::string filePath);

private:
	ImageLoader(){};
	ImageLoader(ImageLoader const&){};
	ImageLoader& operator=(ImageLoader const&){};

	static ImageLoader* m_pInstance;
};

}