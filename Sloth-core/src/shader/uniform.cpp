#include "uniform.h"

sloth::Uniform::Uniform(const std::string & name)
	:m_Name(name)
{
}

void sloth::Uniform::storeUniformLocation(unsigned int programID)
{
	m_ProgramID = programID;
	m_Location = glGetUniformLocation(programID, m_Name.c_str());
	if (m_Location == NOT_FOUND)
		printf("No uniform variable called %s found!", m_Name.c_str());
}

sloth::UniformBool::UniformBool(const std::string & name)
	: Uniform(name)
{
}

void sloth::UniformBool::loadBool(bool b)
{
	if (!m_Used || m_CurrentBool != b)
	{
		glProgramUniform1f(Uniform::getLocation(), Uniform::getLocation(), b ? 1.0f : 0.0f);
		m_Used = true;
		m_CurrentBool = b;
	}
}

sloth::UniformFloat::UniformFloat(const std::string & name)
	:Uniform(name)
{
}

void sloth::UniformFloat::loadFloat(float value)
{
	if (!m_Used || m_CurrentValue != value) {
		glProgramUniform1f(Uniform::getProgramID(), Uniform::getLocation(), value);
		m_Used = true;
		m_CurrentValue = value;
	}
}

sloth::UniformMatrix4::UniformMatrix4(const std::string &name)
	:Uniform(name)
{
}

void sloth::UniformMatrix4::loadMatrix4(const glm::mat4 & matrix)
{
	glProgramUniformMatrix4fv(Uniform::getProgramID(), Uniform::getLocation(), 1, GL_FALSE, glm::value_ptr(matrix));
}

sloth::UniformSampler::UniformSampler(const std::string & name)
	:Uniform(name)
{
}

void sloth::UniformSampler::loadTexUnit(int texUnit)
{
	if (!m_Used || m_CurrentValue != texUnit) {
		glProgramUniform1i(Uniform::getProgramID(), Uniform::getLocation(), texUnit);
		m_Used = true;
		m_CurrentValue = texUnit;
	}
}

sloth::UniformVec2::UniformVec2(const std::string & name)
	:Uniform(name)
{
}

void sloth::UniformVec2::loadVec2(const glm::vec2 & vector)
{
	loadVec2(vector.x, vector.y);
}

void sloth::UniformVec2::loadVec2(float x, float y)
{
	if (!m_Used || x != m_X || y != m_Y) {
		glProgramUniform2f(Uniform::getProgramID(), Uniform::getLocation(), x, y);
		m_X = x;
		m_Y = y;
		m_Used = true;
	}
}

sloth::UniformVec3::UniformVec3(const std::string & name)
	:Uniform(name)
{
}

void sloth::UniformVec3::loadVec3(const glm::vec3 & vector)
{
	loadVec3(vector.x, vector.y, vector.z);
}

void sloth::UniformVec3::loadVec3(float x, float y, float z)
{
	if (!m_Used || x != m_X || y != m_Y || z != m_Z) {
		m_X = x;
		m_Y = y;
		m_Z = z;
		m_Used = true;
		glProgramUniform3f(Uniform::getProgramID(), Uniform::getLocation(), m_X, m_Y, m_Z);
	}
}

sloth::UniformVec4::UniformVec4(const std::string & name)
	: Uniform(name)
{
}

void sloth::UniformVec4::loadVec4(const glm::vec4 & vector)
{
	loadVec4(vector.x, vector.y, vector.z, vector.w);
}

void sloth::UniformVec4::loadVec4(float x, float y, float z, float w)
{
	if (!m_Used || m_X != x || m_Y != y || m_Z != z) {
		m_X = x;
		m_Y = y;
		m_Z = z;
		m_W = w;
		glProgramUniform4f(Uniform::getProgramID(), Uniform::getLocation(), x, y, z, w);
		m_Used = true;
	}
}
