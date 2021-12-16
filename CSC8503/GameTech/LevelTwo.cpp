#include "LevelTwo.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace NCL;
using namespace CSC8503;

void LevelTwo::InitWorld()
{
	world->ClearAndErase();
	physics->Clear();

	player = AddPlayerBallToWorld(Vector3(20, 2, 20));

	InitFloor();
	InitWalls();

	state = PLAY;

	world->BuildStaticList();
}

void LevelTwo::InitFloor()
{
	AddCubeToWorld(Vector3(180, -2, 180), Vector3(180, 2, 180), false, 0.0f, 0);
}

void LevelTwo::InitWalls()
{

	std::ifstream file;
	file.open("../../Assets/Data/TestGrid1.txt");

	string line;
	vector<string> lines;
	while (std::getline(file, line)) {
		lines.emplace_back(line);
	}

	for (auto x : lines) {
		std::cout << x << std::endl;
	}

	int offset = 20;

	for (int i = 3; i < lines.size(); ++i) {
		for (int j = 0; j < lines[3].length(); ++j) {
			if (lines[i][j] == 'x') {
				GameObject* x = AddCubeToWorld(Vector3((offset * (j)) + 10, 10, (offset * (i-3)) + 10), Vector3(10, 10, 10), false, 0.0f, 0);
				x->GetRenderObject()->SetColour(Vector4((1.0f * j) / (float)stoi(lines[1]), 0.2f, (1.0f * i) / (float)stoi(lines[2]), 1.0f));
				x->GetRenderObject()->SetDefaultTexture(NULL);
			}
		}
	}

	//// Top wall
	//for (int i = 0; i < 18; ++i) {
	//	AddCubeToWorld(Vector3((offset * i) + 10, 10, 10), Vector3(10, 10, 10), false, 0.0f, 0);
	//}
	//// Bottom wall
	//for (int i = 0; i < 18; ++i) {
	//	AddCubeToWorld(Vector3((offset * i) + 10, 10, 350), Vector3(10, 10, 10), false, 0.0f, 0);
	//}

	//// Left Wall
	//for (int i = 1; i < 17; ++i) {
	//	AddCubeToWorld(Vector3(10, 10, (offset * i) + 10), Vector3(10, 10, 10), false, 0.0f, 0);
	//}

	//// Right Wall
	//for (int i = 1; i < 17; ++i) {
	//	AddCubeToWorld(Vector3(350, 10, (offset * i) + 10), Vector3(10, 10, 10), false, 0.0f, 0);
	//}

	//AddCubeToWorld(Vector3(90, 10, 30), Vector3(10, 10, 10), false, 0.0f, 0);
}
