#include "water_shader.h"

namespace sloth { namespace graphics {

	WaterShader *WaterShader::m_Inst(nullptr);

	WaterShader * WaterShader::inst()
	{
		if (m_Inst == nullptr)
			m_Inst = new WaterShader();
		return m_Inst;
	}

	WaterShader::~WaterShader()
	{
		delete m_Inst;
	}

	WaterShader::WaterShader()
		:Shader(WATER_VERTEX_FILE, WATER_FRAGMENT_FILE)
	{
		getAllUniformLocation();
	}

	void WaterShader::getAllUniformLocation()
	{
		m_LocModel = glGetUniformLocation(m_ID, "model");
		m_LocView = glGetUniformLocation(m_ID, "view");
		m_LocProjection = glGetUniformLocation(m_ID, "projection");
	}

	void WaterShader::loadModelMatrix(const glm::mat4 & model)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void WaterShader::loadViewMatrix(const RawCamera &camera)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	}

	void WaterShader::loadProjectionMatrix(const glm::mat4 & projection)
	{
		glProgramUniformMatrix4fv(m_ID, m_LocProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}
} }