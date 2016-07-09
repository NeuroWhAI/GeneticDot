#pragma once


#include <memory>
#include <queue>




class Cell;
class Gene;


class CellPool
{
public:
	explicit CellPool(int chunkSize = 16);


protected:
	std::queue<std::shared_ptr<Cell>> m_pool;
	int m_chunkSize;


public:
	std::shared_ptr<Cell> acquireCell(const Gene* gene = nullptr);
	void releaseCell(std::shared_ptr<Cell> cell);
};

