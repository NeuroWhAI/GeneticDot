#include "DrawableWorld.h"

#include <CodeAdapter\EasyCA.h>

#include "Cell.h"
#include "Gene.h"




DrawableWorld::DrawableWorld()
	: m_cellSize(16)
{

}

//###########################################################################

void DrawableWorld::onDraw(Graphics& g, const Transform& parentTransform)
{
	auto& rectArtist = g.rectangleArtist;


	rectArtist->beginFillRectangle();

	for (const auto& cell : m_cellList)
	{
		const auto* gene = m_cellBoard[cell.y][cell.x]->getGene();

		rectArtist->fillRectangle(cell.x * m_cellSize, cell.y * m_cellSize,
			m_cellSize, m_cellSize,
			gene->getColor());
	}

	rectArtist->endFillRectangle();
}

//###########################################################################

void DrawableWorld::setCellSize(float cellSize)
{
	m_cellSize = cellSize;
}

