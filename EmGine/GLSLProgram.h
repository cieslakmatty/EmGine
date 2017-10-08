#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include "MyErrors.h"

namespace EmGine{

class GLSLProgram{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void addAttribute(const std::string& attributeName);
	void linkShaders();

	GLint getUniformLocation(const std::string uniformName);

	void use();
	void unuse();

private:
	void compileShader(const std::string shaderPath, GLuint id);

	GLuint m_programID,
		m_vertexShaderID,
		m_fragmentShaderID,
		m_numAttributes;
};

}