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

	AddCubeToWorld(Vector3(10, 2, 0), Vector3(1, 1, 1), true);

	GameObject* startLine = AddCubeToWorld(Vector3(0, 0.1f, -10), Vector3(20, 0.2f, 3), false, 0, 0, true);
	startLine->GetRenderObject()->SetColour(Vector4(0, 1, 0, 1));

	AddFloorToWorld(Vector3(0, -2, -90));
	AddCubeToWorld(Vector3(20, 2, -80), Vector3(1, 2, 90), false, 0, 0);
	AddCubeToWorld(Vector3(-20, 2, -90), Vector3(1, 2, 100), false, 0, 0);
	AddCubeToWorld(Vector3(0, 2, 10), Vector3(20, 2, 1), false, 0, 0);
	AddCubeToWorld(Vector3(0, 2, -190), Vector3(20, 2, 1), false, 0, 0);

	GameObject* player = AddSphereToWorld(Vector3(0,2,0), 1.0f, 5.0f, true);
	player->SetLayer(1);
	player->GetRenderObject()->SetDefaultTexture(playerTex);
	world->AddLayerConstraint(Vector2(-1, 99));
	//InitDefaultFloor();

	//AddSphereToWorld(Vector3(0, 5, 0), 1.0f);
	//AddSphereToWorld(Vector3(10, 5, 0), 1.0f);

	//AddCapsuleToWorld(Vector3(0, 5, 0), 3.0f, 1.5f);
	//InitMixedGridWorld(5, 5, 3.5f, 3.5f);
	//InitGameExamples();
	//InitDefaultFloor();
	BridgeConstraintTest();
	//testStateObject = AddStateObjectWorld(Vector3(0, 10, 0));
}
