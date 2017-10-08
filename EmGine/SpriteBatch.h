#pragma once

#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"

namespace EmGine{

enum class GlyphSortType{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph{
public:
	Glyph();
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color) :
		texture(Texture), depth(Depth){

		topLeft.setColor(color);
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.setColor(color);
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		topRight.setColor(color);
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomRight.setColor(color);
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	}

	GLuint texture;
	float depth;
	Vertex topLeft,
		bottomLeft,
		topRight,
		bottomRight;
};

class RenderBatch{
public:
	RenderBatch(GLuint aOffset, GLuint aNumOfVertices, GLuint aTexture) :
		offset(aOffset),
		numVertices(aNumOfVertices),
		texture(aTexture){}
	GLuint offset,
		numVertices,
		texture;
};

class SpriteBatch{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
	void renderBatch();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareoBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint m_vbo,
		m_vao;
	std::vector<Glyph> m_glyphs; //actual glyphs
	std::vector<Glyph*> m_glyphPointers; //used for sorting
	GlyphSortType m_sortType;
	std::vector<RenderBatch> m_renderBatches;
};

}