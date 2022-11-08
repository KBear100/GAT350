#pragma once
#include "Framework/Component.h"

namespace Bear
{
	class LightComponent : public Component
	{
	public:
		enum class Type
		{
			Point,
			Directional,
			Spot
		};

		CLASS_DECLARATION(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Type type = Type::Point;
		float cutoff = 45.0f;
		float exponent = 50.0f;
		glm::vec3 color{ 0 };
	};
}