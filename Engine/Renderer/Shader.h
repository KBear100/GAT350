#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace Bear
{
	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(std::string filename, ...) override;

	public:
		GLuint m_shader = 0;
	};
}