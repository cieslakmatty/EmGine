#include "Sprite.h"

namespace EmGine{

Sprite::Sprite() :
	m_vboID(0){
}

Sprite::~Sprite(){

	if (!m_vboID){

		glDeleteBuffers(1, &m_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height, std::string filePath){

	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_texture = ResourceManager::getTexture(filePath);
	if (!m_vboID){

		glGenBuffers(1, &m_vboID);
	}

	Vertex vertexData[6];
	vertexData[0].setPosition(m_x + m_width, m_y + m_height);
	vertexData[0].setUV(1.f, 1.f);
	vertexData[1].setPosition(m_x, m_y + m_height);
	vertexData[1].setUV(0.f, 1.f);
	vertexData[2].setPosition(m_x, m_y);
	vertexData[2].setUV(0.f, 0.f);
	vertexData[3].setPosition(m_x, m_y);
	vertexData[3].setUV(0.f, 0.f);
	vertexData[4].setPosition(m_x + m_width, m_y);
	vertexData[4].setUV(1.f, 0.f);
	vertexData[5].setPosition(m_x + m_width, m_y + m_height);
	vertexData[5].setUV(1.f, 1.f);

	for (int i = 0; i < 6; i++){

		vertexData[i].setColor(100, 0, 100, 255);
	}

	vertexData[1].setColor(0, 0, 200, 255);
	vertexData[4].setColor(255, 255, 100, 255);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw(){

	glBindTexture(GL_TEXTURE_2D, m_texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//color attrib pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//uv attrib pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}