#include "World.h"

#include <cassert>
#include <algorithm>

#include "Cell.h"




World::World()
{

}


World::~World() = default;

//###########################################################################

void World::initialize(int boardSize)
{
#ifdef _DEBUG
	assert(boardSize > 0);
#endif


	m_cellBoard.resize(static_cast<size_t>(boardSize));

	for (auto& arr : m_cellBoard)
	{
		arr.resize(static_cast<size_t>(boardSize));
	}
}


void World::update()
{
	std::vector<size_t> deathList;

	std::vector<Point> birthList;
	std::vector<const Gene*> birthInfoList;


	for (size_t c = 0; c < m_cellList.size(); ++c)
	{
		const auto& center = m_cellList[c];
		int y = center.y;
		int x = center.x;

		auto& cell = m_cellBoard[center.y][center.x];


		// 셀 갱신
		cell->update();


		// 살아있는 인접 셀의 개수를 기준으로 현재 셀의 생사 결정
		int nearY[8] = {
			y - 1, y - 1, y - 1, y, y + 1, y + 1, y + 1, y
		};
		int nearX[8] = {
			x - 1, x, x + 1, x + 1, x + 1, x, x - 1, x - 1
		};

		int nearCount = 0;

		for (int n = 0; n < 8; ++n)
		{
			int nY = nearY[n];
			int nX = nearX[n];

			if (nY >= 0 && static_cast<size_t>(nY) < m_cellBoard.size()
				&& nX >= 0 && static_cast<size_t>(nX) < m_cellBoard[nY].size())
			{
				if (m_cellBoard[nY][nX] != nullptr)
				{
					++nearCount;
				}
				else
				{
					// 죽어있는 인접 셀의 인접 셀을 기준으로 생사 결정

					int nearY2[8] = {
						nY - 1, nY - 1, nY - 1, nY, nY + 1, nY + 1, nY + 1, nY
					};
					int nearX2[8] = {
						nX - 1, nX, nX + 1, nX + 1, nX + 1, nX, nX - 1, nX - 1
					};

					int nearCount2 = 0;

					for (int n2 = 0; n2 < 8; ++n2)
					{
						int nY2 = nearY2[n2];
						int nX2 = nearX2[n2];

						if (nY2 >= 0 && static_cast<size_t>(nY2) < m_cellBoard.size()
							&& nX2 >= 0 && static_cast<size_t>(nX2) < m_cellBoard[nY2].size())
						{
							if (m_cellBoard[nY2][nX2] != nullptr)
							{
								++nearCount2;
							}
						}
					}

					// 부활 가능한 상태인 셀은 살아남.
					if (cell->checkBirth(nearCount2))
					{
						birthList.emplace_back(nX, nY);
						birthInfoList.emplace_back(cell->getGene());
					}
				}
			}
		}

		// 지속 불가 상태인 셀이거나
		// 수명이 다한 셀은 죽음.
		if (cell->checkSurvive(nearCount) == false
			|| cell->isDie())
		{
			deathList.emplace_back(c);
		}
	}


	// 발생한 탄생 이벤트 적용
	const size_t birthCount = std::min(birthList.size(), birthInfoList.size());
	for (size_t b = 0; b < birthCount; ++b)
	{
		const auto& position = birthList[b];
		const auto& gene = birthInfoList[b];

		auto& cell = m_cellBoard[position.y][position.x];

		if (cell == nullptr)
		{
			setCell(gene, position);
		}
		else if (cell->getGene() != gene)
		{
			// 새로운 유전자 생성
			Gene newGene = *cell->getGene();
			newGene.combine(*gene);

			m_geneList.emplace_back(std::move(newGene));

			// The newGene is invalid now.

			cell->reset(&m_geneList[m_geneList.size() - 1]);
		}
	}

	// 발생한 죽음 이벤트 적용
	const size_t deathCount = deathList.size();
	for (size_t d = 0; d < deathCount; ++d)
	{
		// deathList의 인덱스들은 정렬된 상태임.

		size_t index = deathList[d] - d;
		
		clearCell(m_cellList[index]);

		m_cellList.erase(m_cellList.begin() + index);
	}
}

//###########################################################################

const Gene* World::addGene(const Gene& gene)
{
	m_geneList.emplace_back(gene);


	return &m_geneList[m_geneList.size() - 1];
}


void World::setCell(const Gene* gene, const Point& position)
{
	if (m_cellBoard[position.y][position.x] == nullptr)
	{
		m_cellBoard[position.y][position.x] = std::make_unique<Cell>(gene);
		m_cellList.emplace_back(position);
	}
	else
	{
		m_cellBoard[position.y][position.x]->reset(gene);
	}
}


void World::clearCell(const Point& position)
{
	if (m_cellBoard[position.y][position.x] != nullptr)
	{
		m_cellBoard[position.y][position.x].reset();
	}
}

