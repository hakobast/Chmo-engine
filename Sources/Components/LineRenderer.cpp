
#include "LineRenderer.h"
#include "../CoreEngine/GLDrawer.h"

LineRenderer::~LineRenderer()
{
	delete drawer_;
}

LineRenderer::LineRenderer()
{
	drawer_ = new GLDrawer(GL_LINE_STRIP, VBO);

	//TEMP get this data from shader
	drawer_->setVertexIndex(0);
	drawer_->setTexCoordIndex(1);
	drawer_->setNormalIndex(2);
	drawer_->setTangentIndex(3);
	drawer_->setBitangentIndex(4);
}

void LineRenderer::Render(int materialIndex)
{
	glLineWidth(width_);
	drawer_->draw();
	glLineWidth(1.0f);
}

void LineRenderer::setPointsCount(int count)
{
	if (count >= 0)
	{
		pointsCount_ = count;
		points_.resize(pointsCount_);

		if (pointsCount_ > 0)
			drawer_->setVertexData(3, false, pointsCount_, points_[0].getPointer());
		else
			drawer_->setVertexData(3, false, 0, NULL);
	}
}

void LineRenderer::setPoints(const std::vector<Vector3>* points, int offset)
{
	if (points != NULL)
	{
		bool isDirty = false;
		const std::vector<Vector3>& pointsRef = *points;
		for (size_t i = 0, len = pointsRef.size(); i < len; i++)
		{
			if ((int)i + offset < pointsCount_)
			{
				isDirty = true;
				points_[i + offset] = pointsRef[i];
			}
		}

		if (isDirty)
			drawer_->setVertexData(3, false, pointsCount_, points_[0].getPointer());
	}
}

void LineRenderer::setPoint(int index, Vector3 position)
{
	if (index >= 0 && index < pointsCount_)
	{
		points_[index] = position;
		drawer_->setVertexData(3, false, pointsCount_, points_[0].getPointer());
	}
}