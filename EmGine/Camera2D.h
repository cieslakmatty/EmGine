#pragma once

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace EmGine{

class Camera2D{
public:
	Camera2D();
	~Camera2D();

	void init(int screenWidth, int screenHeight);
	void update();

	glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

	void setPosition(glm::vec2& newPosition);
	glm::vec2 getPosition();
	void setScale(float newScale);
	float getScale();
	glm::mat4 getCameraMatrix();

private:
	glm::vec2 m_position;
	glm::mat4 m_cameraMatrix,
		m_orthoMatrix;
	float m_scale;
	bool m_needsUpdate;
	int m_screenWidth,
		m_screenHeight;
};

}