#pragma once


#include <CodeAdapter\Drawable.h>
#include "World.h"




class DrawableWorld : public CodeAdapter::Drawing::Drawable,
	public World
{
private:
	USING_CA_DRAWING(Graphics);
	USING_CA_DRAWING(Transform);


public:
	DrawableWorld();


protected:
	float m_cellSize;


protected:
	virtual void onDraw(Graphics& g, const Transform& parentTransform) override;


public:
	void setCellSize(float cellSize);
};

