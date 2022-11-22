#pragma once
#include "Resource/ResourceManager.h"
#include "Renderer.h"

namespace Bear
{
	class Texture;

	class Framebuffer : public Resource
	{
	public:
		~Framebuffer();

		bool Create(std::string filename, ...) override;
		bool CreateFramebuffer();
		bool CreateDepthbuffer(int width, int height);

		void Bind();
		void Unbind();

	protected:
		GLuint m_fbo = 0;
		std::shared_ptr<Texture> m_texture;
	};
}