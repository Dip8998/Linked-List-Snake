#pragma once 
#include <vector>
#include "Element/Obstacle.h"
#include "Element/ElementData.h"

namespace Element {

	class ElementService {
	private:
		std::vector<Obstacle*> obstacle_list;

		void spawnObstacle(sf::Vector2i position, float cell_width, float cell_height);

	
	public:
		ElementService();
		~ElementService();

		void initialize();
		void update();
		void render();
		std::vector<sf::Vector2i> getElementsPositionList();

		const void spawnElements(std::vector<ElementData>& element_data_list, float cell_width, float cell_height);
	};

}