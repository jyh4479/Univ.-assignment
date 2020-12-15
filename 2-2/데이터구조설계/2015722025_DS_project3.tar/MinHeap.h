#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#define INF 999999999
#include <utility>
#include <vector>
#include <iostream>
using namespace std;
template<typename TKey, typename TValue>
class MinHeap
{
private:
	// array for the elements which should be heap-sorted
	vector<pair<TKey, TValue>> m_vec;
public:
	MinHeap() {}
	pair<TKey, TValue> Top() { return m_vec[0]; }//return Top data

	pair<TKey, TValue> Get(TValue target) //for get pair
	{
		for (vector<int>::size_type i = 0; i < m_vec.size(); i++)
		{
			if (m_vec[i].second == target) return m_vec[i];
		}
		return make_pair(INF, INF);
	}

	bool IsEmpty() //for check empty
	{
		if (m_vec.size() == 0) return true;
		return false;
	}

	void Push(TKey key, TValue value)
	{
		int p_pos = m_vec.size() / 2 - 1;//Declare parent position
		int pos = m_vec.size() - 1; //for reposition

		m_vec.push_back(make_pair(key, value)); //insert

		if (p_pos < 0) return; //if p_pos is smaller than 0
		
		while (pos > 0 && m_vec[p_pos].first > m_vec[pos].first) 
		{ //repeat function pos is bigger than 0  and (compare vector)
			swap(m_vec[p_pos], m_vec[pos]); //swap
			pos = p_pos;
			p_pos = (p_pos - 1) / 2;
		}
	}

	void Pop() //function of pop
	{
		if (m_vec.size() == 0) throw "Empty Heap!";//check Empty
		
		else if (m_vec.size() == 1) //if size is 1
		{
			m_vec.pop_back();//delete
			return;//return
		}

		if (m_vec[0] == m_vec[m_vec.size() - 1])//check vector
			return;
		
		m_vec[0] = m_vec[m_vec.size() - 1];
		m_vec.pop_back();//delete
		Heapify(0);
	}


	void DecKey(TValue target, TKey newKey)//Declare Decrease key
	{
		vector<int>::size_type i;
		
		for (i = 0; i < m_vec.size(); i++) //check target
			if (m_vec[i].second == target) break;
		
		if (i == m_vec.size()) return; //there is no target
		if (m_vec[i].first < newKey) throw "key is invalue";

		m_vec[i] = make_pair(newKey, target);

		while (i != 0 && m_vec[(i - 1) / 2].first > m_vec[i].first)
		{
			swap(m_vec[i], m_vec[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

private:
	void swap(pair<TKey, TValue>& a, pair<TKey, TValue>& b) //for swap
	{
		pair<TKey, TValue> temp = a;
		a = b;
		b = temp;
	}

	void Heapify(int index) //Heapify
	{
		int l = index * 2 + 1;
		int r = index * 2 + 2;
		int smallest = index;
		
		if (l < (int)m_vec.size() && m_vec[l].first < m_vec[smallest].first)
			smallest = l;
		
		else if (r < (int)m_vec.size() && m_vec[r].first < m_vec[smallest].first)
			smallest = r;
		
		if (smallest != index)
		{
			swap(m_vec[index], m_vec[smallest]);
			Heapify(smallest);
		}
	}
};

#endif