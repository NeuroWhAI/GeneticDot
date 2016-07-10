#include "MainScene.h"

#include <ctime>




MainScene::MainScene()
{

}


MainScene::~MainScene()
{

}

//###########################################################################

void MainScene::onInitialize(caDraw::Window& owner)
{
	auto winSize = owner.getSize();


	m_panel = caFactory->createPanel();
	m_panel->transform.position = { 0, 0 };
	m_panel->size = static_cast<caDraw::SizeF>(winSize);

	m_font = caFactory->createFont();
	m_font->loadFromFile("GD Resources/NanumGothic.ttf");
	m_font->setCharacterSize(32);
	m_font->setStyle(caDraw::FontStyles::Bold);


	m_world = canew<DrawableWorld>();


	m_panel->addDrawable(m_world);


	addPanel(m_panel);


	m_world->initializeRandomly(200,
		static_cast<unsigned int>(std::time(nullptr)));
	m_world->setCellSize(2);
}


void MainScene::onRelease()
{

}


void MainScene::onUpdate(caDraw::Window& owner)
{
	if (caKeyboard->isKeyDown(caSys::Keys::Escape))
	{
		reserveNextScene(nullptr);
	}
	else if (caKeyboard->isKeyDown(caSys::Keys::Return))
	{
		m_world->initializeRandomly(200,
			static_cast<unsigned int>(std::time(nullptr)));
	}


	m_world->update();
}


void MainScene::onDrawBack(caDraw::Graphics& g)
{

}


void MainScene::onDrawFront(caDraw::Graphics& g)
{

}

