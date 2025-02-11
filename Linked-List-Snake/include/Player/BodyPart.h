#pragma once 
#include "../../include/Player/Direction.h"
#include "../../include/UI/UIElement/ImageView.h"

namespace Player {

	class BodyPart {
	protected:

		UI::UIElement::ImageView* bodypart_image;

		sf::Vector2i grid_position;
		Direction direction;

		float bodypart_width;
		float bodypart_height;

		void destroy();
		void createBodyPartImage();
		void initializeBodyPartImage();

		sf::Vector2f getBodyPartScreenPosition();
		float getRotateAngle();

	public:

		BodyPart();
		~BodyPart();

		void initialize(float width, float height, sf::Vector2i pos, Direction dir);
		void updatePosition();
		void render();

		void setDirection(Direction direction);
	};

}