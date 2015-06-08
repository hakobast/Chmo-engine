
#include "Ship.h"

#include "../Systems/Input.h"
#include "../Systems/GameTime.h"
#include "../Components/SpriteRenderer.h"

void Ship::Init()
{

}

void Ship::Update()
{
	if (Input::IsKeyDown(Key::w))
		getTransform()->TranslateUp(speed*GameTime::DeltaTime());

	if (Input::IsKeyDown(Key::s))
		getTransform()->TranslateUp(-speed*GameTime::DeltaTime());

	if (Input::IsKeyDown(Key::a))
		getTransform()->RotateZ(rotation*GameTime::DeltaTime());

	if (Input::IsKeyDown(Key::d))
		getTransform()->RotateZ(-rotation*GameTime::DeltaTime());
}