#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

#include <vector>

#include "Renderer.h"
#include "../Extras/Vectors.h"
#include "../Extras/Color.h"

class GLDrawer;

//TODO create functions to set line width

class LineRenderer : public Renderer
{
public:
	~LineRenderer();
	LineRenderer();

	virtual void Render(int materialIndex = 0);

	void setPoints		(const std::vector<Vector3>* points, int offset = 0);
	void setPoint		(int index, Vector3 position);
	void setPointsCount	(int count);
	void setColor		(Color c);
	void setWidth		(float width);

	std::vector<Vector3>	getPoints();
	int						getPointsCount();
	Color					getColor();
	float					getWidth();
private:
	std::vector<Vector3> points_;
	GLDrawer* drawer_ = 0;
	int pointsCount_ = 0;
	float width_ = 1;
};

inline std::vector<Vector3> LineRenderer::getPoints()
{
	return points_;
}

inline int LineRenderer::getPointsCount()
{
	return pointsCount_;
}

inline void LineRenderer::setColor(Color c)
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		mat->setColor(c);
}

inline Color LineRenderer::getColor()
{
	smart_pointer<Material>& mat = getSharedMaterial();
	if (!mat.isEmpty())
		return mat->getColor();

	return Color::BLACK;
}

inline float LineRenderer::getWidth()
{
	return width_;
}

inline void LineRenderer::setWidth(float width)
{
	width_ = width;
}
#endif