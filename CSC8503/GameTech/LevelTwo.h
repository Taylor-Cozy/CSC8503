#pragma once
#include "TutorialGame.h"

namespace NCL {
	namespace CSC8503 {
		class LevelTwo : public TutorialGame
		{
		public:
			LevelTwo() {
				InitWorld();
			}
			virtual ~LevelTwo() {};

		protected:
			virtual void InitWorld() override;

			void InitFloor();
			void InitWalls();
		};
	}
}

