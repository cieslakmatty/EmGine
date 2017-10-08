#pragma once

#include <cstddef>
#include <string>
#include <GL/glew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include "ResourceManager.h"

namespace EmGine{

class Sprite{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string filePath);
	void draw();

private:
	float m_x,
		m_y,
		m_width,
		m_height;

	GLuint m_vboID;
	GLTexture m_texture;
};

}