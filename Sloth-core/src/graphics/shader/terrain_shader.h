#pragma once
#ifndef SLOTH_TERRAIN_SHADER_H_
#define SLOTH_TERRAIN_SHADER_H_

#include "shader.h"
#include "../setup/macro.h"

namespace sloth { namespace graphics {

	class TerrainShader : public Shader
	{
	private:
		static TerrainShader *m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;
		int *m_LocLightPos;
		int *m_LocLightColor;
		float m_LocShininess;
		float m_LocReflectivity;

	public:
		~TerrainShader();
		static TerrainShader* inst();
		virtual void loadModelMatrix(const glm::mat4 &model) override;
		virtual void loadViewMatrix(const Camera &camera) override;
		virtual void loadProjectionMatrix(const glm::mat4 &projection) override;
		virtual void loadLights(const std::vector<Light> &lights) override;
		virtual void loadShineVariable(const float shininess, const float reflectivity) override;

	private:
		TerrainShader();
		void getAllUniformLocation();
	};

} }


#endif // !SLOTH_TERRAIN_SHADER_H_