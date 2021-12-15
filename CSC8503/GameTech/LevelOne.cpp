#include "LevelOne.h"
#include "../CSC8503Common/Spring.h"
#include "../CSC8503Common/SpringConstraint.h"
#include "../CSC8503Common/LockOrientationConstraint.h"
#include "../CSC8503Common/Paddle.h"
#include "../CSC8503Common/PositionConstraint.h"
#include "../CSC8503Common/OrientationConstraint.h"
#include "../CSC8503Common/Pendulum.h"

void LevelOne::InitWorld()
{
	world->ClearAndErase();
	physics->Clear();

	InitFloor();

	GameObject* startLine = AddCubeToWorld(Vector3(0, 0.1f, -10), Vector3(20, 0.2f, 3), false, 0, 0, true);
	startLine->GetRenderObject()->SetColour(Vector4(0, 1, 0, 1));

	//GameObject* paddle = AddCubeToWorld(Vector3(0, 2, 2), Vector3(10, 2, 1), false, 0.1f);
	AddPaddleToWorld(Vector3(0, 2, 2), Vector3(10, 2, 1), Vector3(0, 0, -1), 10000.0f, 30.0f, new Vector3(0, 2, 2));
	GameObject* p = AddPaddleToWorld(Vector3(197, -48.5, -190), Vector3(18, 2, 1), Vector3(0, 0.05, 0.8), 10000.0f, 30.0f, new Vector3(197, -48.5, -190));
	//AddCapsuleToWorld(Vector3(0, 3.5f, -50), 3, 1.5f, 10.0f);
	AddPendulum(Vector3(0, 20, -50), Vector3(0, 3.5f, -50), 18, 3.0f, 1.5f);
	AddPendulum(Vector3(0, 20, -80), Vector3(10, 3.5f, -80), 18, 3.0f, 1.5f);
	AddPendulum(Vector3(0, 20, -110), Vector3(-10, 3.5f, -110), 18, 3.0f, 1.5f);

	BridgeConstraintTest(Vector3(20, 1, 2), Vector3(200, -52, -136));


	GameObject* player = AddSphereToWorld(Vector3(0,2,0), 1.0f, 50.0f, true);
	player->SetName("player");
	player->GetPhysicsObject()->SetFriction(0.2f);
	player->SetLayer(1);
	player->GetRenderObject()->SetDefaultTexture(playerTex);
	player->SetDynamic(true);

	GameObject* water = AddCubeToWorld(Vector3(200, -112, -35), Vector3(20, 4, 20), true, 0.0f, 0);
	water->GetPhysicsObject()->SetSpringRes(true);
	water->GetTransform().SetOrientation(Quaternion(0.05f, 0.0f, 0.0f, 1.0f));
	water->GetRenderObject()->SetDefaultTexture(NULL);
	water->GetRenderObject()->SetColour(Vector4(0.51f, 0.84f, 0.93f, 1.0f));

	GameObject* base = AddCubeToWorld(Vector3(200, -118, -36), Vector3(20, 2, 20), true, 0.0f, 0);
	base->GetPhysicsObject()->SetElasticity(1.5f);
	base->GetPhysicsObject()->SetFriction(false);
	base->GetTransform().SetOrientation(Quaternion(0.05f, 0.0f, 0.0f, 1.0f));

	AddCubeToWorld(Vector3(200, -115, 15), Vector3(20, 2, 30), false, 0.0, 0);

	world->BuildStaticList();
}

