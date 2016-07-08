#pragma once


#include <memory>
#include <vector>

#include <CodeAdapter\Point.h>

#include "Gene.h"




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
	std::vector<Gene> m_geneList;
	BoardType<std::unique_ptr<Cell>> m_cellBoard;
	std::vector<Point> m_cellList;


public:
	void initialize(int boardSize);
	void update();


public:
	const Gene* addGene(const Gene& gene);
	void setCell(const Gene* gene, const Point& position);
	void clearCell(const Point& position);
};

