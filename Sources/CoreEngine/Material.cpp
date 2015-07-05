
#include "../Extras/GLUtils.h"
#include "../Systems/RenderSystem.h"
#include "../Components/Renderer.h"
#include "../Debug/Logger.h"
#include "Material.h"
#include "Utils.h"

////////////////// Making some built-in shader attributes /////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

std::vector<Material*> Material::allMaterials_;

Material::Material(const Material& other) :name(other.name)
{
	smart_pointer<ShaderProgram> shaderToCopy = other.shader_;
	
	shader_ = smart_pointer<ShaderProgram>(new ShaderProgram(Material::AllAttributes));
	shader_->loadShaderFromString(GL_VERTEX_SHADER, shaderToCopy->shaderSources[0], shaderToCopy->sourceLengths[0]);
	shader_->loadShaderFromString(GL_FRAGMENT_SHADER, shaderToCopy->shaderSources[1], shaderToCopy->sourceLengths[1]);
	shader_->createAndLinkProgram();

	std::vector<UniformDesc> uniforms = shaderToCopy->getUniforms();
	for (size_t i = 0, len = uniforms.size(); i < len; i++)
	{
		//Logger::Print("Name %s, type %d\n", uniforms[i].name, uniforms[i].type);
		switch (uniforms[i].type)
		{
		case GL_FLOAT:
			shader_->setFloat(uniforms[i].name, shaderToCopy->getFloat(uniforms[i].name));
			//Logger::Print("GL_FLOAT\n");
			break;
		case GL_FLOAT_VEC2:
			shader_->setVec2(uniforms[i].name, shaderToCopy->getVec2(uniforms[i].name));
			//Logger::Print("GL_FLOAT_VEC2\n");
			break;
		case GL_FLOAT_VEC3:
			shader_->setVec3(uniforms[i].name, shaderToCopy->getVec3(uniforms[i].name));
			//Logger::Print("GL_FLOAT_VEC3\n");
			break;
		case GL_FLOAT_VEC4:
			shader_->setVec4(uniforms[i].name, shaderToCopy->getVec4(uniforms[i].name));
			//Logger::Print("GL_FLOAT_VEC4\n");
			break;
		case GL_FLOAT_MAT4:
			shader_->setMatrix4(uniforms[i].name, shaderToCopy->getMatrix4(uniforms[i].name));
			//Logger::Print("GL_FLOAT_MAT4\n");
			break;
		default:
			break;
 		}
	}

	textures_ = other.textures_;

	allMaterials_.push_back(this);
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
	shader_->bind();

	std::map<int, smart_pointer<Texture2D>>::iterator iter = textures_.begin();
	for (int i = textures_.size()-1; iter != textures_.end(); iter++, i--)
	{
		if (!iter->second.isEmpty())
		{
			glActiveTexture(GL_TEXTURE0 + i);
			iter->second->bindTexture();
		}
	}
}

void Material::unbind()
{
	std::map<int, smart_pointer<Texture2D>>::iterator iter;
	for (iter = textures_.begin(); iter != textures_.end(); iter++)
	{
		if (!iter->second.isEmpty())
		{
			iter->second->unbindTexture();
		}
	}

	shader_->unbind();
}

void Material::setTexture(smart_pointer<Texture2D> texture, const char* propertyName)
{
	GLint loc = shader_->getUniformLocation(propertyName);

	std::pair<std::map<int, smart_pointer<Texture2D>>::iterator, bool> result;
	result = textures_.insert(std::pair<int, smart_pointer<Texture2D>>(loc, texture));
	if (result.second == false)
		textures_[loc] = texture;

	shader_->setUniform1i(propertyName, textures_.size()-1);
}

smart_pointer<Texture2D>& Material::getTexture(const char* propertyName)
{
	GLint loc = shader_->getUniformLocation(propertyName);
	std::map<int, smart_pointer<Texture2D>>::iterator iter = textures_.find(loc);
	if (iter != textures_.end())
		return iter->second;

	return smart_pointer<Texture2D>::null();
}

void Material::setFloat(const char* name, float value)
{
	shader_->setFloat(name, value);
}

void Material::setVec2(const char* name, Vector2& value)
{
	shader_->setVec2(name, value);
}

void Material::setVec3(const char* name, Vector3& value)
{
	shader_->setVec3(name, value);
}

void Material::setVec4(const char* name, Vector4& value)
{
	shader_->setVec4(name, value);
}

void Material::setColor(const char* name, Color& value)
{
	shader_->setColor(name, value);
}

void Material::setMatrix4(const char* name, Matrix4& value)
{
	shader_->setMatrix4(name, value);
}

float Material::getFloat(const char* name)
{
	return shader_->getFloat(name);
}

Vector2 Material::getVec2(const char* name)
{
	return shader_->getVec2(name);
}

Vector3 Material::getVec3(const char* name)
{
	return shader_->getVec3(name);
}

Vector4 Material::getVec4(const char* name)
{
	return shader_->getVec4(name);
}

Color Material::getColor(const char* name)
{
	return shader_->getColor(name);
}

Matrix4 Material::getMatrix4(const char* name)
{
	return shader_->getMatrix4(name);
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