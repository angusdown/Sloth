#include "shader.h"

#include <iostream>

namespace sloth {
	Shader::Shader(const char * vertexPath, const char * fragmentPath, const char * geometryPath)
	{
		std::cout << "vertexPath : " << vertexPath << std::endl;
		std::cout << "fragmentPath : " << fragmentPath << std::endl;
		if (geometryPath != nullptr)
			std::cout << "geometryPath : " << geometryPath << std::endl;
		compile(loadStringFromFile(vertexPath).c_str(),
			loadStringFromFile(fragmentPath).c_str(),
			geometryPath == nullptr ? nullptr : loadStringFromFile(geometryPath).c_str());
	}
	void Shader::compile(const char * vertexSource, const char * fragmentSource, const char * geometrySource)
	{
		if (vertexSource == nullptr)
			std::cout << "vertex load fail!" << std::endl;
		if (fragmentSource == nullptr)
			std::cout << "fragment load fail!" << std::endl;
		if (geometrySource == nullptr)
			std::cout << "geometry load fail!" << std::endl;

		GLuint sVertex, sFragment, gShader;
		// Vertex Shader
		sVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(sVertex, 1, &vertexSource, NULL);
		glCompileShader(sVertex);
		checkCompileErrors(sVertex, "VERTEX");
		// Fragment Shader
		sFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sFragment, 1, &fragmentSource, NULL);
		glCompileShader(sFragment);
		checkCompileErrors(sFragment, "FRAGMENT");
		// If geometry shader source code is given, also compile geometry shader
		if (geometrySource != nullptr)
		{
			gShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(gShader, 1, &geometrySource, NULL);
			glCompileShader(gShader);
			checkCompileErrors(gShader, "GEOMETRY");
		}
		// Shader Program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, sVertex);
		glAttachShader(m_ID, sFragment);
		if (geometrySource != nullptr)
			glAttachShader(m_ID, gShader);
		glLinkProgram(m_ID);
		checkCompileErrors(m_ID, "PROGRAM");
		// Delete the shaders as they're linked into our m_ID now and no longer necessery
		glDeleteShader(sVertex);
		glDeleteShader(sFragment);
		if (geometrySource != nullptr)
			glDeleteShader(gShader);
	}

	void Shader::storeAllUniformLocation(std::vector<Uniform*> &uniforms)
	{
		for (auto item : uniforms) {
			item->storeUniformLocation(m_ID);
		}
		glValidateProgram(m_ID);
	}

	void Shader::loadFloat(const char *name, float value)
	{
		glProgramUniform1f(m_ID, glGetUniformLocation(this->m_ID, name), value);
	}
	void Shader::loadInteger(const char *name, int value)
	{
		glProgramUniform1i(m_ID, glGetUniformLocation(this->m_ID, name), value);
	}
	void Shader::loadVector2f(const char *name, float x, float y)
	{
		glProgramUniform2f(m_ID, glGetUniformLocation(this->m_ID, name), x, y);
	}
	void Shader::loadVector2f(const char *name, const glm::vec2 &value)
	{
		glProgramUniform2f(m_ID, glGetUniformLocation(this->m_ID, name), value.x, value.y);
	}
	void Shader::loadVector3f(const char *name, float x, float y, float z)
	{
		glProgramUniform3f(m_ID, glGetUniformLocation(this->m_ID, name), x, y, z);
	}
	void Shader::loadVector3f(const char *name, const glm::vec3 &value)
	{
		glProgramUniform3f(m_ID, glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z);
	}
	void Shader::loadVector4f(const char *name, float x, float y, float z, float w)
	{
		glProgramUniform4f(m_ID, glGetUniformLocation(this->m_ID, name), x, y, z, w);
	}
	void Shader::loadVector4f(const char *name, const glm::vec4 &value)
	{
		glProgramUniform4f(m_ID, glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z, value.w);
	}
	void Shader::loadMatrix4(const char *name, const glm::mat4 &matrix)
	{
		glProgramUniformMatrix4fv(m_ID, glGetUniformLocation(this->m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::loadMatrix4(int location, const glm::mat4 & matrix)
	{
		glProgramUniformMatrix4fv(m_ID, location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::checkCompileErrors(const GLuint shader, const std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
	}
} 