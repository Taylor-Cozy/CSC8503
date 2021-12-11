#include "LevelOne.h"

void LevelOne::InitWorld()
{
	//world->AddLayerConstraint(Vector2(0, 1));
	world->ClearAndErase();
	physics->Clear();

	//GameObject* a = AddCubeToWorld(Vector3(0, 1.5f, 0), Vector3(1, 1, 1));
	//a->GetTransform().SetOrientation(Quaternion(0, 0.25f, 0, 1.0f));
	//GameObject* b = AddCubeToWorld(Vector3(10, 1.5f, 0), Vector3(1, 1, 1));
	//b->GetTransform().SetOrientation(Quaternion(0.25f, 0, 0, 1.0f));

	AddCubeToWorld(Vector3(10, 2, 0), Vector3(1, 1, 1));
	AddCubeToWorld(Vector3(10, 4, 0), Vector3(1, 1, 1));
	AddCubeToWorld(Vector3(10, 6, 0), Vector3(1, 1, 1));
	AddCubeToWorld(Vector3(10, 8, 0), Vector3(1, 1, 1));
	AddCubeToWorld(Vector3(10, 10, 0), Vector3(1, 1, 1));
	AddCubeToWorld(Vector3(10, 12, 0), Vector3(1, 1, 1));

	//AddSphereToWorld(Vector3(0, 5, 0), 1.0f);
	//AddSphereToWorld(Vector3(10, 5, 0), 1.0f);

	//AddCapsuleToWorld(Vector3(0, 5, 0), 3.0f, 1.5f);
	//InitMixedGridWorld(5, 5, 3.5f, 3.5f);
	//InitGameExamples();
	InitDefaultFloor();
	//BridgeConstraintTest();
	//testStateObject = AddStateObjectWorld(Vector3(0, 10, 0));
}
