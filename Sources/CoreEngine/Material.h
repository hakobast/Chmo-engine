#ifndef EngineTesting_Material_h
#define EngineTesting_Material_h

#include <map>
#include <vector>
#include <string>

#include "LIBS.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/Color.h"

class Renderer;
class MaterialShareInfo;

class Material :public RemovableObject
{
friend class RenderSystem;
private:
	static std::vector<Material*> allMaterials_;
	std::vector<smart_pointer<Texture2D>> textures_;
	std::vector<MaterialShareInfo> sharingInfo_;
	smart_pointer<ShaderProgram> shader_;

	int getSharesCount();
	void share(MaterialShareInfo shareInfo);
	void unshare(MaterialShareInfo shareInfo);

public:
	static smart_pointer<Material> Diffuse();
	static smart_pointer<Material> Unlit();

	~Material();
	Material(const Material& other);
	Material(const char* name,
		const char* vertexShaderSource, int vShaderLength,
		const char* fragmentShaderSource, int fShaderLength/*, 
		std::map<const char*, unsigned int> shaderAattributes*/);

	void bind();
	void unbind();
	void setMainTexture	(smart_pointer<Texture2D> texture);
	void setTexture		(smart_pointer<Texture2D> texture, int index);
	void addTexture		(smart_pointer<Texture2D> texture, char* samplerName = NULL);

	smart_pointer<Texture2D>&		getTexture(int index);
	smart_pointer<Texture2D>&		getMainTexture();
	smart_pointer<ShaderProgram>&	getShader();

	void	setColor(Color c, const char* propertyName = "Color");
	Color	getColor(const char* propertyName = "Color");
	const char* name;
};

inline smart_pointer<ShaderProgram>& Material::getShader()
{
	return shader_;
}

inline smart_pointer<Texture2D>& Material::getTexture(int index)
{
	if (index < (int)textures_.size())
		return textures_[index];

	return smart_pointer<Texture2D>::null();
}

inline smart_pointer<Texture2D>& Material::getMainTexture()
{
	if (textures_.size() > 0)
		return textures_[0];

	return smart_pointer<Texture2D>::null();
}

inline void Material::setMainTexture(smart_pointer<Texture2D> texture)
{
	if (textures_.size() > 0)
		textures_[0] = texture;
	else
	{
		textures_.push_back(texture);
	}
}

#endif