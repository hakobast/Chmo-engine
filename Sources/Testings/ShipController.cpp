
#include "Ship.h"
#include "ShipController.h"
#include "Weapon.h"
#include "CollisionSystem.h"
#include "Collider2D.h"
#include "GameController.h"

void ShipController::Init()
{
	ship_ = getGameObject()->getComponent<Ship>();
	CollisionSystem::GetInstance().addCollider(getGameObject()->getComponent<Collider2D>());
}

void ShipController::Update()
{
	if (ship_ == NULL)
		return;

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

void ShipController::OnDisable()
{
	if (isEnabled()) // Destroying
		CollisionSystem::GetInstance().removeCollider(getGameObject()->getComponent<Collider2D>());
}

void ShipController::OnAction(std::string action, void*const data)
{
	if (action == "Collision")
	{
		//Logger::Print("ShipController::OnAction %s \n", action.c_str());

		GameObject::FindComponent<GameController>()->restartGame();
	}
}