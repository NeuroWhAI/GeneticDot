#pragma once


#include <memory>
#include <vector>

#include <CodeAdapter\Point.h>

#include "Gene.h"
#include "CellPool.h"




class Cell;


class World
{
private:
	USING_CA_DRAWING(Point);

	template <typename T>
	using BoardType = std::vector<std::vector<T>>;


public:
	World();
	virtual ~World();


protected:
	std::vector<std::unique_ptr<Gene>> m_geneList;
	BoardType<std::shared_ptr<Cell>> m_cellBoard;
	std::vector<Point> m_cellList;


private:
	CellPool m_cellPool;
	std::vector<size_t> m_tempDeathList;
	std::vector<Point> m_tempBirthList;
	std::vector<const Gene*> m_tempBirthInfoList;


public:
	void initialize(int boardSize);
	void update();


public:
	const Gene* addGene(const Gene& gene);
	void setCell(const Gene* gene, const Point& position);
	void clearCell(const Point& position);


protected:
	int checkGeneOverlap(const Gene& gene) const;
};

