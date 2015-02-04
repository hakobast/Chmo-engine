#ifndef EngineTesting_Material_h
#define EngineTesting_Material_h

#include "GL_LIBS.h"
#include "Color.h"
#include "Texture2D.h"
#include "smart_pointer.h"

class Material :public RemovableObject
{
public:
	Material(std::string name) :name(name)
	{
		/*printf("MATERIAL created\n");*/ 
		color_ambient.set(0.2f,0.2f,0.2f,1.0f);
		color_diffuse.set(0.8f, 0.8f, 0.8f, 1.0f);
		color_specular.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void bind()
	{
		//glEnable(GL_TEXTURE_2D);

		if (!texture_ambient.isEmpty())
			texture_ambient->bindTexture();

		//TODO implement multi texturing

		glMaterialfv(GL_FRONT, GL_AMBIENT, color_ambient[0]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color_diffuse[0]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, color_specular[0]);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	void unbind()
	{
		//TODO check for solution
		if (!texture_ambient.isEmpty())
			texture_ambient->unbindTexture();

		//glDisable(GL_TEXTURE_2D);
	}

	std::string name;

	smart_pointer<Texture2D> texture_ambient;
	smart_pointer<Texture2D> texture_diffuse;
	smart_pointer<Texture2D> texture_specular;
	smart_pointer<Texture2D> texture_alpha;
	smart_pointer<Texture2D> texture_bump;

	Color color_ambient;
	Color color_diffuse;
	Color color_specular;

	GLint illum = 1;
	GLfloat shininess = 128.0f;
};
#endif