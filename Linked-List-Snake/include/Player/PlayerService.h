#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "SnakeController.h"
#include "Level/LevelConfig.h"

namespace Player {

	class PlayerService {
	private:
		SnakeController* snake_controller;
		void createController();
		void destroy();

	public:
		PlayerService();
		
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer(Level::LinkedListType level_type);

		int getPlayerScore();

		LinkedListOperations getLastOperation();
		TimeComplexity getTimeComplexity();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		bool isPlayerDead();
	};

}