#include "Gene.h"

#include <cassert>
#include <algorithm>




Gene::Gene()
{

}

//###########################################################################

bool Gene::checkSurvive(int step, int nearCount) const
{
#ifdef _DEBUG
	assert(step >= 0);
#endif


	if (static_cast<size_t>(step) < m_gene.size())
	{
		return m_gene[step].rule.checkSurvive(nearCount);
	}
	else
	{
		return false;
	}
}


bool Gene::checkBirth(int step, int nearCount) const
{
#ifdef _DEBUG
	assert(step >= 0);
#endif


	if (static_cast<size_t>(step) < m_gene.size())
	{
		return m_gene[step].rule.checkBirth(nearCount);
	}
	else
	{
		return false;
	}
}


int Gene::getDelay(int step) const
{
#ifdef _DEBUG
	assert(step >= 0 && static_cast<size_t>(step) < m_gene.size());
#endif


	return m_gene[step].delay;
}


bool Gene::stepExists(int step) const
{
#ifdef _DEBUG
	assert(step >= 0);
#endif


	return (static_cast<size_t>(step) < m_gene.size());
}

//###########################################################################

void Gene::appendUnit(const Rule& rule, int delay)
{
	m_gene.emplace_back(rule, delay);
}


void Gene::combine(const Gene& other)
{
	const size_t minSize = std::min(m_gene.size(), other.m_gene.size());

	for (size_t g = 0; g < minSize; ++g)
	{
		m_gene[g].rule = m_gene[g].rule.combine(other.m_gene[g].rule);
		m_gene[g].delay = (m_gene[g].delay + other.m_gene[g].delay) / 2;
	}
}

