#include <stdexcept>

#include "Stack.hpp"

template<class ItemType>
Stack<ItemType>::Stack() : head(nullptr), currentSize(0)
{
	// TODO
	//declared nullptr and currentSize 0 above
} 

template<class ItemType>
Stack<ItemType>::~Stack()
{
	// TODO
	clear();
}

template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	// TODO
	return currentSize == 0;
}

template<class ItemType>
int Stack<ItemType>::size() const
{
	// TODO
	return currentSize;
}

template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	// TODO
	return true;
}

template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	// TODO
	return ItemType();
}

template<class ItemType>
bool Stack<ItemType>::pop() 
{
	// TODO
	return false;
}

template<class ItemType>
void Stack<ItemType>::clear()
{
	// TODO
}

