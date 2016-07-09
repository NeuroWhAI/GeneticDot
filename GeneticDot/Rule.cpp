#include "Rule.h"

#include <cassert>
#include <cmath>
#include <algorithm>




Rule::Rule()
	: m_maxNearCount(0)
{

}


Rule::Rule(int maxNearCount)
	: m_maxNearCount(maxNearCount + 1)
	, m_survive(static_cast<size_t>(maxNearCount + 1), False)
	, m_birth(static_cast<size_t>(maxNearCount + 1), False)
	, m_antiBirth(static_cast<size_t>(maxNearCount + 1), False)
{

}

//###########################################################################

int Rule::getMaxNearCount() const
{
	return m_maxNearCount;
}


void Rule::setMaxNearCount(int maxNearCount)
{
#ifdef _DEBUG
	assert(maxNearCount >= 0);
#endif


	m_maxNearCount = maxNearCount + 1;

	m_survive.resize(static_cast<size_t>(maxNearCount + 1), False);
	m_birth.resize(static_cast<size_t>(maxNearCount + 1), False);
	m_antiBirth.resize(static_cast<size_t>(maxNearCount + 1), False);
}


bool Rule::checkSurvive(int nearCount) const
{
#ifdef _DEBUG
	assert(nearCount < m_maxNearCount && nearCount >= 0);
#endif


	return (m_survive[nearCount] != False);
}


bool Rule::checkBirth(int nearCount) const
{
#ifdef _DEBUG
	assert(nearCount < m_maxNearCount && nearCount >= 0);
#endif


	return (m_birth[nearCount] != False);
}


bool Rule::checkAntiBirth(int nearCount) const
{
#ifdef _DEBUG
	assert(nearCount < m_maxNearCount && nearCount >= 0);
#endif


	return (m_antiBirth[nearCount] != False);
}


void Rule::setSurvive(const NumList& rule)
{
	m_survive.clear();
	m_survive.resize(static_cast<size_t>(m_maxNearCount), False);

	for (auto nearCount : rule)
	{
#ifdef _DEBUG
		assert(nearCount < m_maxNearCount && nearCount >= 0);
#endif

		m_survive[nearCount] = True;
	}
}


void Rule::setBirth(const NumList& rule)
{
	m_birth.clear();
	m_birth.resize(static_cast<size_t>(m_maxNearCount), False);

	m_antiBirth.clear();
	m_antiBirth.resize(static_cast<size_t>(m_maxNearCount), False);


	for (auto nearCount : rule)
	{
#ifdef _DEBUG
		assert(std::abs(nearCount) < m_maxNearCount);
#endif

		if (nearCount >= 0)
		{
			m_birth[nearCount] = True;
		}
		else
		{
			m_antiBirth[-nearCount] = True;
		}
	}
}

//###########################################################################

void Rule::accumulate(const Rule& other)
{
	const int minSize = std::min(m_maxNearCount, other.m_maxNearCount);

	for (int i = 0; i < minSize; ++i)
	{
		m_survive[i] = (m_survive[i] | other.m_survive[i]);
		m_birth[i] = ((m_birth[i] | other.m_birth[i]) & (!other.m_antiBirth[i]));
		m_antiBirth[i] = (m_antiBirth[i] | other.m_antiBirth[i]);
	}


	if (m_maxNearCount < other.m_maxNearCount)
	{
		m_survive.insert(m_survive.end(),
			other.m_survive.begin() + minSize,
			other.m_survive.end());

		m_birth.insert(m_birth.end(),
			other.m_birth.begin() + minSize,
			other.m_birth.end());

		m_antiBirth.insert(m_antiBirth.end(),
			other.m_antiBirth.begin() + minSize,
			other.m_antiBirth.end());
	}
}


Rule Rule::combine(const Rule& other) const
{
	const int minSize = std::min(m_maxNearCount, other.m_maxNearCount);
	const int maxSize = std::max(m_maxNearCount, other.m_maxNearCount);

	Rule temp{ maxSize - 1 };


	for (int i = 0; i < minSize; ++i)
	{
		temp.m_survive[i] = (m_survive[i] | other.m_survive[i]);
		if (temp.m_antiBirth[i] == other.m_antiBirth[i])
			temp.m_birth[i] = ((m_birth[i] & other.m_birth[i]) & (!m_antiBirth[i]) & (!other.m_antiBirth[i]));
		else
			temp.m_birth[i] = ((m_birth[i] | other.m_birth[i]) & (!m_antiBirth[i]) & (!other.m_antiBirth[i]));
		temp.m_antiBirth[i] = (m_antiBirth[i] & other.m_antiBirth[i]);
	}


	if (minSize < maxSize)
	{
		const Rule* bigRule = ((m_maxNearCount > other.m_maxNearCount) ? this : &other);

		temp.m_survive.insert(temp.m_survive.end(),
			bigRule->m_survive.begin() + minSize,
			bigRule->m_survive.end());

		temp.m_birth.insert(temp.m_birth.end(),
			bigRule->m_birth.begin() + minSize,
			bigRule->m_birth.end());

		temp.m_antiBirth.insert(temp.m_antiBirth.end(),
			bigRule->m_antiBirth.begin() + minSize,
			bigRule->m_antiBirth.end());
	}


	return temp;
}

//###########################################################################

bool Rule::equals(const Rule& right) const
{
	if (m_maxNearCount != right.m_maxNearCount)
	{
		return false;
	}


	for (int i = 0; i < m_maxNearCount; ++i)
	{
		if (m_survive[i] != right.m_survive[i])
		{
			return false;
		}

		if (m_birth[i] != right.m_birth[i])
		{
			return false;
		}

		if (m_antiBirth[i] != right.m_antiBirth[i])
		{
			return false;
		}
	}


	return true;
}

