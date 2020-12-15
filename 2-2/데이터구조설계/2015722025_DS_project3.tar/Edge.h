#ifndef EDGE_H
#define EDGE_H

#ifndef NULL
#define NULL	0
#endif

class Edge
{
private:
    int m_key;
    int m_weight;
    Edge* m_pNext=NULL;

public:
	Edge()
	{
		m_key = 0;
		m_weight = 0;
	};


	Edge(int key, int weight)
	{
		m_key = key;
		m_weight = weight;
	};

    // set the next pointer of this edge
	void SetNext(Edge* pNext) { m_pNext = pNext; };

    // get the key of this edge
	int GetKey() const { return m_key; };

    // get the weight of this edge
	int GetWeight() const { return m_weight; };

    // get the next pointer of this edge
	Edge* GetNext() const { return m_pNext; };

	void Setweight(int weight) { m_weight = weight; };
};

#endif