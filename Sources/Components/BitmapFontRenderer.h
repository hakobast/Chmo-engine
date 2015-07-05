#ifndef BITMAP_FONT_RENDERER_H
#define BITMAP_FONT_RENDERER_H

#include <vector>

#include "Renderer.h"
#include "../CoreEngine/GLDrawer.h"
#include "../CoreEngine/Font.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/Vectors.h"

class BitmapFontRenderer : public Renderer
{
public:
	~BitmapFontRenderer();
	BitmapFontRenderer();
	virtual void Create();
	virtual void Init();
	virtual void Render(int materialIndex = 0);

	void setText(const char* text);
	void setHorizontalAlignment(int aligment);
	void setVerticalAlignment(int aligment);
	void setFont(smart_pointer<Font> font);
	void setColor(Color c);
	Color getColor();
private:
	GLDrawer* drawer_ = 0;
	smart_pointer<Font> font_;
	char* text_ = 0;
	int textLength_ = 0;
	int alignmentH_ = 0;
	int alignmentV_ = 0;
	bool isDirty_ = false;
	std::vector<Vector2> vertices_;
	std::vector<Vector2> uvs_;

	void calculatGeometry();
};

inline void BitmapFontRenderer::setFont(smart_pointer<Font> font)
{
	font_ = font;
}

inline void BitmapFontRenderer::setHorizontalAlignment(int aligment)
{
	alignmentH_ = aligment;
}

inline void BitmapFontRenderer::setVerticalAlignment(int aligment)
{
	alignmentV_ = aligment;
}

inline void BitmapFontRenderer::setColor(Color c)
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		mat->setColor("Color", c);
}

inline Color BitmapFontRenderer::getColor()
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		return mat->getColor("Color");

	return Color::BLACK();
}

#endif