#include "../../include/Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Event/EventService.h"

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
		Event::EventService* event_service = Global::ServiceLocator::getInstance()->getEventService();

		if (event_service->pressedUpArrowKey() && current_snake_direction != Direction::DOWN) {
			current_snake_direction = Direction::UP;
		}
		else if (event_service->pressedDownArrowKey() && current_snake_direction != Direction::UP) {
			current_snake_direction = Direction::DOWN;
		}
		else if (event_service->pressedRightArrowKey() && current_snake_direction != Direction::LEFT) {
			current_snake_direction = Direction::RIGHT;
		}
		else if (event_service->pressedLeftArrowKey() && current_snake_direction != Direction::RIGHT) {
			current_snake_direction = Direction::LEFT;
		}

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
	}
	void SnakeController::handleRestart()
	{
	}
	void SnakeController::reset()
	{
	}
	void SnakeController::respawnSnake()
	{
	}

	void SnakeController::delayedUpdate()
	{
		elapsed_duration += Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (elapsed_duration >= movement_frame_duration)
		{
			elapsed_duration = 0.f;
			updateSnakeDirection();
			processSnakeCollision();
			moveSnake();
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