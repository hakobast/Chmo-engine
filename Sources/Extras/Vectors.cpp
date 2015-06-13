
#include "Vectors.h"

const Vector3 Vector3::UP      (0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ONE     (1.0f, 1.0f, 1.0f);
const Vector3 Vector3::ZERO    (0.0f, 0.0f, 0.0f);
const Vector3 Vector3::RIGHT   (1.0f, 0.0f, 0.0f);
const Vector3 Vector3::FORWARD (0.0f, 0.0f, -1.0f);

const Vector2 Vector2::UP    (0.0f, 1.0f);
const Vector2 Vector2::ONE   (1.0f, 1.0f);
const Vector2 Vector2::ZERO  (0.0f, 0.0f);
const Vector2 Vector2::RIGHT (1.0f, 0.0f);

Vector2::Vector2(const Vector3& v): x(v.x), y(v.y){}
Vector3::Vector3(const Vector2& v) : x(v.x), y(v.y), z(0){}
