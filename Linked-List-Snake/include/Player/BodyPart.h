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

	};

}