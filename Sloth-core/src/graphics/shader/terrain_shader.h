/************************************************************************
* @project 		:  sloth
* @class   		:  TerrainShader
* @version 		:  v1.0.0
* @description	:  和地形着色器(terrain)的 uniform 变量相对应，用于修改着色器变量
* @author		:  Oscar Shen
* @creat 		:  2016年10月8日14:52:32
* @revise 		:  2017年2月9日14:53:47
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
*************************************************************************/
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

		int *m_LocLightPos;			// 灯光位置
		int *m_LocLightColor;		// 灯光颜色
		int *m_LocAttenuation;		// 灯光衰减

		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocSkyColor;
		int m_LocBackgroundTexture;
		int m_LocRTexture;
		int m_LocGTexture;
		int m_LocBTexture;
		int m_LocBlendMapTexture;


	public:
		~TerrainShader();
		static TerrainShader* inst();
		virtual void loadModelMatrix(const glm::mat4 &model) override;
		virtual void loadViewMatrix(const RawCamera &camera) override;
		virtual void loadProjectionMatrix(const glm::mat4 &projection) override;
		virtual void loadLight(const Light &light) override;

		/************************************************************************
		* @description	: 加载灯光相关的变量值——位置、颜色、衰减
		* @author		: Oscar Shen
		* @creat		: 2017年2月8日16:52:25
		***********************************************************************/
		virtual void loadLights(const std::vector<Light> &lights) override;

		virtual void loadShineVariable(const float shininess, const float reflectivity) override;
		virtual void loadSkyColor(const float r, const float g, const float b);
		virtual void connectTextureUnits();

	private:
		TerrainShader();

	protected:
		/***********************************************************************
		* @description	: 初始化时获取所有变量的 uniform location
		* @author		: Oscar Shen
		* @creat		: 2016年12月8日16:52:25
		***********************************************************************/
		virtual void getAllUniformLocation() override;
	};

} }


#endif // !SLOTH_TERRAIN_SHADER_H_
