#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelController.h"
#include "../../include/Global/ServiceLocator.h"

namespace Level {

	LevelService::LevelService() {
		level_controller = nullptr;
		createLevelController();
	}

	LevelService::~LevelService() {
		destroy();
	}

	void LevelService::createLevelController() {
		level_controller = new LevelController();
	}

	void LevelService::initialize() {
		level_controller->initialize();
	}

	void LevelService::update() {
		level_controller->update();
	}

	void LevelService::render() {
		level_controller->render();
	}

	void LevelService::createLevel(LevelNumber level_to_load) {
		current_level = level_to_load;
		spawnLevelElements(level_to_load);
		spawnPlayer();
		spawnFood();
	}

	void LevelService::spawnLevelElements(LevelNumber level_to_load)
	{
		float cell_width = level_controller->getCellWidth();
		float cell_height = level_controller->getCellHeight();

		std::vector<Element::ElementData> element_data_list = level_controller->getElementDataList((int)level_to_load);
		Global::ServiceLocator::getInstance()->getElementService()->spawnElements(element_data_list, cell_width, cell_height);
	}

	void LevelService::spawnPlayer() {
		Global::ServiceLocator::getInstance()->getPlayerService()->spawnPlayer();
	}

	void LevelService::spawnFood() {
		Global::ServiceLocator::getInstance()->getFoodService()->startFoodSpawning();
	}

	void LevelService::destroy() {
		delete(level_controller);
	}

	float LevelService::getCellWidth()
	{
		return level_controller->getCellWidth();
	}

	float LevelService::getCellHeight()
	{
		return level_controller->getCellHeight();
	}
}