#pragma once

#include <string>
#include <iostream>
using namespace std;

class WordList //Declare WordList
{
public:
	void insert(const char* word) //This function works for links between word
	{
		wordNode* pos = &head; //Save head to pos
		for (; pos->next; pos = pos->next) //Repeat the function if pos->next is not NULL
		{
			if (word == pos->next->word) //if pos->next->word is word
				return; //return

			if (word < pos->next->word) //if pos->next->word > word
				break; //break
		}

		wordNode* node = new wordNode; //Create new Node
		node->next = pos->next; //Save pos->next to node->next
		node->word = word; //Save word to node->word

		pos->next = node; //Save node to pos->next
	}

	void show() //This function show the List of word
	{
		for (wordNode* node = head.next; node; node = node->next) //If node is not Null, repeat the function
			cout << "->" << node->word;
	}

private:
	class wordNode //Declare class in WordList
	{
	public:
		wordNode* next; //For point next Node
		string word; //For Save data
	};
	wordNode head;
};