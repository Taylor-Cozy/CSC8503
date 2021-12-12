#include "OrientationConstraint.h"
#include "../CSC8503Common/GameObject.h"

using namespace NCL;
using namespace CSC8503;

void OrientationConstraint::UpdateConstraint(float dt) {
	Vector3 relativeRot = 
		objectA->GetTransform().GetOrientation().ToEuler() - 
		objectB->GetTransform().GetOrientation().ToEuler();

	PhysicsObject* physA = objectA->GetPhysicsObject();
	PhysicsObject* physB = objectB->GetPhysicsObject();

	if (relativeRot.x != angle.x) {
		// add rotation to x
	}

	if (relativeRot.y != angle.y) {
		// add rotation to y
	}

	if (relativeRot.z != angle.z) {
		// add rotation to z
	}
}