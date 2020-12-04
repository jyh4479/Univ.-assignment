#pragma once

#include <iostream>

using std::ostream;

namespace kw
{
	template<typename T>
	class Node
	{
	public:
		T               mData;
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
		Node<T>* mTail;
		unsigned int		mSize;

	public:
		LinkedList()
		{}
		~LinkedList()
		{}

		virtual bool			insert(const T& data) //This function create the Node
		{
			Node<T>* newNode = new Node<T>(data); //Declare newNode that have data in heep area 

			Node<T>* tmp = mHead; //Declare tmp and save mHead to tmp

			if (tmp == NULL) //If tmp is NULL
			{
				mHead = newNode; //Save newNode to mHead
			}

			else if (tmp != NULL) //If tmp is not NULL
			{
				while (tmp->mNextNode != NULL) //If tmp->mNextNode is not NULL, repeat the function
				{
					tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
				}
				tmp->mNextNode = newNode; //Save newNode to tmp->mNextNode
			}
			return 0; //return 0
		}
		void reverse() //This function work for changing Node's position
		{
			Node<T>* pretmp = mHead; //Declare pretmp and Save mHead to pretmp
			Node<T>* tmp = pretmp->mNextNode; //Declare tmp and Save pretmp->mNextNode to tmp
			Node<T>* tail = NULL; //Declare tail and Save NULL to tail

			for (; tmp->mNextNode != NULL;)
			{ //Save end Node to tail
				tmp = tmp->mNextNode; //Save tmp->mNextNode to tmp
				pretmp = pretmp->mNextNode; //Save pretmp->mNextNode to pretmp
				tail = tmp; //Save tmp to tail
			}

			for (; mHead->mNextNode != NULL;) //Repeat the function if mHead->mNextNode is not NULL
			{
				for (; pretmp->mNextNode != tmp;) //Repeat the function if pretmp->mNextNode is not tmp
				{
					pretmp = pretmp->mNextNode; //Save pretmp->mNextNode to pretmp
				}
				tmp->mNextNode = pretmp; //Save pretmp to tmp->mNextNode
				tmp = pretmp; //Save pretmp to tmp
				pretmp = mHead; //Save mHead pretmp
				if (tmp == pretmp) //If tmp is not pretmp
				{
					mHead->mNextNode = NULL; //mHead->mNextNode is not NULL
					mHead = tail; //Save tail to mHead
					tail = tmp; //Save tmp to tail
					break; // Declare break
				}
			}
		}

		void sort() //This function to sort Node
		{
			Node<T>* pretmp = mHead; //Declare pretmp and Save mHead to pretmp
			Node<T>* tmp = pretmp->mNextNode; //Declare tmp Save pretmp->mNextNode to tmp
			int Save = 0; //Declare integer and Save 0 to variable

			for (; pretmp; pretmp = pretmp->mNextNode) //Move node for comparison
			{
				for (tmp = pretmp->mNextNode; tmp; tmp = tmp->mNextNode) //Move node for comparison
				{
					if (pretmp->mData > tmp->mData) //Compare the Data
					{//Swap the Data
						Save = pretmp->mData;
						pretmp->mData = tmp->mData;
						tmp->mData = Save;
					}
				}
			}
		}

		virtual void			clear() //The function that delete all List
		{
			Node<T>* tmp; //Declare tmp

			while (mHead->mNextNode != NULL) //If mHead->mNextNode is not NULL, repeat the function
			{ //Change the head and delete the Node
				tmp = mHead;
				mHead = tmp->mNextNode;
				delete tmp;
			}
			mHead = NULL; //Save NULL to mHead
			delete mHead; //Delete mHead
		}

		friend ostream& operator<<(ostream& os, const LinkedList<T>& data)
		{
			Node<T>* tmp = data.mHead;

			int idx = 0;

			if (data.mHead == NULL)
			{
				os << "This linked list is empty." << endl;
			}
			else
			{
				os << "------------------------------------" << endl;
				for (idx = 0; tmp != NULL; idx++)
				{
					cout << "idx: " << idx << ", data: " << tmp->mData << endl;
					tmp = tmp->mNextNode;
				}
				os << "------------------------------------" << endl;
			}
			return os;
		}
	};
}

