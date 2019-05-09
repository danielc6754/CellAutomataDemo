/*
	Cellular Automata Algorithm general logic
	cell directly connected to neighbours and can interact with neighbours
	every cell in grid operates a program, runngin identical programs
	operate on local data, each cell contains memory
		- for this demo is either on or off
	all programs are synchronized

	Above describes SIMD behavior 
	SIMD + Neighbour communications results in Cellular automata

	Treat all cells at an epoch at a time
*/
using namespace std;

#include "ConsoleEngine.h"

class GameofLife :public ConsoleTemplateEngine {
public:
	GameofLife() {
		m_sAppName = L"Cellular Automata Demo";
	}
private:
protected:
	virtual bool OnUserCreate() {
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) {
		// Count Neighbours

		// Rules if cell alive
		// < 2 neighbours: dies from lonlies
		//  > 3 neighbours: dies from overcrowding
		// else stays alive

		// Rules for cell dead
		// if dead cell has 3 neighbours, produce new cell 
		
		return true;
	}
};

int main() {
	GameofLife game;
	game.ConstructConsole(80, 50, 8, 8);
	game.Start();

	return 0;
}