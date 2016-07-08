#pragma once


#include <vector>

#include "Rule.h"




class Gene
{
private:
	class Unit
	{
	public:
		Unit()
			: delay(0)
		{ }

		Unit(const Rule& rule, int delay)
			: rule(rule)
			, delay(delay)
		{ }

	public:
		Rule rule;
		int delay;
	};


public:
	Gene();
	

protected:
	std::vector<Unit> m_gene;


public:
	bool checkSurvive(int step, int nearCount) const;
	bool checkBirth(int step, int nearCount) const;
	int getDelay(int step) const;
	bool stepExists(int step) const;


public:
	void appendUnit(const Rule& rule, int delay);
	void combine(const Gene& other);
};

