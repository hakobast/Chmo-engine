
#include "Material.h"
#include "CoreEngine/LIBS.h"
#include "Extras/smart_pointer.h"
#include "Extras/Color.h"

smart_pointer<Material> Material::Diffuse()
{
	smart_pointer<Material> mat = createMaterial("diffuse",
		"C:/Program Files (x86)/OpenGL Shader Designer/My/BumpedDiffuse.vert",
		"C:/Program Files (x86)/OpenGL Shader Designer/My/BumpedDiffuse.frag");

	mat->color_specular  = Color::BLACK;
	mat->color_emmission = Color::BLACK;

	return mat;
}

smart_pointer<Material> Material::Unlit()
{
	smart_pointer<Material> mat = createMaterial("diffuse",
		"C:/Program Files (x86)/OpenGL Shader Designer/My/UnlitSprite.vert",
		"C:/Program Files (x86)/OpenGL Shader Designer/My/UnlitSprite.frag");

	mat->color_ambient   = Color::WHITE;
	mat->color_diffuse   = Color::BLACK;
	mat->color_specular  = Color::BLACK;
	mat->color_emmission = Color::BLACK;

	return mat;
}

smart_pointer<Material> Material::createMaterial(std::string name, const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	smart_pointer<ShaderProgram> shader = smart_pointer<ShaderProgram>(new ShaderProgram());
	shader->loadShaderFromFile(GL_VERTEX_SHADER_ARB, vertexShaderFilename);
	shader->loadShaderFromFile(GL_FRAGMENT_SHADER_ARB, fragmentShaderFilename);
	shader->createAndLinkProgram();

	return smart_pointer<Material>(new Material(name, shader));
}