GameObject* LevelOne::AddPaddleToWorld(const Vector3& position, Vector3 dimensions, Vector3 normal, float force, float springForce, Vector3* target)
{
	Paddle* paddle = new Paddle(normal, force, "Paddle");
	AABBVolume* volume = new AABBVolume(dimensions);
	paddle->SetBoundingVolume((CollisionVolume*)volume);

	paddle->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	paddle->SetRenderObject(new RenderObject(&paddle->GetTransform(), cubeMesh, basicTex, basicShader));
	paddle->SetPhysicsObject(new PhysicsObject(&paddle->GetTransform(), paddle->GetBoundingVolume()));

	paddle->GetPhysicsObject()->SetInverseMass(1.0f);
	paddle->GetPhysicsObject()->InitCubeInertia();
	paddle->GetPhysicsObject()->SetElasticity(2.0f);
	paddle->GetPhysicsObject()->SetGravity(false);
	paddle->GetPhysicsObject()->SetFriction(false);
	paddle->SetDynamic(true);
	world->AddGameObject(paddle);

	paddle->SetLayer(1);

	Spring* s = new Spring(0, 20.0f);
	
	SpringConstraint* spc = new SpringConstraint((GameObject*)paddle, target, s);
	world->AddConstraint(spc);

	LockOrientationConstraint* loc = new LockOrientationConstraint((GameObject*)paddle, paddle->GetTransform().GetOrientation());
	world->AddConstraint(loc);

	return paddle;

}

void LevelOne::InitFloor()
{
	// Start -> Checkpoint A
	//AddFloorToWorld(Vector3(0, -2, -90));
	AddCubeToWorld(Vector3(0, -2, -70), Vector3(20, 2, 80), false, 0.0f, 0);
	AddCubeToWorld(Vector3(19, 2, -70), Vector3(1, 2, 80), false, 0, 0); // Side wall
	AddCubeToWorld(Vector3(-19, 2, -70), Vector3(1, 2, 80), false, 0, 0); // Side wall

	GameObject* backwall = AddCubeToWorld(Vector3(80, -27.5, -190.5), Vector3(100, 5, 1), true, 0, 0); // Back Wall
	GameObject* backwall2 = AddCubeToWorld(Vector3(80, -27.5, -150.5), Vector3(100, 5, 1), true, 0, 0); // Back Wall
	backwall->GetTransform().SetOrientation(Quaternion(0.0f, 0.0f, -0.1f, 1.0f));
	backwall2->GetTransform().SetOrientation(Quaternion(0.0f, 0.0f, -0.1f, 1.0f));
	backwall->SetName("test");
	GameObject* cpA = AddCubeToWorld(Vector3(80, -32, -170), Vector3(100, 2, 20), true, 0.0f, 0);
	cpA->GetTransform().SetOrientation(Quaternion(0.0f, 0.0f, -0.1f, 1.0f));
	cpA->GetPhysicsObject()->SetFriction(false);
	cpA->GetRenderObject()->SetColour(Vector4(0.29f, 0.54f, 1.0f, 1.0f));
	cpA->GetRenderObject()->SetDefaultTexture(NULL);

	// Checkpoint A -> Checkpoint B
	//GameObject* water = AddCubeToWorld(Vector3(0, -50, -50), Vector3(20, 2, 100), true, 1.0f, 1);
	//water->GetPhysicsObject()->SetSpringRes(true);
	//water->GetRenderObject()->SetColour(Debug::BLUE);
	//GameObject* safety = AddCubeToWorld(Vector3(120, -6, -170), Vector3(100, 2, 20), true, 0.0f, 0); // Underneath
	//safety->GetPhysicsObject()->SetElasticity(1.5f);
	//AddCubeToWorld(Vector3(18, -6, -170), Vector3(2, 2, 20), true, 0.0f, 0);

#pragma region Spikes
	GameObject* cub1 = AddCubeToWorld(Vector3(30, -15, -170), Vector3(2, 10, 2), true, 0.0f, 0);
	cub1->GetTransform().SetOrientation(Quaternion(0.0f, 0.25f, -0.15f, 1.0f));
	cub1->GetPhysicsObject()->SetElasticity(1.5f);

	GameObject* cub2 = AddCubeToWorld(Vector3(50, -25, -180), Vector3(3, 10, 3), true, 0.0f, 0);
	cub2->GetTransform().SetOrientation(Quaternion::EulerAnglesToQuaternion(20.0f, 45.0f, 20.0f));
	cub2->GetPhysicsObject()->SetElasticity(1.5f);

	GameObject* cub3 = AddCubeToWorld(Vector3(80, -30, -160), Vector3(3, 10, 3), true, 0.0f, 0);
	cub3->GetTransform().SetOrientation(Quaternion::EulerAnglesToQuaternion(-70.0f, 45.0f, 20.0f));
	cub3->GetPhysicsObject()->SetElasticity(1.5f);

	GameObject* cap1 = AddCapsuleToWorld(Vector3(100, -35, -152), 5.0f, 2.5f, 0.0f);
	cap1->GetTransform().SetOrientation(Quaternion::EulerAnglesToQuaternion(-20.0f, 45.0f, -20.0f));
	cap1->GetPhysicsObject()->SetElasticity(1.5f);

	GameObject* cap2 = AddCapsuleToWorld(Vector3(80, -30, -180), 5.0f, 2.5f, 0.0f);
	cap2->GetTransform().SetOrientation(Quaternion::EulerAnglesToQuaternion(-20.0f, 45.0f, -20.0f));
	cap2->GetPhysicsObject()->SetElasticity(1.5f);

	GameObject* cap3 = AddCapsuleToWorld(Vector3(120, -42, -180), 10.0f, 5.0f, 0.0f);
	cap3->GetTransform().SetOrientation(Quaternion::EulerAnglesToQuaternion(80.0f, -10.0f, 0.0f));
	cap3->GetPhysicsObject()->SetElasticity(1.5f);

	AddSphereToWorld(Vector3(150, -44, -170), 2.0f, 0.0f, true);
	AddSphereToWorld(Vector3(160, -46, -176), 2.0f, 0.0f, true);
	AddSphereToWorld(Vector3(160, -46, -164), 2.0f, 0.0f, true);
	AddSphereToWorld(Vector3(170, -48, -182), 2.0f, 0.0f, true);
	AddSphereToWorld(Vector3(170, -48, -158), 2.0f, 0.0f, true);
	AddSphereToWorld(Vector3(170, -48, -170), 2.0f, 0.0f, true);
#pragma endregion

	GameObject* cpB = AddCubeToWorld(Vector3(198, -52, -170), Vector3(20, 2, 30), true, 0.0f, 0);
	cpB->GetTransform().SetOrientation(Quaternion(-0.02f, 0.0f, 0.0f, 1.0f));
	AddCubeToWorld(Vector3(218, -52, -170), Vector3(1, 5, 30), false, 0.0f, 0);
}

