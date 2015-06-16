#include "CollisionSystem.h"
#include "Collider2D.h"
#include "QuadTree.h"

void CollisionSystem::Create()
{
	quadTree_ = new QuadTree(Vector2::ZERO, Vector2(6.0f,4.5f));
}

void CollisionSystem::Update()
{
	quadTree_->clear();

	for (Collider2D* coll : colliders_)
		quadTree_->add(coll);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 	glColor3f(1.0f, 0.0f, 1.0f);
// 
// 	quadTree_->draw();
}

void CollisionSystem::getPotentialCollisions(Collider2D* collider, std::vector<Collider2D*>* v)
{
	quadTree_->getPotentialCollisions(collider, v);
}

void CollisionSystem::OnDestroy()
{
	delete quadTree_;
}