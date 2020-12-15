#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
	class StackNode
	{
	public:
		T Data;
		StackNode* pNext;

		StackNode(T data) : Data(data), pNext(NULL) {}
		// initialization of Data and pNext
	};

private:
	// the head pointer of the stack
	StackNode* m_pTop;

public:
	Stack();
	~Stack();

	
	void Push(T data);
	
	void Pop();
	
	T Top();
	
	bool IsEmpty();
};

#endif

template<typename T>
inline Stack<T>::Stack()
{
	m_pTop = NULL;
}

template<typename T>
inline Stack<T>::~Stack()
{
	while (m_pTop != NULL)
	{
		StackNode* tmp = m_pTop;
		m_pTop = m_pTop->pNext;
		delete tmp;
	}
}

template<typename T>
inline void Stack<T>::Push(T data)
{
	StackNode * newNode = new StackNode(data);
	
	if (m_pTop == NULL) 
		m_pTop = newNode;
	
	else
	{
		newNode->pNext = m_pTop;
		m_pTop = newNode;
	}
}

template<typename T>
inline void Stack<T>::Pop()
{
	if (m_pTop == NULL) 
		return;
	
	else if (m_pTop->pNext == NULL)
	{
		delete m_pTop;
		m_pTop = NULL;
	}
	else
	{
		StackNode *tmp = m_pTop;
		m_pTop = m_pTop->pNext;
		delete tmp;
	}
}

template<typename T>
inline T Stack<T>::Top()
{
	return m_pTop->Data;
}

template<typename T>
inline bool Stack<T>::IsEmpty()
{
	if (m_pTop == NULL) 
		return true;

	else 
		return false;
}
