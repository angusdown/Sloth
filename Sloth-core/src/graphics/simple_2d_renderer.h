#pragma once
#ifndef SLOTH_SIMPLE2DRENDER_H_
#define SLOTH_SIMPLE2DRENDER_H_

#include <deque>
#include "renderer_2d.h"
#include "static_sprite.h"

namespace sloth { namespace graphics {
	
	class Simple2DRender: public Renderer2D
	{
	private:
		std::deque<const StaticSprite*> m_RenderQueue;
	public:
		void sumbit(const Renderable2D *renderable) override;
		void flush() override;
	};

} }
#endif // !SLOTH_SIMPLE2DRENDER_H_