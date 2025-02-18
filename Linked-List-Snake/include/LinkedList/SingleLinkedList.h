#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedList/Node.h"
#include "../Player/Direction.h"

namespace LinkedList {

	enum class Operation
	{
		HEAD,
		MID,
		TAIL,
	};

	class SingleLinkedList {

	private:
		Node* head_node;

		float node_width;
		float node_height;

		sf::Vector2i default_position;
		Direction default_direction;

		Node* createNode();

		int linked_list_size;

	public:
		SingleLinkedList();
		~SingleLinkedList();

		void initialize(float width, float height, sf::Vector2i position, Direction direction);
		void render();

		void insertNodeAtTail();
		void insertNodeAtIndex(int index);
		void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);
		void insertNodeAtMiddle();
		int findMiddleNode();
		void updateNodeDirection(Direction direction_to_set);
		void updateNodePosition();
		bool processNodeCollision();
		void removeNodeAtHead();
		void removeAllNodes();
		Node* getHeadNode();
		void shiftNodesAfterRemoval(Node* cur_node);
		void removeNodeAt(int index);
		void removeNodeAtIndex(int index);
		void removeNodeAtMiddle();

		void removeNodeAtTail();
		Node* findNodeAtIndex(int index);
		void removeHalfNodes();

		std::vector<sf::Vector2i> getNodesPositionList();
		sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);
		void initializeNode(Node* new_node, Node* reference_node, Operation operation);

		void insertNodeAtHead();

	};


}