#include <typeinfo>
#include <math.h>

#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "CollisionUtils.h"

bool CircleCollider2D::hasCollision(Collider2D* other)
{
	if (dynamic_cast<CircleCollider2D*>(other))
		return CollisionUtils::CircleToCircle(this, (CircleCollider2D*)other);
	else if (dynamic_cast<BoxCollider2D*>(other))
		return CollisionUtils::CircleToBox(this, (BoxCollider2D*)other);
	else
		return false;
}

void CircleCollider2D::Update()
{
#if defined(DEBUG_COLLISION) && defined(PLATFORM_WINDOWS)
	Vector2 position_ = getTransform()->getPosition();

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_STRIP);

	for (float i = 0; i < GLT_PI * 2; i += 0.4f)
		glVertex3f(position_.x + cos(i)*radius, position_.y + sin(i)*radius, -1.0f);

	glVertex3f(position_.x + cos(0.0f)*radius, position_.y + sin(0.0f)*radius, -1.0f);

	glEnd();
#endif
}