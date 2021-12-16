#pragma once
#include "GameObject.h"
#include "../CSC8503Common/NavigationGrid.h"
#include "Player.h"

namespace NCL {
	namespace CSC8503 {

		class StateMachine;
		class StateAI : public GameObject
		{
		public:
			StateAI(NavigationGrid* navGrid, Player* player, vector<GameObject*> powerups);
			~StateAI();

			virtual void Update(float dt);

		protected:
			StateMachine* rootMachine;
			StateMachine* roamMachine;
			StateMachine* guardMachine;

			void Wander(float dt);
			void ChasePlayer(float dt);
			void GetPowerUp(float dt);

			NavigationGrid* grid;
			NavigationPath path;
			Transform target;
			float refreshPathTime = 3.0f;
			float wanderTime = 10.0f;
			float currentTime = 10.0f;

			GameObject* target;

			Player* player;
			vector<GameObject*> powerups;
		};
	}
}


