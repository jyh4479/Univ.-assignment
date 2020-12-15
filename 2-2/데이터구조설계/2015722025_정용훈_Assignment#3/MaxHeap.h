#pragma once
#include <iostream> 
#include <ctime> 
#include <cstdlib> 
using namespace std; 

template <class T> 
class MaxPQ 

{
public:
	virtual ~MaxPQ() {} //The Destructor
	virtual bool IsEmpty() = 0; //The function of Empty
	virtual T &Top() const = 0; //For returning Top data
	virtual void Push(const T &item) = 0; //For insert Node that has data of item
	virtual void Pop() = 0; //For Delete
};

template <class T> 
class MaxHeap :public MaxPQ<T> 
{
private:
	T *heap; //The heap
	int capacity; //The size of heap
	int heapSize; //The size fo current
public:
	MaxHeap(int theCapacity = 10); //constructor
	virtual ~MaxHeap() {} //destructor
	bool IsEmpty() { return (heapSize == 0); } //The function of checking empty
	void Push(const T &item); //The function of inset
	void Pop(); //The function of delete
	T* getHeap() { return heap; } //get data fo heap
	int getSize() { return heapSize; } //get data of heapsize
	T *Top() const { return heap[1]; } //For return Top data

	void ChangeSize1D(T*&a, const int oldSize, const int newSize) 
	{ //for changesize of size
		if (newSize < 0) throw "New length must be >=0";

		T* temp = new T[newSize]; //decalre new arry
		int number = min(oldSize, newSize); //compare and save the data to number
		copy(a, a + number, temp); //copy
		delete[] a; //Dclare Delete
		a = temp; //save temp to a
	}
};

template<class T> 
MaxHeap<T>::MaxHeap(int theCapacity) 
{ //The definition of MaxHeap constructor
	if (theCapacity < 1)  //if the capacity is smaller than 1
		throw "Capacity must be >= 1."; //throw
	capacity = theCapacity;  //save the capacity
	heapSize = 0; //save 0 to heapsize
	heap = new T[theCapacity + 1]; //save the arry
}

template<class T>
void MaxHeap<T>::Push(const T & e)
{ //The function for insert new data
	if (capacity == heapSize)
	{ //if size of capacity equals heapsize
		ChangeSize1D(heap, capacity, 2 * capacity); //call function to change size of capacity
		capacity *= 2; //change size
	}
	int currentNode = ++heapSize; //save heapSize+1 to currnetNode
	while (currentNode != 1 && heap[currentNode / 2] < e)
	{ //if currentNode is not 1 and the element of heap is smaller than e
		heap[currentNode] = heap[currentNode / 2]; //change value
		currentNode /= 2; //save value of location
	}
	heap[currentNode] = e; //insert value to correct location
}

template<class T> 
void MaxHeap<T>::Pop()
{ //Function of delete
	{
		if (IsEmpty()) //if the function return ture, practice the throw
			throw "Heap is empty. Cannot delete.";
		
		heap[1].~T(); //delete first element of heap

		T lastE = heap[heapSize--]; //save last value
		int currentNode = 1; //Save 1 to currentNode
		int child = 2; //Save 2 to child
		while (child <= heapSize)
		{ //if child <= heapSize, repeat the function
			if (child < heapSize && heap[child] < heap[child + 1]) child++;/*if child is smaller than heap size and
																		   heap[child]<heap[child+1], child = child+1*/
			if (lastE >= heap[child]) break; //if lastE is bigger than heap[child] or equal, break the repeat function

			heap[currentNode] = heap[child]; //save data to heap[currentNode]
			currentNode = child; child *= 2; //save child to current Node, and save child*2 to child
		}
		heap[currentNode] = lastE; //save lastE to heap[currentNode]
	}
}

