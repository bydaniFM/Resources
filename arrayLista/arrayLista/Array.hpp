/*
	Author:	Daniel
	Date:	28-09-2017
*/

#pragma once

#include <cstddef>

namespace exercise {
	class Array {
	private:
		int *data;	//apunta al array
		size_t size;

	public:
		Array() : data(nullptr), size(0) {	//para inicializar data antes de entrar
		}
		Array(size_t initial_size);
		~Array() {
			if (size > 0) delete[]data;
		}

		size_t get_size() const { return size; }

		void clear();

		void push_back(int value);
		void pop_back();

		void insert(size_t index, int value);

		int & at(size_t index) {
			if (index >= size) {
				throw "error: index out of bounds";
			}
		}

		//Devuelve una referencia!
		int & get_item(size_t index) { return *(data + index); }

	};
}