#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <vector>
#include <algorithm>

#include "../CoreEngine/ChmoEngine.h"

class QuadTree;
class Collider2D;

class CollisionSystem : public GameLogic, public Singleton<CollisionSystem>
{
private:
	std::vector<Collider2D*> colliders_;
	QuadTree* quadTree_;
public:
	virtual void Create();
	virtual void Update();
	virtual void OnDestroy();

	void addCollider(Collider2D* collider);
	void removeCollider(Collider2D* collider);
	void getPotentialCollisions(Collider2D* collider, std::vector<Collider2D*>* v);
	void getColliders(std::vector<Collider2D*>* v);
};

inline void CollisionSystem::addCollider(Collider2D* collider)
{
	if (collider != NULL)
		colliders_.push_back(collider);
}

inline void CollisionSystem::removeCollider(Collider2D* collider)
{
	colliders_.erase(std::remove(colliders_.begin(), colliders_.end(), collider), colliders_.end());
}

inline void CollisionSystem::getColliders(std::vector<Collider2D*>* v)
{
	v->insert(v->begin(), colliders_.begin(), colliders_.end());
}


#endif