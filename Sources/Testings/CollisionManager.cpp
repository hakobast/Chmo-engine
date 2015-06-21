#include "CollisionManager.h"
#include "Collider2D.h"
#include "QuadTree.h"

void CollisionManager::Create()
{
	quadTree_ = new QuadTree(Vector2::ZERO, Vector2(7.0f,5.0f));
}

void CollisionManager::Update()
{
	quadTree_->clear();

	for (Collider2D* coll : colliders_)
		 quadTree_->add(coll);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if defined(DEBUG_COLLISION) && defined(PLATFORM_WINDOWS)

 	glColor3f(1.0f, 0.0f, 1.0f);
 
 	quadTree_->draw();
#endif
}

void CollisionManager::getPotentialCollisions(Collider2D* collider, std::vector<Collider2D*>* v)
{
	quadTree_->getPotentialCollisions(collider, v);
}

void CollisionManager::OnDestroy()
{
	delete quadTree_;
}