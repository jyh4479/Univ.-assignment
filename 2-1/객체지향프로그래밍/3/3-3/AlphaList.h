#pragma once

#include "WordList.h"

class AlphaList //Declare AlphaList
{
public:
	void insert(const char* word) //This function works for links word
	{
		char alpha = word[0]; //Save word[0] to alpha

		alphabetNode* pos = &head; //Save head to pos
		for (; pos->next; pos = pos->next) //Repeat the function if pos->next is not NULL
		{
			if (alpha == pos->next->alpha) //If alpha is pos->next->alph
			{
				pos->next->wordList.insert(word); //Practice the insert function
				return; //return
			}

			if (alpha < pos->next->alpha) //If alpha < pos->next->alpha
				break; //break;
		}

		alphabetNode* node = new alphabetNode; //Create New Node
		node->next = pos->next; //Save pos->next to node->next
		node->alpha = alpha; //Save alpha to node->alpha
		node->wordList.insert(word); //practice the insert function

		pos->next = node; //Save node to pos->next
	}

	void alphainsert(const char* word) //This function work for links alphabet
	{
		char alpha = word[0]; //Save word[0] to alpha
		alphabetNode* pos = &head; //Save head to pos

		for (; pos->next; pos = pos->next); //If poss->next is not NULL, repeat the function
		alphabetNode* node = new alphabetNode; //Create new Node

		node->alpha = alpha; // Save data to Node
		pos->next = node; //link the Node
	}

	void show() //Print the list
	{
		for (alphabetNode* node = head.next; node; node = node->next) //Repeat the function if the node is not NULL
		{
			cout << node->alpha; //Print alphabet
			node->wordList.show(); //Call the funtion of showing the word list
			cout << endl;
		}
	}

private:
	class alphabetNode //Declare class in AlphaList
	{
	public:
		alphabetNode* next; //For point the Next Node
		char alpha; //For Save data
		WordList wordList; //For use wordList function
	};
	alphabetNode head;
};
