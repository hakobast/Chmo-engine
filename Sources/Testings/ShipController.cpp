
#include "Ship.h"
#include "ShipController.h"
#include "Weapon.h"

void ShipController::Init()
{
	ship_ = getGameObject()->getComponent<Ship>();
}

void ShipController::Update()
{
	if (Input::IsMouseDownNow(Left))
	{
		if (Application::CurrentPlatform() == ANDROID_PLATFORM)
		{
			Vector2 screen = Input::GetTouch(0)->getPosition();
			Vector3 dest;
			Camera::main->ScreenToWorldPoint(screen, dest);

			ship_->moveTo(dest);
		}
		else
		{
			Vector2 screen = Input::GetMousePosition();
			Vector3 dest;
			Camera::main->ScreenToWorldPoint(screen, dest);

			ship_->moveTo(dest);
		}
	}

	t_ += GameTime::DeltaTime();
	if (t_ >= fireInterval_)
	{
		for (int i = 0, len = ship_->getWeaponsCount(); i < len; i++)
			ship_->fire(i);
		t_ = 0;
	}
}