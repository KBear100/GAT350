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

		glm::ivec2 GetSize() const { return { m_width, m_height }; }

	protected:
		int m_width = 0;
		int m_height = 0;
		GLuint m_fbo = 0;
		std::shared_ptr<Texture> m_texture;
	};
}