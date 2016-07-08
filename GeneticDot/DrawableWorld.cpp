#include "DrawableWorld.h"

#include <CodeAdapter\EasyCA.h>




DrawableWorld::DrawableWorld()
	: m_cellSize(16)
{

}

//###########################################################################

void DrawableWorld::onDraw(Graphics& g, const Transform& parentTransform)
{
	auto& rectArtist = g.rectangleArtist;


	rectArtist->beginFillRectangle();

	const int height = m_cellBoard.size();

	for (int y = 0; y < height; ++y)
	{
		const int width = m_cellBoard[y].size();

		for (int x = 0; x < width; ++x)
		{
			if (m_cellBoard[y][x] != nullptr)
			{
				rectArtist->fillRectangle(x * m_cellSize, y * m_cellSize,
					m_cellSize, m_cellSize,
					caDraw::Color::Gray);
			}
		}
	}

	rectArtist->endFillRectangle();
}

//###########################################################################

void DrawableWorld::setCellSize(float cellSize)
{
	m_cellSize = cellSize;
}

