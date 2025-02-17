#include "../../include/Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Sound/SoundService.h"
#include "Event/EventService.h"
#include "Element/ElementService.h"
#include "Food/FoodService.h"

using namespace Food;

namespace Player {

	SnakeController::SnakeController() {
		single_linked_list = nullptr;
		createLinkedList();
	}

	SnakeController::~SnakeController() {
		delete single_linked_list;
	}

	void SnakeController::createLinkedList()
	{
		single_linked_list = new SingleLinkedList();
	}

	void SnakeController::initialize() {

		float width = Global::ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		float height = Global::ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		single_linked_list->initialize(width, height, default_position, default_direction);
	}

	void SnakeController::update() {
		switch (current_snake_state)
		{
		case SnakeState::ALIVE:
			processPlayerInput();
			delayedUpdate();
			break;

		case SnakeState::DEAD:
			handleRestart();
			break;
		}
	}

	void SnakeController::render() {
		single_linked_list->render();
	}

	void SnakeController::spawnSnake()
	{
		for (int i = 0; i < initial_snake_length; i++) {
			single_linked_list->insertNodeAtTail();     // Insert nodes at tail to create the initial snake
		}
	}

	void SnakeController::processPlayerInput()
	{
		if (current_input_state == InputState::PROCESSING)
			return;

		Event::EventService* event_service = Global::ServiceLocator::getInstance()->getEventService();

		if (event_service->pressedUpArrowKey() && current_snake_direction != Direction::DOWN) {
			current_snake_direction = Direction::UP;
			current_input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedDownArrowKey() && current_snake_direction != Direction::UP) {
			current_snake_direction = Direction::DOWN;
			current_input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedRightArrowKey() && current_snake_direction != Direction::LEFT) {
			current_snake_direction = Direction::RIGHT;
			current_input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedLeftArrowKey() && current_snake_direction != Direction::RIGHT) {
			current_snake_direction = Direction::LEFT;
			current_input_state = InputState::PROCESSING;
		}

	}
	std::vector<sf::Vector2i> SnakeController::getCurrentSnakePositionList()
	{
		return single_linked_list->getNodesPositionList();
	}
	void SnakeController::updateSnakeDirection()
	{
		single_linked_list->updateNodeDirection(current_snake_direction);
	}
	void SnakeController::moveSnake()
	{
		single_linked_list->updateNodePosition();
	}

	void SnakeController::processSnakeCollision()
	{
		processBodyCollision();
		processElementsCollision();
		processFoodCollision();
	}

	void SnakeController::processBodyCollision()
	{
		if (single_linked_list->processNodeCollision())
		{
			current_snake_state = SnakeState::DEAD;
			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
		}
	}

	void SnakeController::processElementsCollision()
	{
		Element::ElementService* element_service = Global::ServiceLocator::getInstance()->getElementService();

		if (element_service->processElementsCollision(single_linked_list->getHeadNode()))
		{
			current_snake_state = SnakeState::DEAD;
			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
		}
	}

	void SnakeController::processFoodCollision()
	{
		FoodService* food_service = Global::ServiceLocator::getInstance()->getFoodService();
		FoodType food_type;

		if (food_service->processFoodCollision(single_linked_list->getHeadNode(), food_type))
		{
			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::PICKUP);

			food_service->destroyFood();
			OnFoodCollected(food_type);
		}
	}

	void SnakeController::OnFoodCollected(FoodType food_type)
	{
		switch (food_type)
		{
		case FoodType::PIZZA:
			//Insert At Tail
			break;

		case FoodType::BURGER:
			//Insert At Head
			break;

		case FoodType::CHEESE:
			//Insert in Middle
			break;

		case FoodType::APPLE:
			//Delete at Head
			break;

		case FoodType::MANGO:
			//Delete at Middle
			break;

		case FoodType::ORANGE:
			//Delete at Tail
			break;

		case FoodType::POISION:
			//Delete half the snake
			break;

		case FoodType::ALCOHOL:
			//Reverse the snake
			break;
		}
	}
	void SnakeController::handleRestart()
	{
		restart_counter += Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (restart_counter >= restart_duration)
		{
			respawnSnake();
		}
	}
	void SnakeController::reset()
	{
		current_snake_state = SnakeState::ALIVE;
		current_snake_direction = default_direction;
		elapsed_duration = 0.f;
		restart_counter = 0.f;

		current_input_state = InputState::WAITING;
	}
	void SnakeController::respawnSnake()
	{
		single_linked_list->removeAllNodes();
		reset();
		spawnSnake();
	}

	void SnakeController::delayedUpdate()
	{
		elapsed_duration += Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (elapsed_duration >= movement_frame_duration)
		{
			elapsed_duration = 0.f;
			updateSnakeDirection();
			processSnakeCollision();
			if (current_snake_state != SnakeState::DEAD)
			{
				moveSnake();
			}
			current_input_state = InputState::WAITING;
		}
	}

	void SnakeController::setSnakeState(SnakeState state)
	{
		current_snake_state = state;
	}
	SnakeState SnakeController::getSnakeState()
	{
		return current_snake_state;
	}


}