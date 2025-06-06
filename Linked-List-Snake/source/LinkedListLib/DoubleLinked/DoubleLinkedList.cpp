#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleNode.h"

namespace LinkedListLib {

	namespace DoubleLinked {

		DoubleLinkedList::DoubleLinkedList() = default;
		DoubleLinkedList::~DoubleLinkedList() = default;


		 void DoubleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
            Node* next_node = cur_node;
            cur_node = new_node;

            while (cur_node != nullptr && next_node != nullptr)
            {
                cur_node->body_part.setPosition(next_node->body_part.getPosition());
                cur_node->body_part.setDirection(next_node->body_part.getDirection());

                prev_node = cur_node;
                cur_node = next_node;
                next_node = next_node->next;
            }

            if (cur_node != nullptr) {
                initializeNode(cur_node, prev_node, Operation::TAIL);
            }
        }

		void DoubleLinkedList::removeNodeAt(int index)
		{
			if (index < 0 || index >= linked_list_size) return;

			if (index == 0)
			{
				removeNodeAtHead();
			}
			else
			{
				removeNodeAtIndex(index);
			}
		}

		void DoubleLinkedList::removeNodeAtMiddle() {
			if (head_node == nullptr) return;

			int midIndex = findMiddleNode();
			removeNodeAt(midIndex);
		}


		void DoubleLinkedList::removeNodeAtIndex(int index)
		{
			if (index < 0 || index >= linked_list_size) return;
			linked_list_size--;

			int current_index = 0;
			Node* cur_node = head_node;
			Node* prev_node = nullptr;

			while (cur_node != nullptr && current_index < index)
			{
				prev_node = cur_node;
				cur_node = cur_node->next;
				current_index++;
			}

			if (cur_node == nullptr) return;

			if (prev_node != nullptr)
				prev_node->next = cur_node->next;

			if (cur_node->next != nullptr)
				static_cast<DoubleNode*>(cur_node->next)->previous = prev_node;

			shiftNodesAfterRemoval(cur_node);
			delete cur_node;
		}

		void DoubleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
		{
			sf::Vector2i previous_node_position = cur_node->body_part.getPosition();
			Direction previous_node_direction = cur_node->body_part.getDirection();
			cur_node = cur_node->next;

			while (cur_node != nullptr)
			{
				sf::Vector2i temp_node_position = cur_node->body_part.getPosition();
				Direction temp_node_direction = cur_node->body_part.getDirection();

				cur_node->body_part.setPosition(previous_node_position);
				cur_node->body_part.setDirection(previous_node_direction);

				cur_node = cur_node->next;
				previous_node_position = temp_node_position;
				previous_node_direction = temp_node_direction;
			}
		}

		Node* DoubleLinkedList::createNode()
		{
			return new DoubleNode();
		}

		void DoubleLinkedList::insertNodeAtHead()
		{
			linked_list_size++;
			Node* new_node = createNode();

			if (head_node == nullptr)
			{
				head_node = new_node;
				static_cast<DoubleNode*>(new_node)->previous = nullptr;
				initializeNode(new_node, nullptr, Operation::HEAD);
				return;
			}

			initializeNode(new_node, head_node, Operation::HEAD);

			new_node->next = head_node;
			static_cast<DoubleNode*>(head_node)->previous = new_node;

			head_node = new_node;
		}

		void DoubleLinkedList::insertNodeAtTail()
		{
			linked_list_size++;
			Node* new_node = createNode();
			Node* curr_node = head_node;

			if (curr_node == nullptr)
			{
				head_node = new_node;
				static_cast<DoubleNode*>(new_node)->previous = nullptr;
				initializeNode(new_node, nullptr, Operation::TAIL);
				return;
			}

			while (curr_node->next != nullptr) {
				curr_node = curr_node->next;
			}

			curr_node->next = new_node;
			static_cast<DoubleNode*>(new_node)->previous = curr_node;
			initializeNode(new_node, curr_node, Operation::TAIL);
		}

		void DoubleLinkedList::insertNodeAtIndex(int index)
		{
			if (index < 0 || index >= linked_list_size) return;

			if (index == 0)
			{
				insertNodeAtHead();
				return;
			}

			Node* new_node = createNode();
			int current_index = 0;
			Node* cur_node = head_node;
			Node* prev_node = nullptr;

			while (cur_node != nullptr && current_index < index)
			{
				prev_node = cur_node;
				cur_node = cur_node->next;
				current_index++;
			}

			prev_node->next = new_node;
			static_cast<DoubleNode*>(new_node)->previous = prev_node;
			new_node->next = cur_node;
			static_cast<DoubleNode*>(cur_node)->previous = new_node;

			initializeNode(new_node, head_node, Operation::TAIL);
			linked_list_size++;

			shiftNodesAfterInsertion(new_node, cur_node, prev_node);
		}

		void DoubleLinkedList::insertNodeAtMiddle()
		{
			if (head_node == nullptr)
			{
				insertNodeAtHead();
				return;
			}

			int midIndex = findMiddleNode();

			insertNodeAtIndex(midIndex);

		}

		void DoubleLinkedList::removeNodeAtHead()
		{
			if (head_node == nullptr) return;
			linked_list_size--;

			Node* cur_node = head_node;
			head_node = head_node->next;

			if (head_node != nullptr) {
				static_cast<DoubleNode*>(head_node)->previous = nullptr;
			}

			delete cur_node;
		}

		void DoubleLinkedList::removeNodeAtTail()
		{
			if (head_node == nullptr) return;
			linked_list_size--;

			Node* cur_node = head_node;

			if (cur_node->next == nullptr)
			{
				removeNodeAtHead();
				return;
			}

			while (cur_node->next != nullptr)
			{
				cur_node = cur_node->next;
			}

			Node* previous = static_cast<DoubleNode*>(cur_node)->previous;
			previous->next = nullptr;
			delete (cur_node);
		}

		void DoubleLinkedList::removeAllNodes()
		{
			if (head_node == nullptr) return;

			while (head_node != nullptr)
			{
				removeNodeAtHead();
			}
		}

		void DoubleLinkedList::removeHalfNodes()
		{
			if (linked_list_size <= 1) return;
			int half_length = linked_list_size / 2;
			int new_tail_index = half_length - 1;

			Node* prev_node = findNodeAtIndex(new_tail_index);
			Node* cur_node = prev_node->next;

			while (cur_node != nullptr)
			{
				Node* node_to_delete = cur_node;
				cur_node = cur_node->next;

				delete (node_to_delete);
				linked_list_size--;
			}

			prev_node->next = nullptr;
		}

		Direction DoubleLinkedList::reverse()
		{
			Node* cur_node = head_node;
			Node* prev_node = nullptr;
			Node* next_node = nullptr;

			while (cur_node != nullptr)
			{
				next_node = cur_node->next;
				cur_node->next = prev_node;
				static_cast<DoubleNode*>(cur_node)->previous = next_node;

				prev_node = cur_node;
				cur_node = next_node;
			}

			head_node = prev_node;

			if (head_node != nullptr)
				static_cast<DoubleNode*>(head_node)->previous = nullptr;

			reverseNodeDirections();
			return head_node->body_part.getDirection();
		}
	}

}