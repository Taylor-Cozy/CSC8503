#pragma once

namespace NCL {
	namespace CSC8503 {

		class Spring {
		public:
			Spring(float length, float k) : length(length), k(k) {}

			float GetLength() const { return length; }
			float GetK() const { return k; }

		protected:
			float length;
			float k;
		};
	}
}

