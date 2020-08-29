#pragma once

#include "CellStruct.h"
#include <vector>




struct brainWaves
{
	float posX;
	float posZ;
	int gridX;
	int gridZ;
	int nextGridX;
	int nextGridZ;
	float speed;
	CellStruct fleeSpace[10];
	int previousGridX;
	int previousGridZ;

	bool initialisedStartGoal;
	bool foundGoal;
	bool hit;

	
};

class GameAI
{
	public: 
			
		GameAI(void);
		~GameAI(void);
		int GameAI::findInArray(int x, int z);
		void FindPath(int goalX, int goalZ, brainWaves* objectProperties);
		void ClearOpenList()
		{
			openList.clear();
		}
		void ClearVisitedList()
		{
			visitedList.clear();
		}
		enum state{pursue, flee, kill};
		state enemyState;
	private:

		void SetStartAndGoal(CellStruct start, CellStruct goal);
		void PathOpened(int x, int z, float newCost, CellStruct* parent);
		CellStruct* GetNextCell();
		void ContinuePath(brainWaves* objectProperties);
		CellStruct* startCell;
		CellStruct* goalCell;
		CellStruct* currentCell;
		CellStruct* getPath;
		CellStruct start;
		CellStruct goal;
		CellStruct* newChild;

		CellStruct path[100];
		
		CellStruct cells[100][100];


		float newEvaluation;
		float bestEvaluation;
		int bestHeuristic;
		int cellIndex;
		CellStruct* nextCell;
		int _cellID;
		
		std::vector<CellStruct*> openList;
		std::vector<CellStruct*> visitedList;
};
