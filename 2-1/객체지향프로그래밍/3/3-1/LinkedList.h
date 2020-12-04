#pragma once

#include <iostream>

using std::ostream;

namespace kw
{
	template<typename T>
	class Node
	{
	public:
		T           mData; 
		Node<T>*	mNextNode; 

		Node(const T& data)
			:
			mData(data),
			mNextNode(NULL)
		{
		}

		Node(const T& data, Node<T>* nextNode)
			:
			mData(data),
			mNextNode(nextNode)
		{
		}

		Node()
			:
			mData(NULL),
			mNextNode(NULL)
		{
		}
	};

	template <typename T>
	class LinkedList
	{

	private:
		Node<T>*                mHead;
		unsigned int		mSize;

	public:
		LinkedList()
		{}
		~LinkedList()
		{}

		virtual T                       get(const int index) const
		{
			Node<T>* tmp = mHead; //Delcare tmp and Save mHead to tmp
			for (int a = 0; index-1 > a; a++) //Declae a and Save 0, if (index-1) is bigger than a, repeat the fucntion
			{//and update the a
				tmp = tmp->mNextNode; //Save tmp->mNExtNode to tmp
			}
			return tmp->mData; //return tmp->mData
		}
		virtual bool			set(const int index, const T& data)
		{
			Node<T>* tmp = mHead; //Declare tmp and Save mHead to tmp
			for (int a = 0; index - 1 > a; a++) //Declae a and Save 0, if (index-1) is bigger than a, repeat the fucntion
			{//and update the a
				tmp = tmp->mNextNode; //Save tmp->mNExtNode to tmp
			}
			tmp->mData = data; //Save data to tmp->mData
			return 0; //return 0
		}

		virtual bool			insert(const T& data)
		{
			Node<T>* newNode = new Node<T>(data); //Declare newNode that in the heep area and has information about data 
	
			Node<T>* tmp = mHead; //Save mHead to tmp

			if (tmp == NULL) //If tmp is NULL practice the function
			{
				mHead = newNode; //Save newNode to mHead
			}

			else if (tmp != NULL) //If tmp is not NULL practice the function
			{
				while (tmp->mNextNode != NULL) //If tmp->mNextNode is not NULL, repeat the function
				{
					tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
				}
				tmp->mNextNode=newNode; // Save newNode to tmp->mNextNode
			}
			return 0; //return 0
		}

		virtual bool			insert(const int index, const T& data)
		{
			Node<T>* tmp = mHead; //Declare tmp and Save mHead to tmp
			
			for (int a = 0; a < index-1; a++) //Declae a and Save 0, if (index-1) is smaller than a, repeat the fucntion
			{//and update the a
				tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
			}

			Node<T>* newNode = new Node<T>(data); //Declare newNode that in the heep area and has information about data 

			newNode->mNextNode = tmp->mNextNode; //Save tmp->mNextNode to newNode->mNextNode
			tmp->mNextNode = newNode; //Save newNode to tmp->mNextNode
		
			return 0;
		}

		virtual bool			pop()
		{
			Node<T>* pretmp = mHead; //Save mHead to pretmp
			Node<T>* tmp = pretmp->mNextNode; //Save pretmp->mNextNode to tmp
			 
			for (; tmp->mNextNode != NULL;) //If tmp->mNextNode is not NULL, repeat the function
			{
				tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
				pretmp = pretmp->mNextNode; //Save pretmp->mNextNode to pretmp
			}
			pretmp->mNextNode = NULL; //Save NULL to pretmp->mNExtNode
			delete tmp; //delete tmp
			return 0; //return 0
		}

		virtual bool			pop(const int index)
		{
			Node<T>* pretmp = mHead; //Save mHead to pretmp
			Node<T>* tmp = pretmp->mNextNode; //Save pretmp->mNextNode to tmp

			if (index == 0) //If index is 0, practice the function
			{
				mHead = tmp; //Save tmp to mHead
				delete pretmp; //delete pretmp
			}

			else
			{
				for (int a = 0; a < index-1; a++) //Declae a and Save 0, if (index-1) is smaller than a, repeat the fucntion
				{//and update the a
					tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
					pretmp = pretmp->mNextNode; //Save pretmp->mNextNode to pretmp
				}
				pretmp->mNextNode = NULL; //Save NULL to pretmp->mNextNode
				pretmp->mNextNode = tmp->mNextNode; //Save tmp->mNextNode to pretmp->mNextNode
				delete tmp; //delete tmp
			}
			return 0; //return 0
		}

		virtual unsigned int            size()	const
		{
			int a = 0; //Declare a and Save 0

			Node<T>* pretmp = mHead; //Declare pretmp and Save mHead to pretmp
			Node<T>* tmp; //Declare tmp
			 
			if (mHead == NULL) //If mHead is NULL practice the function
				return a; //return a

			else
			{
				tmp = pretmp->mNextNode; //Save mNextNode to pretmp
				a = 1; //Save 1 to a
				while (tmp != NULL) //If tmp is not NULL, repeat the function
				{
					tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
					pretmp = pretmp->mNextNode; //Save pretmp->mNextNode to pretmp
					a++; //Save a+1 to a
				}
			}
			return a; //return a
		}

		virtual bool			empty() const
		{
			if (mHead == NULL) //If mHead is NULL, practice the function
				cout << "This linked list is empty." << endl; //print the string
			return 0; //return 0
		}

		virtual void			clear()
		{
			Node<T>* tmp; //Declare the tmp

			while (mHead->mNextNode != NULL) //If mHead->mNextNode is not NULL, repeat the function
			{ 
				tmp = mHead; //Save mHead to tmp
				mHead = tmp->mNextNode; //Save tmp->mNextNode to mHead
				delete tmp; //delete tmp
			}
			mHead = NULL; //Save NULL to mHead
			delete mHead; //delete mHead
		}

		friend ostream& operator<<(ostream& os, const LinkedList<T>& data)
		{
			Node<T>* tmp = data.mHead;

			int idx = 0;

			if(tmp!=NULL)
			{
				os << "------------------------------------" << endl;
				for (idx=0;tmp != NULL;idx++)
				{
					cout << "idx: " << idx << ", data: " << tmp->mData << endl;
					tmp = tmp->mNextNode;
				}
				os << "------------------------------------" << endl;
			}
			data.empty();
			return os;
		}
	};
}
