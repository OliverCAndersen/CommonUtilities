#include "DirectionalLight.h"

namespace CommonUtilities
{
	DirectionalLight::DirectionalLight()
		: myDirection({ 0.0f, 0.0f, 1.0f })
		, myStrength(1.0f)
		, myColor({ 1.0f, 1.0f, 1.0f })
		, mySpecularColor({ 1.0f, 1.0f, 1.0f })
	{
		
	}

	DirectionalLight::DirectionalLight(const Vector3f & aDirection, float aStrength, const Vector3f & aColor, const Vector3f & aSpecColor)
		: myDirection(aDirection)
		, myStrength(aStrength)
		, myColor(aColor)
		, mySpecularColor(aSpecColor)
	{
		
	}

	DirectionalLight::DirectionalLight(const DirectionalLight & aDirLight)
	{
		myDirection = aDirLight.myDirection;
		myStrength = aDirLight.myStrength;
		myColor = aDirLight.myColor;
		mySpecularColor = aDirLight.mySpecularColor;
	}

	DirectionalLight::~DirectionalLight()
	{
	}
	const Vector3f & DirectionalLight::GetDirection() const
	{
		return myDirection;
	}
	float DirectionalLight::GetStrength() const
	{
		return myStrength;
	}
	const Vector3f & DirectionalLight::GetColor() const
	{
		return myColor;
	}
	const Vector3f & DirectionalLight::GetSpecularColor() const
	{
		return mySpecularColor;
	}

	void DirectionalLight::SetDirection(const Vector3f & aDirection)
	{
		myDirection = aDirection;
	}

	void DirectionalLight::SetStrength(float aStrength)
	{
		myStrength = aStrength;
	}

	void DirectionalLight::SetColor(const Vector3f & aColor)
	{
		myColor = aColor;
	}

	void DirectionalLight::SetSpecularColor(const Vector3f & aSpecColor)
	{
		mySpecularColor = aSpecColor;
	}
}
