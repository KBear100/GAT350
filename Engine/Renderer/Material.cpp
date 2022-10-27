#include "Material.h" 
#include "Engine.h" 

namespace Bear
{
	bool Material::Create(std::string filename, ...)
	{
		// load program json document 
		rapidjson::Document document;
		bool success = Bear::json::Load(filename, document);
		if (!success)
		{

			LOG("Could not load program file (%s).", filename.c_str());
			return false;
		}

		// read the program name 
		std::string program;
		READ_DATA(document, program);
		// get program resource 
		m_program = Bear::g_resources.Get<Bear::Program>(program);

		// read the texture name 
		std::string texture;
		READ_DATA(document, texture);
		if (!texture.empty())
		{
			// get texture resource 

			m_textures.push_back(Bear::g_resources.Get<Bear::Texture>(texture));
		}

		// read colors 
		READ_DATA(document, color);
		READ_DATA(document, shininess);

		return true;
	}

	void Material::Bind()
	{
		m_program->Use();
		m_program->SetUniform("material.color", color);
		m_program->SetUniform("material.shininess", shininess);

		for (auto& texture : m_textures)
		{
			texture->Bind();
		}
	}
}