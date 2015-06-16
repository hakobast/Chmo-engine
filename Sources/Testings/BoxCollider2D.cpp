#include <typeinfo>
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include "CollisionUtils.h"

bool BoxCollider2D::HasCollision(Collider2D* other)
{
	if (dynamic_cast<BoxCollider2D*>(other))
		return CollisionUtils::BoxToBox(this, (BoxCollider2D*)other);
	else if (dynamic_cast<CircleCollider2D*>(other))
		return CollisionUtils::CircleToBox((CircleCollider2D*)other, this);
	else
		return false;
}

void BoxCollider2D::Update()
{
#ifdef DEBUG_COLLISION
	Vector2 position_ = getTransform()->getPosition();
	Vector2 halfSize_ = size / 2;

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_STRIP);

	glVertex3f(position_.x - halfSize_.x, position_.y + halfSize_.y, -1.0f);
	glVertex3f(position_.x + halfSize_.x, position_.y + halfSize_.y, -1.0f);
	glVertex3f(position_.x + halfSize_.x, position_.y - halfSize_.y, -1.0f);
	glVertex3f(position_.x - halfSize_.x, position_.y - halfSize_.y, -1.0f);
	glVertex3f(position_.x - halfSize_.x, position_.y + halfSize_.y, -1.0f);

	glEnd();
#endif
}