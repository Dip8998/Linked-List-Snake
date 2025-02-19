#pragma once
#include "UI/UIElement/ImageView.h"
#include "FoodType.h"

namespace Food {

	class FoodItem {
	private:
		UI::UIElement::ImageView* food_image;
		sf::Vector2i grid_position;
		float cell_width;
		float cell_height;
		FoodType food_type;

		void initializeFoodImage();

		sf::String getFoodTexturePath();
		sf::Vector2f getFoodImagePosition();

		
	public:
		FoodItem();
		~FoodItem();

		static const int number_of_foods = 8;

		void initialize(sf::Vector2i grid_pos, float width, float height, FoodType type);
		void  update();
		void render();

		FoodType getFoodType();
		sf::Vector2i getFoodPosition();

	};

}