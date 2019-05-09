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
	// Two 2d arrays
	// What is seen on screen
	int* m_output;
	// current state of cell
	int* m_state;
protected:
	virtual bool OnUserCreate() {
		m_output = new int[ScreenWidth() * ScreenHeight()];
		m_state = new int[ScreenWidth() * ScreenHeight()];
		memset(m_output, 0, ScreenWidth() * ScreenHeight() * sizeof(int));
		memset(m_state, 0, ScreenWidth() * ScreenHeight() * sizeof(int));

		for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
			m_state[i] = rand() % 2;

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) {
		auto cell = [&](int x, int y) {
			return m_output[y * ScreenWidth() + x];
		};

		// Store output state
		for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
			m_output[i] = m_state[i];

		// Iterate through cells; no boards to avoid reading mem that is not there
		for (int x = 1; x < ScreenWidth() - 1; x++)
			for (int y = 1; y < ScreenHeight() - 1; y++) {
				// Count Neighbours
				int nNeighbours = cell(x - 1, y - 1) + cell(x + 0, y - 1) + cell(x + 1, y - 1) +
								  cell(x - 1, y + 0) +			0		  + cell(x + 1, y - 0) +
								  cell(x - 1, y + 1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

				// Rules if cell alive
				// < 2 neighbours: dies from lonliness OR > 3 neighbours: dies from overcrowding
				if (cell(x, y) == 1)
					m_state[y * ScreenWidth() + x] = nNeighbours == 2 || nNeighbours == 3;
				// Rules for cell dead
				// if dead cell has 3 neighbours, produce new cell 
				else
					m_state[y * ScreenWidth() + x] = nNeighbours == 3;

				// Draw
				if (cell(x, y) == 1)
					Draw(x, y, PIXEL_SOLID, FG_WHITE);
				else
					Draw(x, y, PIXEL_SOLID, FG_BLACK);
			}
		
		return true;
	}
};

int main() {
	srand(clock());

	GameofLife game;
	game.ConstructConsole(80, 50, 8, 8);
	game.Start();

	return 0;
}