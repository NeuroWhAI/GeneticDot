#pragma once


#include <vector>
#include <random>




class Rule
{
private:
	using RuleType = std::vector<int>;
	using NumList = std::vector<int>;

	enum Boolean
	{
		False = 0,
		True = 1
	};


public:
	Rule();
	explicit Rule(int maxNearCount);


protected:
	int m_maxNearCount;
	RuleType m_survive;
	RuleType m_birth, m_antiBirth;


public:
	void initializeRandomly(std::mt19937& engine, int maxNearCount);


public:
	int getMaxNearCount() const;
	void setMaxNearCount(int maxNearCount);
	bool checkSurvive(int nearCount) const;
	bool checkBirth(int nearCount) const;
	bool checkAntiBirth(int nearCount) const;
	void setSurvive(const NumList& rule);
	void setBirth(const NumList& rule);


public:
	void accumulate(const Rule& other);
	Rule combine(const Rule& other) const;


public:
	bool equals(const Rule& right) const;
};

