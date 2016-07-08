#include "Cell.h"

#include <cassert>

#include "Gene.h"




Cell::Cell()
	: m_gene(nullptr)
	, m_step(0)
	, m_count(0)
{

}


Cell::Cell(const Gene* gene)
	: m_gene(gene)
	, m_step(0)
	, m_count(0)
{

}

//###########################################################################

void Cell::reset(const Gene* gene)
{
	m_gene = gene;
	m_step = 0;
	m_count = 0;
}


void Cell::update()
{
#ifdef _DEBUG
	assert(m_gene != nullptr);
#endif

	
	++m_count;

	if (m_count > m_gene->getDelay(m_step))
	{
		m_count = 0;

		++m_step;
	}
}

//###########################################################################

const Gene* Cell::getGene() const noexcept
{
	return m_gene;
}


bool Cell::isDie() const
{
#ifdef _DEBUG
	assert(m_gene != nullptr);
#endif


	return (!m_gene->stepExists(m_step));
}


bool Cell::checkSurvive(int nearCount) const
{
	return m_gene->checkSurvive(m_step, nearCount);
}


bool Cell::checkBirth(int nearCount) const
{
	return m_gene->checkBirth(m_step, nearCount);
}

