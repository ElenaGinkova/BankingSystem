#pragma once
#include <iostream>
#include <exception>

template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();

	size_t getSize() const;
	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, size_t indx);
	void pushAt(T&& element, size_t indx);
	T& popBack();
	T& popAt(size_t indx);
	T& operator[](size_t indx);
	const T& operator[]( size_t indx) const;
	bool isEmpty() const;
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = CAPACITYDEFAULT;

	static const int CAPACITYDEFAULT = 4;

	void copyFrom(const Vector&);
	void moveFrom(Vector&&);
	void free();

	void resize();
};

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) {
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
Vector<T>::~Vector() {
	free();
}

template <typename T>
size_t Vector<T>::getSize() const {
	return size;
}


template <typename T>
void Vector<T>::pushBack(const T& element) {
	if (size == capacity)
	{
		resize();
	}

	data[size++] = element;
}


template <typename T>
void Vector<T>::pushBack(T&& element) {
	if (size == capacity)
	{
		resize();
	}

	data[size++] = element;
}

template <typename T>
void Vector<T>::pushAt(const T& element, const size_t index) {
	if (size == capacity)
	{
		resize();
	}

	for (size_t i = size; i > index; i--)
	{
		data[i] = data[i - 1];
	}

	data[index] = element;
	size++;
}

template <typename T>
void Vector<T>::pushAt(T&& element, const size_t index) {
	if (size == capacity)
	{
		resize();
	}

	for (size_t i = size; i > index; i--)
	{
		data[i] = data[i - 1];
	}

	data[index] = element;
	size++;
}

template <typename T>
T& Vector<T>::popBack() {
	if (isEmpty())
	{
		throw std::runtime_error("No elements");
	}

	return data[--size];
}

template <typename T>
T& Vector<T>::popAt(size_t index) {
	if (index < 0 || index >= size)
	{
		throw std::runtime_error("Invalid index");
	}

	T deleted = data[index];
	for (size_t i = index; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}

	size--;
	return deleted;
}

template <typename T>
T& Vector<T>::operator[](const size_t index) {
	if (index < 0 || index >= size)
	{
		throw std::runtime_error("Invalid index");
	}

	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](const size_t index) const {
	if (index < 0 || index >= size)
	{
		throw std::runtime_error("Invalid index");
	}

	return data[index];
}

template <typename T>
bool Vector<T>::isEmpty() const {
	return size == 0;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other[i];
	}
}

template <typename T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
	capacity = size = 0;
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other)
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.capacity = other.size = 0;
}

template <typename T>
void Vector<T>::resize() {
	capacity *= 2;
	T* newData = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}