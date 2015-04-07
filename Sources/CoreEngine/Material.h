#ifndef EngineTesting_Material_h
#define EngineTesting_Material_h

#include <vector>

#include "CoreEngine/LIBS.h"
#include "CoreEngine/Texture2D.h"
#include "CoreEngine/ShaderProgram.h"
#include "Extras/smart_pointer.h"
#include "Extras/Color.h"


class Material :public RemovableObject
{
friend class Renderer;

private:
	std::vector<smart_pointer<Texture2D>> textures;
	int _sharesCount = 0;
public:
	/* FEW STANDART MATERIALS */
	static const smart_pointer<Material> diffuse;
	static const smart_pointer<Material> unlitTexture;
	/*END*/
	std::string name;
	smart_pointer<ShaderProgram> shader;

	Color color_ambient;
	Color color_diffuse;
	Color color_specular;
	Color color_emmission;

	GLint illum = 1;
	GLfloat shininess = 128.0f;

	Material(std::string name) :name(name)
	{
		color_ambient.  set(0.3f, 0.3f, 0.3f, 1.0f);
		color_diffuse.  set(0.6f, 0.6f, 0.6f, 1.0f);
		color_specular. set(0.0f, 0.0f, 0.0f, 1.0f);
		color_emmission.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Material(std::string name, smart_pointer<ShaderProgram>& shader) : Material(name)
	{
		this->shader = shader;
	}

	Material(std::string name, const char* vertexShaderSource,const char* fragmentShaderSource) : Material(name)
	{
		shader = smart_pointer<ShaderProgram>(new ShaderProgram());
		shader->loadShaderFromString(GL_VERTEX_SHADER_ARB, vertexShaderSource);
		shader->loadShaderFromString(GL_FRAGMENT_SHADER_ARB, fragmentShaderSource);
		shader->createAndLinkProgram();
	}

	static smart_pointer<Material> createMaterial(std::string name, const char* vertexShaderFilename, const char* fragmentShaderFilename);
	static smart_pointer<Material> Diffuse();
	static smart_pointer<Material> Unlit();

	void bind();
	void unbind();
	void setMainTexture(smart_pointer<Texture2D> texture);
	void setTexture(smart_pointer<Texture2D> texture, int index);
	void addTexture(smart_pointer<Texture2D> texture, char* samplerName = NULL);
	smart_pointer<Texture2D>& getTexture(int index);
	smart_pointer<Texture2D>& getMainTexture();
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

	glMaterialfv(GL_FRONT, GL_AMBIENT, color_ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_specular[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
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

#endif