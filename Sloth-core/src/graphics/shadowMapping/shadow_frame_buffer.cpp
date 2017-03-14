#include "shadow_frame_buffer.h"

namespace sloth { namespace graphics {
	ShadowFrameBuffer::ShadowFrameBuffer(int width, int height)
		: FrameBuffer(), m_Width(width), m_Height(height)
	{
		initialiseFrameBuffer();
	}

	void ShadowFrameBuffer::bindShadowFrameBuffer()
	{
		FrameBuffer::bind(m_Width, m_Height);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void ShadowFrameBuffer::initialiseFrameBuffer()
	{
		FrameBuffer::addDepthTextureAttachment(m_Width, m_Height);
		glTextureParameteri(m_DepthTextureAttachment, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_DepthTextureAttachment, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_DepthTextureAttachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_DepthTextureAttachment, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glNamedFramebufferDrawBuffer(m_ID, GL_NONE);
		glNamedFramebufferReadBuffer(m_ID, GL_NONE);
	}

} }