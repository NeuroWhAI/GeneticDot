#include "MainScene.h"




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


	m_world->initialize(64);
	m_world->setCellSize(10);

	Gene conwaysGene;

	Rule conwaysRule{ 8 };
	conwaysRule.setSurvive({ 2, 3 });
	conwaysRule.setBirth({ 3 });

	conwaysGene.appendUnit(conwaysRule, 1000);

	const auto* gene = m_world->addGene(conwaysGene);

	// Blinker
	m_world->setCell(gene, { 8, 4 });
	m_world->setCell(gene, { 8, 5 });
	m_world->setCell(gene, { 8, 6 });

	// Block
	m_world->setCell(gene, { 16, 4 });
	m_world->setCell(gene, { 16, 5 });
	m_world->setCell(gene, { 17, 4 });
	m_world->setCell(gene, { 17, 5 });

	// Gosper glider gun
	char gunBlueprint[11][64] = {
		"0000000000000000000000000000000000000000",
		"0000000000000000000000000010000000000000",
		"0000000000000000000000001010000000000000",
		"0000000000000011000000110000000000001100",
		"0000000000000100010000110000000000001100",
		"0011000000001000001000110000000000000000",
		"0011000000001000101100001010000000000000",
		"0000000000001000001000000010000000000000",
		"0000000000000100010000000000000000000000",
		"0000000000000011000000000000000000000000",
		"0000000000000000000000000000000000000000",
	};

	for (int y = 0; y < 11; ++y)
	{
		int len = std::strlen(gunBlueprint[y]);

		for (int x = 0; x < len; ++x)
		{
			if (gunBlueprint[y][x] != '0')
			{
				m_world->setCell(gene, { x, y + 16 });
			}
		}
	}
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


	m_world->update();
}


void MainScene::onDrawBack(caDraw::Graphics& g)
{

}


void MainScene::onDrawFront(caDraw::Graphics& g)
{

}

