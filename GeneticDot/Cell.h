#pragma once


class Gene;


class Cell
{
public:
	Cell();
	explicit Cell(const Gene* gene);


protected:
	const Gene* m_gene;
	int m_step;
	int m_count;


public:
	void reset(const Gene* gene);
	void update();


public:
	const Gene* getGene() const noexcept;
	bool isDie() const;
	bool checkSurvive(int nearCount) const;
	bool checkBirth(int nearCount) const;
};

