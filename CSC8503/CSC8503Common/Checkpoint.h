#pragma once
#include "GameObject.h"

namespace NCL {
	namespace CSC8503 {
		class Checkpoint : public GameObject {
			Checkpoint(string name = "") : GameObject(name) {};
			~Checkpoint() {};

			void OnCollisionBegin(GameObject* otherObject) {
				
			}
		};
	}
}