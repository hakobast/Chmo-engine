#ifndef EngineTesting_Material_h
#define EngineTesting_Material_h

#include <GL\glut.h>
#include "Color.h"
#include "Texture2D.h"
#include "smart_pointer.h"

class Material :public RemovableObject
{
public:
	Material(std::string name) :name(name){ /*printf("MATERIAL created\n");*/ };

	std::string name;

	std::string ambient_texture_path;
	std::string diffuse_texture_path;
	std::string specular_texture_path;
	std::string alpha_texture_path;
	std::string bump_texture_path;

	smart_pointer<Texture2D> texture_ambient;
	smart_pointer<Texture2D> texture_diffuse;
	smart_pointer<Texture2D> texture_specular;
	smart_pointer<Texture2D> texture_alpha;
	smart_pointer<Texture2D> texture_bump;

	Color color_ambient;
	Color color_diffuse;
	Color color_specular;

	GLint illum = 1;
	GLfloat shininess; //TODO set defualt value
	GLfloat transparency = 1.0f;

};
#endif