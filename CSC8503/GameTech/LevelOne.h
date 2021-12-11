#pragma once
#include "TutorialGame.h"

namespace NCL {
	namespace CSC8503 {
		class LevelOne : public TutorialGame
		{
		public:
			LevelOne() {
				InitWorld();
			};
			virtual ~LevelOne() {};

		protected:
			virtual void InitWorld() override;
		};
	}
}


