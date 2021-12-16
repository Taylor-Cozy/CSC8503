#include "StateAI.h"
#include "StateTransition.h"
#include "StateMachine.h"
#include "State.h"
#include "SpeedUp.h"

using namespace NCL;
using namespace CSC8503;

StateAI::StateAI(NavigationGrid* navGrid, Player* player, vector<GameObject*> powerups)
{
	this->player = player;
	this->powerups = powerups;
	grid = navGrid;
	target = powerups[0];

	rootMachine = new StateMachine();
	roamMachine = new StateMachine();
	guardMachine = new StateMachine();

#pragma region root level
	// Root level
	State* groupA_keyNotFound = new State([&](float dt)->void {
		std::cout << "Roaming..." << std::endl;
		roamMachine->Update(dt);
		}
	);

	State* groupB_keyFound = new State([&](float dt)->void {
		std::cout << "Guarding..." << std::endl;
		guardMachine->Update(dt);
		}
	);

	StateTransition* stateGroupAGroupB = new StateTransition(groupA_keyNotFound, groupB_keyFound, [&](void)->bool {
		return player->HasKey();
		});

	StateTransition* stateGroupBGroupA = new StateTransition(groupB_keyFound, groupA_keyNotFound, [&](void)->bool {
		return !player->HasKey();
	});

	rootMachine->AddState(groupA_keyNotFound);
	rootMachine->AddState(groupB_keyFound);

	rootMachine->AddTransition(stateGroupAGroupB);
	rootMachine->AddTransition(stateGroupBGroupA);

#pragma endregion

#pragma region Group A - Key Not Found

	State* wander = new State([&](float dt)->void {
		Wander(dt);
		});

	State* chasePlayer = new State([&](float dt)->void {
		ChasePlayer(dt);
		});

	State* getPowerUp = new State([&](float dt)->void {
		GetPowerUp(dt);
		});

#pragma endregion
	// States
	// Heirarchal Group A - Key not found
	// State Wander through maze


	// Chase player
	// Go to powerup

	// Heirarchal Group B - key found
	// Guard gate
	// Chase player

	// Transitions
	// Heirarchal Group A -> B	: Key found
	
	// Wander -> Chase Player		: Player within range
	// Chase Player -> Wander		: Player out of range

	// Wander -> Get powerup		: Powerup within certain range
	// Get powerup -> Wander		: Powerup gone

	// Chase player -> Get powerup	: Powerup within certain range
	// Get powerup -> Chase Player	: Power up gone / Player within certain range

	// Guard -> Chase Player		: Player within range
	// Chase Player -> Guard		: Player out of range
}

StateAI::~StateAI()
{
}

void StateAI::Update(float dt)
{
}

void StateAI::Wander(float dt)
{
	currentTime -= dt;
	if (currentTime < 0.0f) {
		currentTime = refreshPathTime;
		// Pick a new point
		bool found = false;
		while (!found) {
			path.Clear();
			Vector3 newPoint(rand() % 360, 1, rand() % 360);
			found = grid->FindPath(transform.GetPosition(), newPoint, path);
		}
	}
}

void StateAI::ChasePlayer(float dt)
{
	currentTime -= dt;
	if (currentTime < 0.0f) {
		currentTime = refreshPathTime;
		// Pick new point
		path.Clear();
		grid->FindPath(transform.GetPosition(), player->GetTransform().GetPosition(), path);
	}
}

void StateAI::GetPowerUp(float dt)
{
	currentTime -= dt;
	if (currentTime < 0.0f) {
		currentTime = refreshPathTime;
		Vector3 endPos = ((SpeedUp*)target)->GetTransform().GetPosition();
		path.Clear();
		grid->FindPath(transform.GetPosition(), endPos, path);
	}
}
