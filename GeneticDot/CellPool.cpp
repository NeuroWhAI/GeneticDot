#include "CellPool.h"

#include "Cell.h"




CellPool::CellPool(int chunkSize)
	: m_chunkSize(chunkSize)
{

}

//###########################################################################

std::shared_ptr<Cell> CellPool::acquireCell(const Gene* gene)
{
	if (m_pool.empty())
	{
		for (int i = 0; i < m_chunkSize; ++i)
		{
			m_pool.push(std::make_shared<Cell>());
		}
	}


	auto cell = m_pool.front();
	m_pool.pop();

	
	cell->reset(gene);


	return cell;
}


void CellPool::releaseCell(std::shared_ptr<Cell> cell)
{
	if (cell != nullptr)
	{
		cell->reset(nullptr);


		m_pool.push(cell);
	}
}

