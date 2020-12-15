#include "Vertex.h"

void Vertex::AddEdge(int edgeKey, int weight)
{
	if (m_pEHead == NULL) //if Head is NULL
	{
		Edge *newNode = new Edge(edgeKey, weight); //create new Edge for head
		m_pEHead = newNode; //declare head
		m_size++;
		return; //return
	}

	else
	{
		Edge *newNode = new Edge(edgeKey, weight); //create new Edge
		Edge *tmp = m_pEHead; //Save data of Head to tmp
		while (tmp->GetNext() != NULL) tmp = tmp->GetNext(); //Move tmp to tail

		tmp->SetNext(newNode); //set newNode
		m_size++;
		return; //return
	}
}

void Vertex::Clear()
{
	Edge * tmp = m_pEHead;
	if (m_pEHead == NULL) //if no more already, return
	{
		return;
	}
	else
	{
		/*until the last*/
		while (tmp != NULL)
		{
			tmp = m_pEHead->GetNext();//remove become next nod
			delete m_pEHead;
			m_pEHead = tmp;
		}
	}
}