#include "GLSLProgram.h"

namespace EmGine{

GLSLProgram::GLSLProgram() :
	m_programID(0),
	m_vertexShaderID(0),
	m_fragmentShaderID(0),
	m_numAttributes(0){
}


GLSLProgram::~GLSLProgram(){}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){

	m_programID = glCreateProgram();
	if (!m_programID){

		fatalError("Program failed to be created");
	}
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!m_vertexShaderID){

		fatalError("Vertex shader failed to be created");
	}
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!m_fragmentShaderID){

		fatalError("Fragment shader failed to be created");
	}

	compileShader(vertexShaderFilePath, m_vertexShaderID);
	compileShader(fragmentShaderFilePath, m_fragmentShaderID);
}

void GLSLProgram::compileShader(const std::string shaderPath, GLuint id){

	//open the shader file
	std::ifstream shaderFile(shaderPath);
	if (shaderFile.fail()){

		perror(shaderPath.c_str());
		fatalError("Failed to open: \"" + shaderPath + "\"");
	}
	//read the shader file
	std::string fileContents = "",
		line;
	while (std::getline(shaderFile, line)){

		fileContents += "\n" + line;
	}
	shaderFile.close();
	//compilation
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);
	//error checking
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success){

		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Shader with: \"" + shaderPath + "\" file path failed to compile");
	}
}

void GLSLProgram::addAttribute(const std::string& attributeName){

	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

void GLSLProgram::linkShaders(){

	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	glLinkProgram(m_programID);

	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (!isLinked){

		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(m_programID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Program failed to link");
	}

	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

GLint GLSLProgram::getUniformLocation(const std::string uniformName){

	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	if (GL_INVALID_INDEX == location){

		fatalError("Uniform: \"" + uniformName + "\" not found in shader.");
	}
	return location;
}

void GLSLProgram::use(){

	glUseProgram(m_programID);
	for (unsigned int i = 0; i < m_numAttributes; i++){

		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse(){

	glUseProgram(0);
	for (unsigned int i = 0; i < m_numAttributes; i++){

		glDisableVertexAttribArray(i);
	}
}

}