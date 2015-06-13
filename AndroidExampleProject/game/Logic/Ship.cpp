
#include "Ship.h"
#include "Weapon.h"

void Ship::Init()
{
	transform_ = getTransform();
}

void Ship::Update()
{
	if (hasDestination_)
	{
		Vector3 current = transform_->getPosition();
		if (!current.compare(dest_, 0.1f))
		{
			current += (dest_ - current).normalize()*speed*GameTime::DeltaTime();
			transform_->setPosition(current);
		}
		else
			hasDestination_ = false;
	}
}

void Ship::OnDestroy()
{
	std::vector<std::pair<Weapon*, Vector3>>::iterator iter;
	for (iter = weapons_.begin(); iter != weapons_.end(); iter++)
		delete iter->first;
}

void Ship::moveTo(Vector3 dest)
{
	Vector3 dir = (dest - transform_->getPosition()).normalize();
	transform_->SetRotation(atan2f(dir.y, dir.x)*180.0f/3.141592f-90, 0.0f, 0.0f, 1.0f);

	dest_ = dest;
	hasDestination_ = true;
}

void Ship::fire(int weaponIndex)
{
	if (weaponIndex >= 0 && weaponIndex < (int)weapons_.size())
	{
		transform_->getMatrix(weaponTransformation_, false);

		//keeping weapon's local direction
		Weapon* weapon = weapons_[weaponIndex].first;
		weapon->currentDirection = weapon->direction;
		weapon->currentDirection.rotateVector(weaponTransformation_);

		//keeping weapon's local position
		Vector3 weaponPos = weapons_[weaponIndex].second;
		weaponPos.rotateVector(weaponTransformation_);
		weapon->position = transform_->getPosition() + weaponPos;

		weapon->fire();
	}
	else
		Logger::PrintWarning("Ship::fire - invalid argument\n");
}

Weapon* Ship::getWeapon(int index)
{
	if (index >= 0 && index < (int)weapons_.size())
	{ 
		return weapons_[index].first;
	}

	Logger::PrintWarning("Ship::getWeapon - invalid argument\n");
	return NULL;
}
void Ship::addWeapon(Weapon* weapon, Vector3 localPosition, Vector3 direction)
{
	weapon->currentDirection = weapon->direction = direction;
	weapons_.push_back(std::pair<Weapon*, Vector3>(weapon, localPosition));
}

int Ship::getWeaponsCount()
{
	return weapons_.size();
}