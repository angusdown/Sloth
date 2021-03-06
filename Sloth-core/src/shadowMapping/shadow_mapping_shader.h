/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_SHADOW_MAPPING_SHADER_H_
#define SLOTH_SHADOW_MAPPING_SHADER_H_
#include <memory>
#include <shader/shader.h>
#include <shader/uniform.h>
namespace sloth {

#define SHADOW_MAPPING_VERTEX_FILE "src/shadowMapping/shadowMapping.vert"
#define SHADOW_MAPPING_FRAGMENT_FILE "src/shadowMapping/shadowMapping.frag"
	class ShadowMappingShader : public Shader
	{
	public:
		static std::shared_ptr<ShadowMappingShader> inst();
		UniformMatrix4 m_Model = UniformMatrix4("model");
		UniformMatrix4 m_LightSpace = UniformMatrix4("lightSpace");

		ShadowMappingShader();
	};

} 


#endif // SLOTH_SHADOW_MAPPING_SHADER_H_
