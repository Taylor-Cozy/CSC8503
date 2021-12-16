#include "SpeedUp.h"
#include "Player.h"

void NCL::CSC8503::SpeedUp::OnCollisionBegin(GameObject* otherObject)
{
	if (otherObject->GetName() == "player") {
		((Player*)otherObject)->IncreaseSpeed(speed, time);
	}
}
