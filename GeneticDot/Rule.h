#pragma once


#include <vector>




class Rule
{
private:
	using RuleType = std::vector<bool>;
	using NumList = std::vector<int>;


public:
	Rule();
	explicit Rule(int maxNearCount);


protected:
	int m_maxNearCount;
	RuleType m_survive;
	RuleType m_birth, m_antiBirth;


public:
	int getMaxNearCount() const;
	void setMaxNearCount(int maxNearCount);
	bool checkSurvive(int nearCount) const;
	bool checkBirth(int nearCount) const;
	void setSurvive(const NumList& rule);
	void setBirth(const NumList& rule);


public:
	void accumulate(const Rule& other);
	Rule combine(const Rule& other) const;
};

