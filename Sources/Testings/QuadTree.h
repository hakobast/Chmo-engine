#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <vector>
#include "../CoreEngine/ChmoEngine.h"

class Collider2D;

class QuadTree
{
private:
	static const int MAX_OBJECTS_IN_NODE = 2;

	QuadTree* nodes_[4];
	Vector2 position_;
	Vector2 halfSize_;
	std::vector<Collider2D*> objects_;

	bool hasChilds();
	void split();
	int getIndex(Collider2D* collider); // returns -1 if collider out of area, 4 if collider in more than one sub area, 0-3 if in specefic area
public:
	~QuadTree();
	QuadTree(Vector2 position, Vector2 halfSize);
	void draw();
	void add(Collider2D* collider);
	void getPotentialCollisions(Collider2D* collider, std::vector<Collider2D*>* v);
	void clear();
};

inline bool QuadTree::hasChilds()
{
	return nodes_[0] != NULL;
}

inline void QuadTree::split()
{
	Vector2 subSize = halfSize_ / 2;

	nodes_[0] = new QuadTree(position_ + Vector2(-subSize.x, subSize.y), subSize);
	nodes_[1] = new QuadTree(position_ + Vector2(subSize.x, subSize.y), subSize);
	nodes_[2] = new QuadTree(position_ + Vector2(subSize.x, -subSize.y), subSize);
	nodes_[3] = new QuadTree(position_ + Vector2(-subSize.x, -subSize.y), subSize);
}

inline void QuadTree::clear()
{
	objects_.clear();
	if (hasChilds())
	{
		for (int i = 0; i < 4; i++)
		{
			nodes_[i]->clear();
			delete nodes_[i];
			nodes_[i] = NULL;
		}
	}
}

#endif