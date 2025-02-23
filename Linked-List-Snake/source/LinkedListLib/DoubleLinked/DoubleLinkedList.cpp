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

			initializeNode(cur_node, prev_node, Operation::TAIL);
		}

		void DoubleLinked::removeNodeAtIndex(int index)
		{

		}

		void DoubleLinked::shiftNodesAfterRemoval(Node* cur_node)
		{

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

			while (curr_node->next != nullptr)
			{
				curr_node = curr_node->next;
			}

			curr_node->next = new_node;
			static_cast<DoubleNode*>(new_node)->previous = curr_node;
			initializeNode(new_node, head_node, Operation::TAIL);
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

			initializeNode(new_node, prev_node, Operation::TAIL);
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

	}

}