
#include "Ship.h"

#include "../Systems/Input.h"
#include "../Systems/GameTime.h"
#include "../Components/SpriteRenderer.h"

void Ship::Init()
{

}

void Ship::Update()
{
	if (Input::IsKeyDown(KeyCode::w))
		getTransform()->TranslateUp(speed*GameTime::DeltaTime());

	if (Input::IsKeyDown(KeyCode::s))
		getTransform()->TranslateUp(-speed*GameTime::DeltaTime());

	if (Input::IsKeyDown(KeyCode::a))
		getTransform()->RotateZ(rotation*GameTime::DeltaTime());

	if (Input::IsKeyDown(KeyCode::d))
		getTransform()->RotateZ(-rotation*GameTime::DeltaTime());
}