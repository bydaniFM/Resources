/*
Author:	Daniel
Date:	28-09-2017
*/

#include "Array.hpp"

using namespace exercise;

Array::Array(size_t initial_size) {

	if (initial_size > 0) {
		data = new int[size = initial_size];
	}
	else {
		data = nullptr;
		size = 0;
	}
}

void Array::clear() {

	if (size > 0) {
		delete[]data;
		data = nullptr;
		size = 0;
	}
}

void Array::push_back(int value) {

	int *new_data = new int[size + 1];
	int * src = data;
	int *dst = new_data;	//Para recorrer directamente el for y no tener que buscar la dirección (lo que hago yo)
	for (int *src_end = data + size; src < src_end; src++, dst++) {
	*dst = *src;
	}
	*dst = value;
	delete[]data;
	data = new_data;
	size++;
}

void Array::pop_back() {

	if (size > 0) {
		if (size == 1) {
			clear();
		} else {
			int *new_data = new int[size - 1];
			int * src = data;
			int *dst = new_data;	//Para recorrer directamente el for y no tener que buscar la dirección (lo que hago yo)
			for (int *src_end = data + size - 1; src < src_end; src++, dst++) {
				*dst = *src;
			}
			delete[]data;
			data = new_data;
			size--;
		}
	}
}

void Array::insert(size_t index, int value) {

	int *newArray = new int[size + 1];
	for (size_t i = 0; i < size + 1; i++) {
		if (i == index) {
			newArray[i] = value;
		} else {
			newArray[i] = data[i];
		}
	}
	delete[] data;
	data = newArray;
	size++;
}

// Legacy

// push_back
//int *newArray = new int[size + 1];
//for (size_t i = 0; i < size; i++) {
//	newArray[i] = *(data + i);			//Es lo mismo, sí
//}
//newArray[size] = value;
//delete[] data;
//data = newArray;
//size++;

// pop_back
/*int *newArray = new int[size - 1];
for (size_t i = 0; i < size - 1; i++) {
newArray[i] = data[i];
}
delete[]data;
data = newArray;
size--;*/

// Mejor inline
//int & Array::get_item(size_t index) {
//	return *(data + index);
//}