#include "skybox_renderer.h"

namespace sloth {
	float SkyboxRenderer::m_Size = 100.0f;
	std::vector<glm::vec3> SkyboxRenderer::m_Vertices = {
		glm::vec3(-m_Size,  m_Size, -m_Size),
		glm::vec3(-m_Size, -m_Size, -m_Size),
		glm::vec3(m_Size, -m_Size, -m_Size),
		glm::vec3(m_Size, -m_Size, -m_Size),
		glm::vec3(m_Size,  m_Size, -m_Size),
		glm::vec3(-m_Size,  m_Size, -m_Size),

		glm::vec3(-m_Size, -m_Size,  m_Size),
		glm::vec3(-m_Size, -m_Size, -m_Size),
		glm::vec3(-m_Size,  m_Size, -m_Size),
		glm::vec3(-m_Size,  m_Size, -m_Size),
		glm::vec3(-m_Size,  m_Size,  m_Size),
		glm::vec3(-m_Size, -m_Size,  m_Size),

		glm::vec3(m_Size, -m_Size, -m_Size),
		glm::vec3(m_Size, -m_Size,  m_Size),
		glm::vec3(m_Size,  m_Size,  m_Size),
		glm::vec3(m_Size,  m_Size,  m_Size),
		glm::vec3(m_Size,  m_Size, -m_Size),
		glm::vec3(m_Size, -m_Size, -m_Size),

		glm::vec3(-m_Size, -m_Size,  m_Size),
		glm::vec3(-m_Size,  m_Size,  m_Size),
		glm::vec3(m_Size,  m_Size,  m_Size),
		glm::vec3(m_Size,  m_Size,  m_Size),
		glm::vec3(m_Size, -m_Size,  m_Size),
		glm::vec3(-m_Size, -m_Size,  m_Size),

		glm::vec3(-m_Size,  m_Size, -m_Size),
		glm::vec3(m_Size,  m_Size, -m_Size),
		glm::vec3(m_Size,  m_Size,  m_Size),
		glm::vec3(m_Size,  m_Size,  m_Size),
		glm::vec3(-m_Size,  m_Size,  m_Size),
		glm::vec3(-m_Size,  m_Size, -m_Size),

		glm::vec3(-m_Size, -m_Size, -m_Size),
		glm::vec3(-m_Size, -m_Size,  m_Size),
		glm::vec3(m_Size, -m_Size, -m_Size),
		glm::vec3(m_Size, -m_Size, -m_Size),
		glm::vec3(-m_Size, -m_Size,  m_Size),
		glm::vec3(m_Size, -m_Size,  m_Size) };

	SkyboxRenderer::SkyboxRenderer(Loader &loader, const glm::mat4 & projection)
	{
		SkyboxShader::inst()->loadProjectionMatrix(projection);
		m_Cube = loader.loadToVAO(m_Vertices);
	}

	void SkyboxRenderer::render(unsigned int cubeMapID, const RawCamera & camera)
	{
		auto shader = SkyboxShader::inst();
		shader->enable();
		shader->loadViewMatrix(camera);
		glBindVertexArray(m_Cube.getVaoID());
		glEnableVertexAttribArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
		// ֻ����û���κ�����ɼ����������պвŻᱻ��Ⱦ
		// ����������ԭ�򣬿���Զƽ�沿�ֵ�ƬԪ���Իᷢ����ͻ
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, m_Cube.getVertexCount());
		glDepthFunc(GL_LESS);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		shader->disable();
	}

} 