void LevelOne::AddPendulum(Vector3 anchorPosition, Vector3 headPos, float length, float halfHeight, float radius)
{
	Pendulum* pend = new Pendulum(); 
	CapsuleVolume* volume = new CapsuleVolume(halfHeight, radius);
	pend->SetBoundingVolume((CollisionVolume*)volume);

	pend->GetTransform()
		.SetScale(Vector3(radius*2, halfHeight, radius*2))
		.SetPosition(headPos)
		.SetOrientation(Quaternion(0.0f, 0.0f, 1.0f, 1));
	pend->SetLayer(1); // Pendulum Layer
	
	pend->SetRenderObject(new RenderObject(&pend->GetTransform(), capsuleMesh, basicTex, basicShader));
	pend->SetPhysicsObject(new PhysicsObject(&pend->GetTransform(), pend->GetBoundingVolume()));

	pend->GetPhysicsObject()->SetInverseMass(10.0f);
	pend->GetPhysicsObject()->InitCubeInertia();
	pend->SetDynamic(true);

	world->AddGameObject(pend);

	GameObject* anchor = AddCubeToWorld(anchorPosition, Vector3(1, 1, 1), false, 0.0f, 0);
	
	
	PositionConstraint* constraint = new PositionConstraint(anchor, pend, length);
	LockOrientationConstraint* constraintO = new LockOrientationConstraint(pend, pend->GetTransform().GetOrientation());
	world->AddConstraint(constraint);
	world->AddConstraint(constraintO);
}

