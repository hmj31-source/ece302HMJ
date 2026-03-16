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
	//create new node
	Node<ItemType>* newNode = new Node<ItemType>(newItem, headPtr);
	//set the headPtr to the newNode
	headPtr = newNode;
	//increase current size
	currentSize++;
	//return true
	return true;
}

template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	// TODO
	//bounds check
	if (isEmpty()) throw std::logic_error("peel() called on empty stack");

	return headPtr->getItem();
}

template<class ItemType>
bool Stack<ItemType>::pop() 
{
	// TODO
	//bounds check
	if (isEmpty()) return false;
	
	//create new node
	Node<ItemType>* nodeToDelete = headPtr;
	//set headptr to next node
	headPtr = headPtr->getNext()
	nodeToDelete->setNext(nullptr);
	//delete node
	delete nodeToDelete;
	//decrement size
	currentSize--
	//return true
	return true;
}

template<class ItemType>
void Stack<ItemType>::clear()
{
	// TODO
	//while not empty continusly pop
	while (!isEmpty()){
		pop();
	}
}

