#pragma once
#include "PolymorphicPtr.hpp"
#include "Vector.hpp"

template<class T>
class polymorphic_container
{

public:
	void add(T*);
	void remove(size_t indx);
	polymorphic_ptr<T>& operator[](size_t idx);
	const polymorphic_ptr<T>& operator[](size_t idx) const;
	size_t getSize() const;

	void execute(size_t idx, void (*func)(T*));
private:
	Vector<polymorphic_ptr<T>> data;
};

template<class T>
void polymorphic_container<T>::add(T* ptr)
{
	data.pushBack(ptr);
}

template<class T>
void polymorphic_container<T>::remove(size_t indx)
{
	data.popAt(indx);
}

template<class T>
polymorphic_ptr<T>& polymorphic_container<T>::operator[](size_t idx)
{
	return data[idx];
}

template<class T>
const polymorphic_ptr<T>& polymorphic_container<T>::operator[](size_t idx) const
{
	return data[idx];
}

template<class T>
inline size_t polymorphic_container<T>::getSize() const
{
	return data.getSize();
}

template<class T>
void polymorphic_container<T>::execute(size_t idx, void(*func)(T*))
{
	func(data[idx].get());
}
