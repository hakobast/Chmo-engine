
#include "Ship.h"

#include "Input.h"
#include "GameTime.h"

void Ship::Init()
{

}

void Ship::Update()
{
	if (Input::GetKeyDown(KeyCode::w))
		getTransform()->TranslateUp(speed*GameTime::DeltaTime());

	if (Input::GetKeyDown(KeyCode::s))
		getTransform()->TranslateUp(-speed*GameTime::DeltaTime());

	if (Input::GetKeyDown(KeyCode::a))
		getTransform()->RotateZ(rotation*GameTime::DeltaTime());

	if (Input::GetKeyDown(KeyCode::d))
		getTransform()->RotateZ(-rotation*GameTime::DeltaTime());
}
