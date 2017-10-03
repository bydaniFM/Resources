/*
Author: Daniel Fernández
Date: 03/10/2017
*/

#include "List.h"

using exercise::List;

void List::clear() {
	Node * current = first;

	while (current) {

		Node * next = current->next;

		delete current;

		current = next;
	}

	first = last = nullptr;
	count = 0;
}

void List::pushFront(int value) {
	Node * new_node = new Node{ nullptr, first, value };

	if (first) {
		first->prev = new_node;
	} else {
		last = new_node;
	}
	first = new_node;
	count++;
}

void List::pushBack(int value) {
	Node * new_node = new Node{ last, nullptr, value };

	if (last) {
		last->next = new_node;
	} else {
		first = new_node;
	}
	last = new_node;
	count++;
}

void List::popFront() {
	if (first) {
		Node * next = first->next;

		delete first;
		first = next;

		if (first) {
			first->prev = nullptr;
		} else {
			last = nullptr;
		}
		--count;
	}
}

void List::popBack() {
	if (last) {
		Node * prev = last->prev;

		delete last;
		last = prev;

		if (last) {
			last->next = nullptr;
		} else {
			first = nullptr;
		}
		count--;
	}
}

void List::insert(const Iterator & i, int value) {

	Node * current = i.current;

	if (current == nullptr || current == last) {
		pushBack(value);
	} else {
		Node * new_node = new Node{ current, current->next, value };

		if (current->next) {
			current->next->prev = new_node;
		}
		current->next = new_node;
		count++;
	}
}

void List::erase(const Iterator & i) {
	Node * current = i.current;

	if (current) {
		Node * prev = current->prev;
		Node * next = current->next;

		if (current == first) first = next;
		if (current == last) last = prev;

		delete current;

		if (prev) prev->next = next;
		if (next) next->prev = prev;

		count--;
	}
}