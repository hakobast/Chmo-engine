#ifndef EngineTesting_Material_h
#define EngineTesting_Material_h

#include <vector>
#include <string>

#include "LIBS.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "../Systems/RenderSystem.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/Color.h"

class Renderer;

class Material :public RemovableObject
{
friend class RenderSystem;
private:
	static std::vector<Material*> allMaterials;
	std::vector<smart_pointer<Texture2D>> textures;
	std::vector<MaterialShareInfo> sharingInfo;
	smart_pointer<ShaderProgram> shader;

	int getSharesCount();
	void share(MaterialShareInfo shareInfo);
	void unshare(MaterialShareInfo shareInfo);

public:
	std::string name;

	GLint illum = 1;
	GLfloat shininess = 128.0f;

	Material(const Material& other);
	Material(std::string name);
	Material(std::string name, smart_pointer<ShaderProgram>& shader);
	Material(std::string name, const char* vertexShaderSource, const char* fragmentShaderSource);
	~Material();

	void bind();
	void unbind();
	smart_pointer<ShaderProgram>& getShader();
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

inline smart_pointer<ShaderProgram>& Material::getShader()
{
	return shader;
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