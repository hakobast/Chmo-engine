
#include "../Extras/GLUtils.h"
#include "../Systems/RenderSystem.h"
#include "../Components/Renderer.h"
#include "../Debug/Logger.h"
#include "Material.h"
#include "Utils.h"

const char* Material::vertexAttribName = "InVertex";
const char* Material::texCoordAttribName = "InTexCoord0";
const char* Material::normalAttribName = "InNormal";
const char* Material::tangentAttribName = "InTangent";
const char* Material::bitangentAttribName = "InBitangent";

std::map<const char*, unsigned int> Material::AllAttributes{
	{ vertexAttribName, 0 },
	{ texCoordAttribName, 1 },
	{ normalAttribName, 2 },
	{ tangentAttribName, 3 },
	{ bitangentAttribName, 4 }
};

std::map<const char*, unsigned int> Material::StandartAttributes{
	{ vertexAttribName, 0 },
	{ texCoordAttribName, 1 },
	{ normalAttribName, 2 },
};

std::map<const char*, unsigned int> Material::SmallAttributes{
	{ vertexAttribName, 0 },
	{ texCoordAttribName, 1 },
};

std::vector<Material*> Material::allMaterials_;

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

Material::Material(const Material& other) :name(other.name)
{
	textures_ = other.textures_;
	shader_ = other.shader_; //TODO implement shader duplication
}

Material::Material(const char* name,
	const char* vertexShaderSource, int vShaderLength,
	const char* fragmentShaderSource, int fShaderLength
	/*,std::map<const char*, unsigned int> shaderAattributes*/) : name(name)
{
	shader_ = smart_pointer<ShaderProgram>(new ShaderProgram(Material::AllAttributes));
	shader_->loadShaderFromString(GL_VERTEX_SHADER, vertexShaderSource, vShaderLength);
	shader_->loadShaderFromString(GL_FRAGMENT_SHADER, fragmentShaderSource, fShaderLength);
	shader_->createAndLinkProgram();

	allMaterials_.push_back(this);
}

Material::~Material()
{
	vectorRemove<Material>(allMaterials_, this);
}

void Material::bind()
{
	//glEnable(GL_TEXTURE_2D);

	//check_gl_error();
	if (!shader_.isEmpty())
		shader_->bind();
	//check_gl_error();
	for (size_t i = 0, ilen = textures_.size(); i < ilen; i++)
	{
		if (!textures_[i].isEmpty())
		{
			glActiveTexture(GL_TEXTURE0 + i);
			textures_[i]->bindTexture();
		}
	}
}

void Material::unbind()
{
	for (size_t i = 0, ilen = textures_.size(); i < ilen; i++)
	{
		if (!textures_[i].isEmpty())
		{
			textures_[i]->unbindTexture();
		}
	}

	if (!shader_.isEmpty())
		shader_->unbind();
}

void Material::setTexture(smart_pointer<Texture2D> texture, int index)
{
	if (index >= (int)textures_.size())
	{
		textures_.push_back(texture);
		index = textures_.size() - 1;
	}
	else
	{
		textures_[index] = texture;
	}

	if (!shader_.isEmpty())
	{
		std::vector<UniformDesc> samplers = shader_->getUniforms(GL_SAMPLER_2D);
		if (index < (int)samplers.size())
		{
			shader_->setUniform1i(samplers[index].name, index);
		}
	}
}


void Material::addTexture(smart_pointer<Texture2D> texture, char* samplerName)
{
	textures_.push_back(texture);

	if (!shader_.isEmpty())
	{
		if (samplerName != NULL)
		{
			shader_->setUniform1i(samplerName, textures_.size() - 1);
		}
		else
		{
			std::vector<UniformDesc> samplers = shader_->getUniforms(GL_SAMPLER_2D);
			if (textures_.size() <= samplers.size())
			{
				//printf("Sampler %s\n", samplers[textures.size() - 1].name);
				shader_->setUniform1i(samplers[textures_.size() - 1].name, textures_.size() - 1);
			}
		}
	}
}

void Material::setColor(Color c, const char* propertyName)
{
	if (!shader_.isEmpty())
	{
		shader_->bind();
		shader_->setUniform4f(propertyName, c.getR(), c.getG(), c.getB(), c.getA());
		shader_->unbind();
	}
}


Color Material::getColor(const char* propertyName)
{
	// implement Uniform reads

	if (!shader_.isEmpty())
	{
		GLfloat* colorData = new GLfloat[4];

		GLuint loc = shader_->getUniformLocation(propertyName);
		glGetUniformfv(shader_->getProgram(), loc, colorData);

		Color c(colorData[0], colorData[1], colorData[2], colorData[3]);
		delete[] colorData;

		return c;
	}

	return Color::BLACK;
}

void Material::setFloat(float value, const char* propertyName)
{
	if (!shader_.isEmpty())
	{
		shader_->bind();
		shader_->setUniform1f(propertyName, value);
		shader_->unbind();
	}
}

float Material::getFloat(const char* propertyName)
{
	if (!shader_.isEmpty())
	{
		float value = 0;
		GLuint loc = shader_->getUniformLocation(propertyName);
		glGetUniformfv(shader_->getProgram(), loc, &value);

		return value;
	}

	return 0.0f;
}

void Material::share(MaterialShareInfo info)
{
	sharingInfo_.push_back(info);
}

void Material::unshare(MaterialShareInfo info)
{
	std::vector<MaterialShareInfo>::iterator iter;
	for (iter = sharingInfo_.begin(); iter != sharingInfo_.end(); iter++)
	{
		if (iter->rend == info.rend && iter->materialIndex == info.materialIndex)
		{
			sharingInfo_.erase(iter);
			//printf("**************MATERIAL UNSHARED******************\n");
			break;
		}
	}
}

int Material::getSharesCount()
{
	return sharingInfo_.size();
}