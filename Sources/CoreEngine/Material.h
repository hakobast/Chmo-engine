#ifndef EngineTesting_Material_h
#define EngineTesting_Material_h

#include <vector>

#include "LIBS.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/Color.h"


class Material :public RemovableObject
{
friend class Renderer;
private:
	std::vector<smart_pointer<Texture2D>> textures;
	int _sharesCount = 0;
public:
	std::string name;
	smart_pointer<ShaderProgram> shader;

	GLint illum = 1;
	GLfloat shininess = 128.0f;

	Material(std::string name) :name(name)
	{
		
	}

	Material(std::string name, smart_pointer<ShaderProgram>& shader) : Material(name)
	{
		this->shader = shader;
	}

	Material(std::string name, const char* vertexShaderSource,const char* fragmentShaderSource) : Material(name)
	{
		shader = smart_pointer<ShaderProgram>(new ShaderProgram());
		shader->loadShaderFromString(GL_VERTEX_SHADER, vertexShaderSource);
		shader->loadShaderFromString(GL_FRAGMENT_SHADER, fragmentShaderSource);
		shader->createAndLinkProgram();
	}


	void bind();
	void unbind();
	void setMainTexture(smart_pointer<Texture2D> texture);
	void setTexture(smart_pointer<Texture2D> texture, int index);
	void addTexture(smart_pointer<Texture2D> texture, char* samplerName = NULL);
	smart_pointer<Texture2D>& getTexture(int index);
	smart_pointer<Texture2D>& getMainTexture();
	void setColor(Color c, const char* propertyName = "Color");
	Color getColor(const char* propertyName = "Color");

	static smart_pointer<Material> createMaterial(std::string name, const char* vertexShaderFilename, const char* fragmentShaderFilename);
	static smart_pointer<Material> Diffuse();
	static smart_pointer<Material> Unlit();
};

inline void Material::bind()
{
	//glEnable(GL_TEXTURE_2D);

 	if (!shader.isEmpty())
		shader->bind();

	for (size_t i = 0, ilen = textures.size(); i < ilen; i++)
	{
		if (!textures[i].isEmpty())
		{
			glActiveTexture(GL_TEXTURE0 + i);
			textures[i]->bindTexture();
		}
	}
}

inline void Material::unbind()
{
	for (size_t i = 0, ilen = textures.size(); i < ilen; i++)
	{
		if (!textures[i].isEmpty())
		{
			textures[i]->unbindTexture();
		}
	}

	if (!shader.isEmpty())
		shader->unbind();
}

inline void Material::setTexture(smart_pointer<Texture2D> texture, int index)
{
	if (index >= (int)textures.size())
	{
		textures.push_back(texture);
		index = textures.size()-1;
	}
	else
	{
		textures[index] = texture;
	}

	if (!shader.isEmpty())
	{
		std::vector<UniformDesc> samplers = shader->getUniforms(GL_SAMPLER_2D);
		if (index < (int)samplers.size())
		{
			shader->setUniform1i(samplers[index].name, index);
		}
	}
}

inline void Material::addTexture(smart_pointer<Texture2D> texture, char* samplerName)
{
	textures.push_back(texture);

	if (!shader.isEmpty())
	{
		if (samplerName != NULL)
		{
			shader->setUniform1i(samplerName, textures.size()-1);
		}
		else
		{
			std::vector<UniformDesc> samplers = shader->getUniforms(GL_SAMPLER_2D);
			if (textures.size() <= samplers.size())
			{
				//printf("Sampler %s\n", samplers[textures.size() - 1].name);
				shader->setUniform1i(samplers[textures.size()-1].name, textures.size()-1);
			}
		}
	}
}

inline smart_pointer<Texture2D>& Material::getTexture(int index)
{
	if (index < (int)textures.size())
		return textures[index];

	return smart_pointer<Texture2D>::null();
}

inline smart_pointer<Texture2D>& Material::getMainTexture()
{
	if (textures.size() > 0)
		return textures[0];

	return smart_pointer<Texture2D>::null();
}

inline void Material::setMainTexture(smart_pointer<Texture2D> texture)
{
	if (textures.size() > 0)
		textures[0] = texture;
	else
	{
		textures.push_back(texture);
	}
}

inline void Material::setColor(Color c, const char* propertyName)
{
	if (!shader.isEmpty())
	{
		shader->setUniform4f(propertyName, c.getR(),c.getG(),c.getB(),c.getA());
	}
}

inline Color Material::getColor(const char* propertyName)
{
	// implement Uniform reads

	if (!shader.isEmpty())
	{
		GLfloat* colorData = new GLfloat[4];

		GLuint loc = shader->getUniformLocation(propertyName);
		glGetUniformfv(shader->getProgram(),loc,colorData);

		Color c(colorData[0], colorData[1], colorData[2], colorData[3]);
		delete[] colorData;

		return c;
	}

	return Color::BLACK;
}

#endif