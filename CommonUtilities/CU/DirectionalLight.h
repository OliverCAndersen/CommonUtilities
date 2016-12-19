#pragma once
#include "Vector.h"

namespace CommonUtilities
{
	class DirectionalLight
	{
	public:
		DirectionalLight();
		DirectionalLight(const Vector3f & aDirection, float aStrength, const Vector3f & aColor, const Vector3f & aSpecColor);
		DirectionalLight(const DirectionalLight & aDirLight);
		~DirectionalLight();

		const Vector3f & GetDirection() const;
		float GetStrength() const;
		const Vector3f & GetColor() const;
		const Vector3f & GetSpecularColor() const;

		void SetDirection(const Vector3f & aDirection);
		void SetStrength(float aStrength);
		void SetColor(const Vector3f & aColor);
		void SetSpecularColor(const Vector3f & aSpecColor);

	private:
		Vector3f myDirection;
		float myStrength;
		Vector3f myColor;
		Vector3f mySpecularColor;
	};
}

namespace CU = CommonUtilities;

