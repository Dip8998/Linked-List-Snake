#include "Player/BodyPart.h"
#include "Global/Config.h"
#include "Level/LevelView.h"

namespace Player {

	BodyPart::BodyPart() {
		grid_position = sf::Vector2i(0, 0);
		createBodyPartImage();
	}

	BodyPart::~BodyPart() {
		destroy();
	}

	void BodyPart::createBodyPartImage() {
		bodypart_image = new UI::UIElement::ImageView();
	}

	void BodyPart::initialize(float width, float height, sf::Vector2i pos, Direction dir)
	{
		bodypart_width = width;
		bodypart_height = height;
		direction = dir;
		grid_position = pos;

		initializeBodyPartImage();
	}

	void BodyPart::initializeBodyPartImage() {
		bodypart_image->initialize(Global::Config::snake_body_texture_path, bodypart_width, bodypart_height, getBodyPartScreenPosition());
		bodypart_image->setOriginAtCentre();
	}

	sf::Vector2f BodyPart::getBodyPartScreenPosition()
	{
		float x_screen_position = Level::LevelView::border_offset_left + (grid_position.x * bodypart_width) + (bodypart_width / 2);
		float y_screen_position = Level::LevelView::border_offset_top + (grid_position.y * bodypart_height) + (bodypart_height / 2);

		return sf::Vector2f(x_screen_position, y_screen_position);
	}

	float BodyPart::getRotateAngle() {
		switch (direction)
		{
		case Direction::UP:
			return 270.f;
		case Direction::DOWN:
			return 90.f;
		case Direction::RIGHT:
			return 0;
		case Direction::LEFT:
			return 180.f;
		}
	}

	void BodyPart::setDirection(Direction direction)
	{
		this->direction = direction;
	}

	void BodyPart::updatePosition()
	{
		bodypart_image->setPosition(getBodyPartScreenPosition());
		bodypart_image->setRotation(getRotateAngle());
		bodypart_image->update();
	}

	void BodyPart::render() {
		bodypart_image->render();
	}

	void BodyPart::destroy() {
		delete bodypart_image;
	}
}