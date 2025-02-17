#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <random>

namespace Food
{
	enum class FoodType;
	class FoodItem;

	class FoodService
	{
	private:

		FoodItem* current_food_item;

		float cell_width;
		float cell_height;

		void destroyFood();
		void reset();

		std::default_random_engine random_engine;
		std::random_device random_device;

		FoodItem* createFood(sf::Vector2i position, FoodType type);
		void spawnFood();


	public:
		FoodService();
		~FoodService();

		void initialize();
		void update();
		void render();

		void startFoodSpawning();
		sf::Vector2i getRandomPosition();
		bool isValidPosition(std::vector<sf::Vector2i>position_data, sf::Vector2i food_position);
		sf::Vector2i getValidSpawnPosition();
		FoodType getRandomFoodType();
	};
}