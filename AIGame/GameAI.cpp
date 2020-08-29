#include "GameAI.h"


GameAI::GameAI(void)
{
		
}

GameAI::~GameAI(void)
{
}

//find the element of the array relating to the grid space
int GameAI::findInArray(int x, int z)
{
	int index = (x * 21) + z;

	return index;
}

//set start and goal grid positions and clear existing data from vectors
void GameAI::FindPath(int goalX, int goalZ, brainWaves* objectProperties)
{
	if(!objectProperties->initialisedStartGoal)
	{
		objectProperties->foundGoal = false;
		for (int i = 0; i < openList.size(); i++)
		{
			delete openList[i];
		}
		openList.clear();

		for (int i = 0; i < visitedList.size(); i++)
		{
			delete visitedList[i];
		}
		visitedList.clear();

		start.xPos = objectProperties->gridX;
		start.zPos = objectProperties->gridZ;
		
		
		goal.xPos = goalX;
		goal.zPos = goalZ;

		SetStartAndGoal(start, goal);
		objectProperties->initialisedStartGoal = true;

	}

	if(objectProperties->initialisedStartGoal)
	{
		ContinuePath(objectProperties);
	}

}

//assigns IDs to start and goal cells
void GameAI::SetStartAndGoal(CellStruct start, CellStruct goal)
{
	startCell = new CellStruct(start.xPos, start.zPos, NULL);
	goalCell = new CellStruct(goal.xPos, goal.zPos, &goal);

	startCell->cumulativeCost = 0;
	startCell->heuristic = startCell->ManhattanDistance(goalCell);
	startCell->parent = 0;

	openList.push_back(startCell);

}

//evaulates next best cell and assigns ID
CellStruct* GameAI::GetNextCell()
{
	cellIndex = -1;
	nextCell = NULL;
	bestHeuristic = 999;

	for (int i = 0; i < openList.size(); i++)
	{
		if(openList[i]->heuristic < bestHeuristic)
		{
			bestHeuristic = openList[i]->heuristic;
			cellIndex = i;
		}

	}

	if(cellIndex >= 0)
	{
		nextCell = openList[cellIndex];
		visitedList.push_back(nextCell);
		openList.erase(openList.begin() + cellIndex);
	}

	return nextCell;
}

//parses the surrounding cells to evauluate
void GameAI::PathOpened(int x, int z, float newCost, CellStruct* parent)
{
	int mazeArray[441] =  
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 
		 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 
		 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
		 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,
		 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 
		 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 
		 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 
		 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
		 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
		 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1,
		 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
		 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
		 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
		 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
		 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1};

	if(x < 0 || z < 0 || x > 21 || z > 21)
	{
		return;
	}

	if(mazeArray[findInArray(x, z)] == 1)
	{ 
		return;
	}

	_cellID = z * GRID_SIZE + x;

	for(int i = 0; i < visitedList.size(); i++)
	{
		if(_cellID == visitedList[i]->cellID)
		{
			return;
		}
	}

	newChild = new CellStruct(x, z, parent);
	newChild->cumulativeCost = newCost;
	newChild->heuristic = parent->ManhattanDistance(goalCell);

	for(int i = 0; i < openList.size(); i++)
	{
		if(_cellID == openList[i]->cellID)
		{
			newEvaluation = newChild->cumulativeCost + newCost + openList[i]->heuristic;
			if(openList[i]->evaluate() > newEvaluation)
			{
				openList[i]->cumulativeCost = newChild->cumulativeCost + newCost;
				openList[i]->parent = newChild;
			}
			else
			{
				return;
			}
			
		}
	}

	openList.push_back(newChild);
}

//loops until goal cell is found, then loads path into path array
void GameAI::ContinuePath(brainWaves* objectProperties)
{	
	if(openList.empty())
	{
		return;
	}

	currentCell = GetNextCell();

	if(currentCell->cellID == goalCell->cellID)
	{
		goalCell->parent = currentCell->parent;
		
		int i = 0;

		for(getPath = goalCell; getPath != NULL; getPath = getPath->parent)
		{
			path[i].xPos = getPath->xPos;
			path[i].zPos = getPath->zPos;
			i++;
		}

		objectProperties->nextGridX = path[i-2].xPos;
		objectProperties->nextGridZ = path[i-2].zPos;

		objectProperties->initialisedStartGoal = false;
		objectProperties->foundGoal = true;
		return;		
	}
	
	else
	{
		//Right
		PathOpened(currentCell->xPos + 1, currentCell->zPos, currentCell->cumulativeCost + 1, currentCell);
		//Left
		PathOpened(currentCell->xPos - 1, currentCell->zPos, currentCell->cumulativeCost + 1, currentCell);
		//Above
		PathOpened(currentCell->xPos, currentCell->zPos + 1, currentCell->cumulativeCost + 1, currentCell);
		//Below
		PathOpened(currentCell->xPos, currentCell->zPos - 1, currentCell->cumulativeCost + 1, currentCell);

		for(int i = 0; i < openList.size(); i++)
		{
			if(currentCell->cellID == openList[i]->cellID)
			{
				openList.erase(openList.begin() + i);
			}
		}

		if(!objectProperties->foundGoal) ContinuePath(objectProperties);
	}

}