#ifndef LIGHT_H
#define LIGHT_H

#include "../CoreEngine/GameLogic.h"
#include "../CoreEngine/LIBS.h"

enum LightType
{
	DIRECTIONAL,
	POSITIONAL,
	SPOT
};

class Light : public GameLogic
{
private:
	int _light = 0; //TEMP
	LightType _type;
	Color _color_ambient;
	Color _color_diffuse;
	Color _color_specular;
	GLfloat _spotCutoff = 180.0f;
	GLfloat _spotExponent = 0.0f;
	GLfloat _constAttenuation = 0.0f;
	GLfloat _linearAttenuation = 1.0f;
	GLfloat _quadraticAttenuation = 0.0f;
	GLfloat* v;

	void Create();
	void Init();
	void Update();
	void OnDisable();
	void OnEnable();
	void OnDestroy();

public:
	void setLight(int l);
	void setLightType(LightType type);
	void setAmbient(Color c);
	void setDiffuse(Color c);
	void setSpecular(Color c);
	//Range[0,180]
	void setSpotCutoff(float value);
	void setSpotExponent(float value);
	void setConstAttenuation(float value);
	void setLinearAttenuation(float value);
	void setQuadraticAttenuation(float value);
};

inline void Light::setLight(int l)
{
	glDisable(GL_LIGHT0 + _light);
	glEnable(GL_LIGHT0 + l);
	_light = l;

	setAmbient(Color(0.2f, 0.2f, 0.2f));
	setDiffuse(Color(0.5f, 0.5f, 0.5f));
	setSpecular(Color(0.0f, 0.0f, 0.0f));
}

inline void Light::setLightType(LightType type)
{
	_type = type;

	switch (_type)
	{
	case DIRECTIONAL:
		//glLightfv(GL_LIGHT0 + _light, GL_POSITION, new float[]{0.0f, 0.0f, 1.0f, 0.0f});
		break;
	case POSITIONAL:
		setLinearAttenuation(1.0f);
		//glLightfv(GL_LIGHT0 + _light, GL_POSITION, new float[]{0.0f, 0.0f, 0.0f, 1.0f});
		break;
	case SPOT:
		//setLinearAttenuation(0.2f);
		//glLightfv(GL_LIGHT0 + _light, GL_POSITION, new float[]{0.0f, 0.0f, 0.0f, 1.0f});
		break;
	}
}

inline void Light::setAmbient(Color c)
{
	_color_ambient = c;
	glLightfv(GL_LIGHT0 + _light, GL_AMBIENT, _color_ambient[0]);
}

inline void Light::setDiffuse(Color c)
{
	_color_diffuse = c;
	glLightfv(GL_LIGHT0 + _light, GL_DIFFUSE, _color_diffuse[0]);
}

inline void Light::setSpecular(Color c)
{
	_color_specular = c;
	glLightfv(GL_LIGHT0 + _light, GL_SPECULAR, _color_specular[0]);
}

inline void Light::setSpotCutoff(float value)
{
	value = value > 180.0f ? 180.0f : value;
	value = value < 0.0f ? 0.0f : value;
	
	_spotCutoff = value;
	glLightf(GL_LIGHT0 + _light, GL_SPOT_CUTOFF, _spotCutoff);
}

inline void Light::setSpotExponent(float value)
{
	_spotExponent = value;
	glLightf(GL_LIGHT0 + _light, GL_SPOT_EXPONENT, _spotExponent);
}

inline void Light::setConstAttenuation(float value)
{
	_constAttenuation = value;
	glLightf(GL_LIGHT0 + _light, GL_CONSTANT_ATTENUATION, _constAttenuation);
}

inline void Light::setLinearAttenuation(float value)
{
	_linearAttenuation = value;
	glLightf(GL_LIGHT0 + _light, GL_LINEAR_ATTENUATION, _linearAttenuation);
}

inline void Light::setQuadraticAttenuation(float value)
{
	_quadraticAttenuation = value;
	glLightf(GL_LIGHT0 + _light, GL_QUADRATIC_ATTENUATION, _quadraticAttenuation);
}

#endif