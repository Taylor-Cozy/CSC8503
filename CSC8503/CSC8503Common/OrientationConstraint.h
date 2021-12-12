#pragma once
#include "Constraint.h"
#include "../../Common/Vector3.cpp"
namespace NCL {
	namespace CSC8503 {
		class GameObject;

		class OrientationConstraint : public Constraint
		{
		public:
			OrientationConstraint(GameObject* a, GameObject* b, Vector3 x) {
				objectA = a;
				objectB = b;
				angle = x;
			}
			~OrientationConstraint() {}

			void UpdateConstraint(float dt) override;

		protected:
			GameObject* objectA;
			GameObject* objectB;
			Vector3 angle;
		};
	}
}

