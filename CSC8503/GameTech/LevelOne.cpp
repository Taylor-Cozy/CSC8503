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
	//world->AddLayerConstraint(Vector2(0, 1));
	world->ClearAndErase();
	physics->Clear();

	//GameObject* a = AddCubeToWorld(Vector3(0, 1.5f, 0), Vector3(1, 1, 1));
	//a->GetTransform().SetOrientation(Quaternion(0, 0.25f, 0, 1.0f));
	//GameObject* b = AddCubeToWorld(Vector3(10, 1.5f, 0), Vector3(1, 1, 1));
	//b->GetTransform().SetOrientation(Quaternion(0.25f, 0, 0, 1.0f));

	//AddCubeToWorld(Vector3(10, 2, 0), Vector3(1, 1, 1), true);

	InitFloor();

	GameObject* startLine = AddCubeToWorld(Vector3(0, 0.1f, -10), Vector3(20, 0.2f, 3), false, 0, 0, true);
	startLine->GetRenderObject()->SetColour(Vector4(0, 1, 0, 1));

	//GameObject* paddle = AddCubeToWorld(Vector3(0, 2, 2), Vector3(10, 2, 1), false, 0.1f);
	AddPaddleToWorld(Vector3(0, 2, 2), Vector3(10, 2, 1), Vector3(0, 0, -1), 10000.0f, 30.0f, new Vector3(0, 2, 2));

	//AddCapsuleToWorld(Vector3(0, 3.5f, -50), 3, 1.5f, 10.0f);
	AddPendulum(Vector3(0, 20, -50), Vector3(0, 3.5f, -50), 18, 3.0f, 1.5f);
	AddPendulum(Vector3(0, 20, -80), Vector3(10, 3.5f, -80), 18, 3.0f, 1.5f);
	AddPendulum(Vector3(0, 20, -110), Vector3(-10, 3.5f, -110), 18, 3.0f, 1.5f);

	GameObject* player = AddSphereToWorld(Vector3(0,2,0), 1.0f, 50.0f, true);
	player->GetPhysicsObject()->SetFriction(0.3f);
	player->SetLayer(1);
	player->GetRenderObject()->SetDefaultTexture(playerTex);
	world->AddLayerConstraint(Vector2(-1, 99));
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
	
	world->AddGameObject(paddle);

	paddle->SetLayer(1);

	Spring* s = new Spring(0, 50.0f);
	
	SpringConstraint* spc = new SpringConstraint((GameObject*)paddle, target, s);
	world->AddConstraint(spc);

	LockOrientationConstraint* loc = new LockOrientationConstraint((GameObject*)paddle, paddle->GetTransform().GetOrientation());
	world->AddConstraint(loc);

	return paddle;

}

void LevelOne::InitFloor()
{
	// Start
	AddFloorToWorld(Vector3(0, -2, -90));
	AddCubeToWorld(Vector3(19, 2, -70), Vector3(1, 2, 80), false, 0, 0); // Side wall
	AddCubeToWorld(Vector3(-19, 2, -70), Vector3(1, 2, 80), false, 0, 0); // Side wall
	AddCubeToWorld(Vector3(0, 2, -190), Vector3(20, 2, 1), false, 0, 0); // Back Wall

	// Checkpoint A -> Checkpoint B
	GameObject* water = AddCubeToWorld(Vector3(120, -2, -170), Vector3(100, 2, 20), true, 0.0f, 0);
	water->GetPhysicsObject()->SetSpringRes(true);
	water->GetRenderObject()->SetColour(Debug::BLUE);
	GameObject* safety = AddCubeToWorld(Vector3(120, -6, -170), Vector3(100, 2, 20), true, 0.0f, 0); // Underneath
	safety->GetPhysicsObject()->SetElasticity(1.5f);
	AddCubeToWorld(Vector3(18, -6, -170), Vector3(2, 2, 20), true, 0.0f, 0);

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

	world->AddGameObject(pend);

	GameObject* anchor = AddCubeToWorld(anchorPosition, Vector3(1, 1, 1), false, 0.0f, 0);
	
	PositionConstraint* constraint = new PositionConstraint(anchor, pend, length);
	LockOrientationConstraint* constraintO = new LockOrientationConstraint(pend, pend->GetTransform().GetOrientation());
	world->AddConstraint(constraint);
	world->AddConstraint(constraintO);
}

