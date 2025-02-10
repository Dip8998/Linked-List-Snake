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
	}

	void LevelService::spawnPlayer() {
		Global::ServiceLocator::getInstance()->getPlayerService()->spawnPlayer();
	}

	void LevelService::destroy() {
		delete(level_controller);
	}
}