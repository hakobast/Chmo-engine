#include "QuadTree.h"
#include "Collider2D.h"
#include "CollisionUtils.h"

#include "../Debug/Logger.h"

QuadTree::~QuadTree()
{
	clear();
}

QuadTree::QuadTree(Vector2 position, Vector2 halfSize)
:position_(position), halfSize_(halfSize)
{
	nodes_[0] = 0;
	nodes_[1] = 0;
	nodes_[2] = 0;
	nodes_[3] = 0;
}

void QuadTree::draw()
{
	if (hasChilds())
	{
		nodes_[0]->draw();
		nodes_[1]->draw();
		nodes_[2]->draw();
		nodes_[3]->draw();
	}

	glBegin(GL_LINE_STRIP);

	glVertex3f(position_.x - halfSize_.x, position_.y + halfSize_.y, -1.0f);
	glVertex3f(position_.x + halfSize_.x, position_.y + halfSize_.y, -1.0f);
	glVertex3f(position_.x + halfSize_.x, position_.y - halfSize_.y, -1.0f);
	glVertex3f(position_.x - halfSize_.x, position_.y - halfSize_.y, -1.0f);
	glVertex3f(position_.x - halfSize_.x, position_.y + halfSize_.y, -1.0f);

	glEnd();
}

void QuadTree::add(Collider2D* collider)
{
	int index = getIndex(collider);
	if (index == -1)
		return;

	if (hasChilds() && index != 4) // if collider in single area
	{
		nodes_[index]->add(collider);
	}
	else
	{
		objects_.push_back(collider);
		if (objects_.size() > MAX_OBJECTS_IN_NODE && !hasChilds())
		{
			split();
			int i = 0;
			while (i < (int)objects_.size())
			{
				int index = getIndex(objects_[i]);
				if (index != -1 && index != 4)
				{
					nodes_[index]->add(objects_[i]);
					objects_.erase(objects_.begin() + i);
				}
				else
					i++;
			}
		}
	}
}

void QuadTree::getPotentialCollisions(Collider2D* collider, std::vector<Collider2D*>* v)
{
	int index = getIndex(collider);
	if (index == -1)
		return;

	if (hasChilds())
	{
		if (index == 4) // if collider in more than one area
		{
			nodes_[0]->getPotentialCollisions(collider, v);
			nodes_[1]->getPotentialCollisions(collider, v);
			nodes_[2]->getPotentialCollisions(collider, v);
			nodes_[3]->getPotentialCollisions(collider, v);
		}
		else
			nodes_[index]->getPotentialCollisions(collider, v);
	}

	v->insert(v->begin(), objects_.begin(), objects_.end());
}

int QuadTree::getIndex(Collider2D* collider)
{
	int result[4] = { 0, 0 };

	Vector2 subSize = halfSize_ / 2;

	result[0] = (int)CollisionUtils::IsInersectsWithCollider(position_ + Vector2(-subSize.x, subSize.y), subSize, collider);
	result[1] = (int)CollisionUtils::IsInersectsWithCollider(position_ + Vector2(subSize.x, subSize.y), subSize, collider);
	if (result[0] + result[1] > 1)return 4;

	result[2] = (int)CollisionUtils::IsInersectsWithCollider(position_ + Vector2(subSize.x, -subSize.y), subSize, collider);
	if (result[0] + result[1] + result[2] > 1)return 4;

	result[3] = (int)CollisionUtils::IsInersectsWithCollider(position_ + Vector2(-subSize.x, -subSize.y), subSize, collider);
	if (result[0] + result[1] + result[2] + result[3] > 1)return 4;

	for (int i = 0; i < 4; i++)
		if (result[i] > 0)
			return i;

	return -1;
}