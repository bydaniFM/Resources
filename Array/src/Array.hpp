/*
	Author:	Daniel
	Date:	28-09-2017
*/

#pragma once

#include <cstddef>

namespace exercise {
	template <typename T>
	class Array {
	private:
		T *data;	//apunta al array
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

		// Para poder acceder a un valor con los "[]"
		T & operator [] (size_t index) {
			return *(data + index);
		}

		// Sobrecarga para cuando se use const Array
		const T & operator [] (size_t index) const {
			return *(data + index);
		}

		// Para poder copiar arrays tenemos que sobreescibir el operador "="
		Array & operator = (const Array & other) {
			if (this != &other) {
				clear();

				if (other.size > 0) {
					this->data = new T[other.size];

					T *src = other.data;
					T *dst = this->data;

					for (T *end = src + other.size; src < end; ++src, ++dst) {
						*dst = *src;
					}
				} else {
					this->data = nullptr;
				}
				this->size = other.size;
			}
			return *this;
		}

		void push_back(T value);
		void pop_back();

		void insert(size_t index, T value);

		//Devuelve una referencia!
		T & get_item(size_t index) { return *(data + index); }

	};


	template<typename T>
	Array<T>::Array(size_t initial_size) {

		if (initial_size > 0) {
			data = new T[size = initial_size];
		}
		else {
			data = nullptr;
			size = 0;
		}
	}

	template<typename T>
	void Array<T>::clear() {

		if (size > 0) {
			delete[]data;
			data = nullptr;
			size = 0;
		}
	}

	template<typename T>
	void Array<T>::push_back(T value) {

		T *new_data = new T[size + 1];
		T * src = data;
		T *dst = new_data;	//Para recorrer directamente el for y no tener que buscar la dirección (lo que hago yo)
		for (T *src_end = data + size; src < src_end; src++, dst++) {
			*dst = *src;
		}
		*dst = value;
		delete[]data;
		data = new_data;
		size++;
	}
	
	template<typename T>
	void Array<T>::pop_back() {

		if (size > 0) {
			if (size == 1) {
				clear();
			}
			else {
				T *new_data = new T[size - 1];
				T * src = data;
				T *dst = new_data;	//Para recorrer directamente el for y no tener que buscar la dirección (lo que hago yo)
				for (T *src_end = data + size - 1; src < src_end; src++, dst++) {
					*dst = *src;
				}
				delete[]data;
				data = new_data;
				size--;
			}
		}
	}

	template<typename T>
	void Array<T>::insert(size_t index, T value) {

		T *newArray = new T[size + 1];
		for (size_t i = 0; i < size + 1; i++) {
			if (i == index) {
				newArray[i] = value;
			}
			else {
				newArray[i] = data[i];
			}
		}
		delete[] data;
		data = newArray;
		size++;
	}
}