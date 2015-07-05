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
	std::map<int, smart_pointer<Texture2D>> textures_;
	std::vector<MaterialShareInfo> sharingInfo_;
	smart_pointer<ShaderProgram> shader_;
	const char* name;

	int getSharesCount();
	void share(MaterialShareInfo shareInfo);
	void unshare(MaterialShareInfo shareInfo);
public:
	////////////// SHADER STANDERT ATTRIBUTES ////////////////
	static const char* vertexAttribName;
	static const char* texCoordAttribName;
	static const char* normalAttribName;
	static const char* tangentAttribName;
	static const char* bitangentAttribName;
	
	static std::map<const char*, unsigned int> AllAttributes;
	static std::map<const char*, unsigned int> SmallAttributes;
	static std::map<const char*, unsigned int> StandartAttributes;
	/////////////////////////////////////////////////////////

	~Material();
	Material(const Material& other);
	Material(const char* name,
		const char* vertexShaderSource, int vShaderLength,
		const char* fragmentShaderSource, int fShaderLength/*, 
		std::map<const char*, unsigned int> shaderAattributes*/);

	void bind();
	void unbind();
	void setMainTexture	(smart_pointer<Texture2D> texture);
	void setTexture(smart_pointer<Texture2D> texture, const char* propertyName);

	smart_pointer<Texture2D>&		getTexture(const char* propertyName);
	smart_pointer<Texture2D>&		getMainTexture();
	smart_pointer<ShaderProgram>&	getShader();

	void setFloat	(const char* name, float value);
	void setVec2	(const char* name, Vector2& value);
	void setVec3	(const char* name, Vector3& value);
	void setVec4	(const char* name, Vector4& value);
	void setColor	(const char* name, Color& value);
	void setMatrix4	(const char* name, Matrix4& value);

	float	getFloat	(const char* name);
	Vector2 getVec2		(const char* name);
	Vector3 getVec3		(const char* name);
	Vector4 getVec4		(const char* name);
	Color	getColor	(const char* name);
	Matrix4 getMatrix4	(const char* name);
};

inline smart_pointer<ShaderProgram>& Material::getShader()
{
	return shader_;
}

inline smart_pointer<Texture2D>& Material::getMainTexture()
{
	return getTexture("mainTexture");
}

inline void Material::setMainTexture(smart_pointer<Texture2D> texture)
{
	setTexture(texture, "mainTexture");
}

#endif