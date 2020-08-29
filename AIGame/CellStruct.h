#pragma once

#include <math.h>
#define GRID_SIZE 21

struct CellStruct
{
	public:
		int xPos;
		int zPos;
		int cellID;
		CellStruct* parent;
		float cumulativeCost;
		float heuristic;

		CellStruct(): parent(0) 
		{
		
		};

		CellStruct(int x, int z, CellStruct*_parent = 0) : xPos(x), zPos(z), parent(_parent), cellID(z * GRID_SIZE + x), cumulativeCost(0), heuristic(0)
		{

		};

		float evaluate()
		{
			return cumulativeCost + heuristic; 
		};

		float ManhattanDistance(CellStruct* nodeEnd)
		{
			float a = (float)(fabs((float)(this->xPos - nodeEnd->xPos)));
			float b = (float)(fabs((float)(this->zPos - nodeEnd->zPos)));
			return a + b;
		}
};