
#include "../Systems/RenderSystem.h"
#include "Material.h"
#include "Utils.h"

std::vector<Material*> Material::allMaterials;

smart_pointer<Material> Material::Diffuse()
{
	smart_pointer<Material> mat;

	mat->setColor(Color::BLACK, "Specular");
	mat->setColor(Color::BLACK, "Emission");

	return mat;
}

smart_pointer<Material> Material::Unlit()
{
	smart_pointer<Material> mat;

	mat->setColor(Color::WHITE, "Color");

	return mat;
}

Material::Material(const Material& other) :Material(other.name)
{
	textures = other.textures;
	shader = other.shader;
}

Material::Material(std::string name) :name(name)
{
	//std::cout << "**************MATERIAL CREATED*************" << std::endl;
	allMaterials.push_back(this);
}

Material::Material(std::string name, smart_pointer<ShaderProgram>& shader) : Material(name)
{
	this->shader = shader;
}

Material::Material(std::string name, const char* vertexShaderSource, int vShaderLength, const char* fragmentShaderSource, int fShaderLength) : Material(name)
{
	shader = smart_pointer<ShaderProgram>(new ShaderProgram());
	shader->loadShaderFromString(GL_VERTEX_SHADER, vertexShaderSource, vShaderLength);
	shader->loadShaderFromString(GL_FRAGMENT_SHADER, fragmentShaderSource, fShaderLength);
	shader->createAndLinkProgram();
}

Material::~Material()
{
	vectorRemove<Material>(allMaterials, this);
}

void Material::bind()
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

void Material::unbind()
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

void Material::setTexture(smart_pointer<Texture2D> texture, int index)
{
	if (index >= (int)textures.size())
	{
		textures.push_back(texture);
		index = textures.size() - 1;
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


void Material::addTexture(smart_pointer<Texture2D> texture, char* samplerName)
{
	textures.push_back(texture);

	if (!shader.isEmpty())
	{
		if (samplerName != NULL)
		{
			shader->setUniform1i(samplerName, textures.size() - 1);
		}
		else
		{
			std::vector<UniformDesc> samplers = shader->getUniforms(GL_SAMPLER_2D);
			if (textures.size() <= samplers.size())
			{
				//printf("Sampler %s\n", samplers[textures.size() - 1].name);
				shader->setUniform1i(samplers[textures.size() - 1].name, textures.size() - 1);
			}
		}
	}
}

void Material::setColor(Color c, const char* propertyName)
{
	if (!shader.isEmpty())
	{
		shader->setUniform4f(propertyName, c.getR(), c.getG(), c.getB(), c.getA());
	}
}


Color Material::getColor(const char* propertyName)
{
	// implement Uniform reads

	if (!shader.isEmpty())
	{
		GLfloat* colorData = new GLfloat[4];

		GLuint loc = shader->getUniformLocation(propertyName);
		glGetUniformfv(shader->getProgram(), loc, colorData);

		Color c(colorData[0], colorData[1], colorData[2], colorData[3]);
		delete[] colorData;

		return c;
	}

	return Color::BLACK;
}

void Material::share(MaterialShareInfo info)
{
	sharingInfo.push_back(info);
}

void Material::unshare(MaterialShareInfo info)
{
	std::vector<MaterialShareInfo>::iterator iter;
	for (iter = sharingInfo.begin(); iter != sharingInfo.end(); iter++)
	{
		if (iter->rend == info.rend && iter->materialIndex == info.materialIndex)
		{
			sharingInfo.erase(iter);
			//printf("**************MATERIAL UNSHARED******************\n");
			break;
		}
	}
}

int Material::getSharesCount()
{
	return sharingInfo.size();
}