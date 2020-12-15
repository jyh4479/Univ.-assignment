#ifndef VERTEX_H
#define VERTEX_H

#ifndef NULL
#define NULL	0
#endif

#include "Edge.h"

class Vertex
{
private:
    // the key of this vertex
    int m_key;
    // the number of the edges from this vertex to others
    int m_size=0;
    // the head pointer for the linked list of the edges
    Edge* m_pEHead=NULL;
    // the next pointer for the linked list of the vertics
    Vertex* m_pNext=NULL;

public:
	Vertex() { m_key = 0; };
	Vertex(int key) { m_key = key; };
	~Vertex() {};

   
	void SetNext(Vertex* pNext) { m_pNext = pNext; };
   
	int GetKey() const { return m_key; };
   
	Vertex* GetNext() const { return m_pNext; };

	int Size() const { return m_size; };

    
    void AddEdge(int edgeKey, int weight);
    
	Edge* GetHeadOfEdge() const {return m_pEHead;};
   
    void Clear();
};

#endif
