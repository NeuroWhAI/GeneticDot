#pragma once


#include <vector>
#include <random>

#include "Rule.h"

#include <CodeAdapter\Color.h>




class Gene
{
private:
	USING_CA_DRAWING(Color);


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


protected:
	Color m_color;


public:
	void initializeRandomly(std::mt19937& engine, int maxNearCount);


public:
	bool checkSurvive(int step, int nearCount) const;
	bool checkBirth(int step, int nearCount) const;
	int getDelay(int step) const;
	bool stepExists(int step) const;
	bool equals(const Gene& right) const;


public:
	void appendUnit(const Rule& rule, int delay);
	void combine(const Gene& other);


protected:
	void updateColor();


public:
	const Color& getColor() const noexcept;
};

