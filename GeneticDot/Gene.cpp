#include "Gene.h"

#include <cassert>
#include <algorithm>




Gene::Gene()
	: m_color(Color::Transparent)
{

}

//###########################################################################

void Gene::initializeRandomly(std::mt19937& engine, int maxNearCount)
{
	m_gene.clear();


	std::normal_distribution<> sizeDist{ 1.0, 32.0 };

	double dSize = sizeDist(engine);
	int size = 0;
	if (dSize < 1)
		size = 1;
	else if (dSize > 128)
		size = 128;
	else
		size = static_cast<int>(dSize);

	
	std::normal_distribution<> delayDist{ 1000.0, 1000000.0 };

	for (int i = 0; i < size; ++i)
	{
		Unit unit;

		double dDelay = delayDist(engine);
		if (dDelay < 1)
			unit.delay = 1;
		else if (dDelay > 4000000)
			unit.delay = 4000000;
		else
			unit.delay = static_cast<int>(dDelay);

		unit.rule.initializeRandomly(engine, maxNearCount);

		m_gene.emplace_back(unit);
	}


	updateColor();
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


bool Gene::equals(const Gene& right) const
{
	if (m_color != right.m_color)
	{
		return false;
	}


	if (m_gene.size() != right.m_gene.size())
	{
		return false;
	}


	for (size_t i = 0; i < m_gene.size(); ++i)
	{
		if (m_gene[i].delay != right.m_gene[i].delay)
		{
			return false;
		}


		if (!m_gene[i].rule.equals(right.m_gene[i].rule))
		{
			return false;
		}
	}


	return true;
}

//###########################################################################

void Gene::appendUnit(const Rule& rule, int delay)
{
	m_gene.emplace_back(rule, delay);


	updateColor();
}


void Gene::combine(const Gene& other)
{
	const size_t minSize = std::min(m_gene.size(), other.m_gene.size());

	for (size_t g = 0; g < minSize; ++g)
	{
		m_gene[g].rule = m_gene[g].rule.combine(other.m_gene[g].rule);
		m_gene[g].delay = (m_gene[g].delay + other.m_gene[g].delay) / 2;
	}


	if (m_gene.size() < other.m_gene.size())
	{
		m_gene.insert(m_gene.end(),
			other.m_gene.begin() + minSize,
			other.m_gene.end());
	}


	updateColor();
}

//###########################################################################

void Gene::updateColor()
{
	m_color.a = 255;
	m_color.r = 0;
	m_color.g = 0;
	m_color.b = 0;


	for (size_t g = 0; g < m_gene.size(); ++g)
	{
		const auto& rule = m_gene[g].rule;


		const int count = rule.getMaxNearCount();

		for (int i = 1; i < count; ++i)
		{
			m_color.r += (rule.checkAntiBirth(i) ? i * 16 : 0);
			m_color.g += (rule.checkBirth(i) ? i * 16 : 0);
			m_color.b += (rule.checkSurvive(i) ? i * 16 : 0);

			while (m_color.r > 255)
			{
				m_color.r = 255;
			}

			while (m_color.g > 255)
			{
				m_color.g = 255;
			}

			while (m_color.b > 255)
			{
				m_color.b = 255;
			}
		}
	}
}

//###########################################################################

auto Gene::getColor() const noexcept -> const Color&
{
	return m_color;
}

