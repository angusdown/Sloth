/************************************************************************
 * @project 	:  sloth
 * @class   	:  Loader
 * @version 	:  v1.0.0
 * @description :  ���е�VAO����Ҫ�� Loader ���������� OpenGL������֮�����е�
				   RawModel ֻ���� Loader ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��13��21:54:09
 * @revise 		:
************************************************************************
 * Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_LOADER_H_
#define SLOTH_LOADER_H_

#include <sloth.h>
#include <buffers/index_buffer.h>
#include <buffers/vertex_array.h>
#include <model/raw_model.hpp>
#include <model/model_data.hpp>
#include <config/header.hpp>

namespace sloth {

	class Loader
	{
	private:
		std::vector<VertexArray*> m_Vaos1;
		std::vector<unsigned int> m_Textures;
		std::vector<unsigned int> m_Vbos;

	public:
		Loader() {}
		~Loader();

		/************************************************************************
		* @description	: ����3άλ�á�2ά������3ά���������Լ���������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:00:40
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords,
			std::vector<glm::vec3> &normals,
			std::vector<unsigned int> &indices
		);

		/************************************************************************
		* @description	: ����3άλ�á�2ά����
		* @author		: Oscar Shen
		* @creat		: 2017��3��2��11:14:40
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords
		);

		/************************************************************************
		* @description	: ����2άλ�á�2ά����������VAO���
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��22:03:05
		***********************************************************************/
		unsigned int loadToVAO(
			std::vector<float> &positions,
			std::vector<float> &texCoords
			);


		/************************************************************************
		* @description	: ����3άλ�á�2ά������3ά��������3ά���������Լ���������
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:00:40
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords,
			std::vector<glm::vec3> &normals,
			std::vector<glm::vec3> &tangents,
			std::vector<unsigned int> &indices
		);

		/************************************************************************
		* @description	: ����һ��ֻ����vec2λ�ú�������RawModel����Ҫ���ڽ�����άGUI����
		* @author		: Oscar Shen
		* @creat		: 2017��2��9��14:03:57
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec2> &positions,
			std::vector<glm::vec2> &texCoords
		);

		/************************************************************************
		* @description	: ����һ��ֻ����vec3λ�õ�RawModel
		* @author		: Oscar Shen
		* @creat		: 2017��2��9��14:03:57
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions
		);

		/************************************************************************
		* @description	: ����һ��ֻ����dimentionλ�õ�RawModel
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:56:46
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<float> &position,
			int dimention
		);

		/************************************************************************
		* @description	: ����һ��ָ����С�� vbo����Сָ���󲻿ɱ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:04:37
		***********************************************************************/
		unsigned int createEmptyVbo(unsigned int floatCount);

		/************************************************************************
		* @description	: ����ʵ����Ⱦ������������֯
						  vao : ��Ҫ�����ݰ󶨵��� vao
						  vbo : �洢ʵ�����ݵĻ���
						  attribute : ��ǰ��֯�����Ա��
						  dataSize : vao �����Զ�Ӧ��������С��vec2->2��vec4->4
						  instancedDataLength : ����ʵ���������ݳ���
						  offset : ����������������е��ֽ���ʼλ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:09:40
		***********************************************************************/
		void addIntancedAttribute(unsigned int vao, unsigned int vbo, unsigned int attribute,
			unsigned int dataSize, unsigned int instancedDataLength, unsigned int offset);

		/************************************************************************
		* @description	: ����֯�õ����ݵ��� vbo
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:10:16
		***********************************************************************/
		void updateVbo(unsigned int vbo, std::vector<float> &vboData);

		/************************************************************************
		* @description	: ���ض�ά����
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:56:46
		***********************************************************************/
		unsigned int loadTexture(const std::string &fileName, bool alpha = false);

		/************************************************************************
		* @description	: ��������������
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��18:56:46
		***********************************************************************/
		unsigned int loadCubeMap(const std::vector<std::string> &cubeMapPaths, bool alpha = false);

		/************************************************************************
		* @description	: �����ǰ Loader ���ص�������Դ
		* @author		: Oscar Shen
		* @creat		: 2017��2��16��10:02:02
		***********************************************************************/
		void cleanUp();

	private:
		VertexArray* createVAO();

		unsigned int setupTexture(int width, int height, unsigned char *data, bool alpha);
	};


}


#endif // !SLOTH_LOADER_H_