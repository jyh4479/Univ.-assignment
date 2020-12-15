#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define DFS_FIRST_PATH


Graph::Graph()
{
	m_pVHead = NULL;
    // TODO: implement
}
Graph::~Graph()
{
    // TODO: implement
}

void Graph::AddVertex(int vertexKey)
{
	if (m_pVHead == NULL) //if vertex head is NULL
	{
		Vertex* newNode = new Vertex(vertexKey); //create new Node for head
		m_pVHead = newNode; //declare Head
		m_vSize++;
		return; //return
	}

	else
	{
		Vertex* newNode = new Vertex(vertexKey); //create new Node
		Vertex* tmp=m_pVHead; //save data of head to tmp
		while (tmp->GetNext() != NULL) tmp = tmp->GetNext(); //Move tmp to tail

		tmp->SetNext(newNode); //set newNode
		m_vSize++;
		return;
	}
}

Vertex * Graph::FindVertex(int key)
{
	if (key < 0) { return NULL; } //check value of key

	Vertex *tmp = m_pVHead;

	while (tmp->GetKey() != key) //repeat until find vertex
	{	
		tmp = tmp->GetNext();
		if (tmp == NULL)
			return NULL;
	}

	return tmp; //return
}

void Graph::Print(std::ofstream & fout) //for printing data
{
	Vertex * tmp = m_pVHead; //declare head to tmp
	Edge * Etmp; //Edge tmp

	////////area of printing data////////
	fout << "======PRINT======" << endl;
	while (tmp) //repeat function if tmp is not null
	{
		Etmp = tmp->GetHeadOfEdge();

		for (int time = 0; time < m_vSize; time++)
		{
			if (Etmp==NULL)
				fout << "0" << " ";

			else if (time == Etmp->GetKey())
			{
				fout << Etmp->GetWeight() << " ";
				Etmp = Etmp->GetNext();
			}

			else fout << "0" << " ";
		}
		fout << endl;
		tmp = tmp->GetNext(); //move tmp
	}
	fout << "=================" << endl;
	return;
}


void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
	if (m_pVHead == NULL) throw "Create Vertax Node begin addedge"; //if head is null

	Vertex* tmp = FindVertex(startVertexKey);//Find start vertex

	if (tmp == NULL) return; //if tmp is null return

	tmp->AddEdge(endVertexKey, weight);//add edge
}

Edge* Graph::FindEdge(int startkey, int endkey) //for find edge
{
	Vertex* tmp;//Declare tmp

	for (tmp = m_pVHead; tmp->GetKey() != startkey; tmp = tmp->GetNext())
	{//repeat function
		if (tmp == NULL)
			return NULL;
	}
	
	Edge* edge;//Declare edge

	for (edge = tmp->GetHeadOfEdge(); edge->GetKey() != endkey; edge = edge->GetNext())
	{//repeat function
		if (edge == NULL)
			return NULL;
	}

	return edge; //return edge
}

void Graph::Clear() //function of Clear
{
	Vertex* tmp = m_pVHead;//load head

	while (tmp != NULL)//if tmp is null...end function
	{
		Vertex* vtmp = tmp;
		tmp = tmp->GetNext();
		vtmp->Clear();
		delete vtmp;
	}
}

bool Graph::IsNegativeEdge() //for check negative weight
{
	Vertex* tmp;
	Edge* Etmp;

	for (tmp = m_pVHead; tmp; tmp = tmp->GetNext()) //check all linked list
		for (Etmp = tmp->GetHeadOfEdge(); Etmp; Etmp = Etmp->GetNext())
		{
			if (Etmp->GetWeight() < 0) //check negative weight
				return true;
		}
	return false;
}

vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey)
{
	if (IsNegativeEdge())
		return vector<int>(0, 0); //check negative weight
	
	int count = 0;//for counting non visited vertex
	int vertex_key = startVertexKey;
	bool *visit = new bool[m_vSize]; //for check visiting
	
	Stack<int> s;
	vector<int> path;
	
	for (int i = 0; i < m_vSize; i++)//initialize
		visit[i] = false;

	s.Push(vertex_key);
	while (1)
	{
		count = 0;
		vertex_key = s.Top(); //Top data
		if (visit[vertex_key] == false) //check visiting
			path.push_back(vertex_key); //insert
		
		if (path.back() == endVertexKey)
			break; //End function
		
		if (visit[vertex_key] == false) //check visiting
		{
			visit[vertex_key] = true;
		}

		Vertex* Vtmp = FindVertex(vertex_key);
		Edge* Etmp = Vtmp->GetHeadOfEdge();//head of edge
		for (; Etmp; Etmp = Etmp->GetNext())
		{
			if (!visit[Etmp->GetKey()])//check non visited vertex
			{
				s.Push(Etmp->GetKey());
				count++;//counting
			}
		}

		if (count == 0) //check counting
		{
			path.pop_back();
			s.Pop();//Pop
		}
	}
	delete[] visit;
	return path; //return path
}

vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	if (IsNegativeEdge()) //check negative weight
		return vector<int>(0, 0);

	set<pair<int, int> > st;//Declare set
	vector<int> dist(m_vSize, IN_FINITY); //Declare dist
	vector<vector<int> > path(m_vSize, vector<int>(m_vSize, IN_FINITY)); //Declare paths
	
	for (int i = 0; i != m_vSize; i++)//initialize
		path[i][0] = startVertexKey;

	st.insert(std::make_pair(0, startVertexKey)); //insert
	dist[startVertexKey] = 0;

	while (!st.empty())
	{
		pair<int, int> tmp = *(st.begin());//Declare tmp

		st.erase(st.begin());//delete

		int u = tmp.second;//Delcare u
		Edge* Etmp = FindVertex(u)->GetHeadOfEdge();

		for (; Etmp; Etmp = Etmp->GetNext())
		{
			int v = Etmp->GetKey(); //key
			int weight = Etmp->GetWeight(); //weight

			if (dist[v] > dist[u] + weight)
			{
				if (dist[v] != IN_FINITY) //check dist[v]
					st.erase(st.find(std::make_pair(dist[v], v)));//delete set

				dist[v] = dist[u] + weight;//update distance
				st.insert(std::make_pair(dist[v], v));//insert set

				int i = 0;
				for (i = 0; IN_FINITY != path[u][i]; i++)//for update
				{
					path[v][i] = path[u][i];
					if (i == m_vSize - 1) break;
				}
				path[v][i] = v;
			}
		}
	}
	return path[endVertexKey];
}

vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey) 
{
	if (IsNegativeEdge()) //check negative weight
		return vector<int>(0, 0); 

	MinHeap<int, int> heap; //Declare heap
	vector<int> dist(m_vSize, IN_FINITY);//Declare dist
	vector<vector<int> > path(m_vSize, vector<int>(m_vSize, IN_FINITY));//Declare path
	
	for (int i = 0; i != m_vSize; i++)//initialize
	{
		path[i][0] = startVertexKey;
		heap.Push(dist[i], i);
	}

	dist[startVertexKey] = 0;
	heap.DecKey(startVertexKey, dist[startVertexKey]);//run DecKey

	while (!heap.IsEmpty()) //check Empty of heap
	{
		pair<int, int> tmp = heap.Top();//Delcare tmp
		heap.Pop();//Pop

		int u = tmp.second;
		Edge* Etmp = FindVertex(u)->GetHeadOfEdge();

		for (; Etmp; Etmp = Etmp->GetNext())
		{ //repeat function Etmp is not NULL
			int v = Etmp->GetKey();
			int weight = Etmp->GetWeight();
	
			if (dist[v] > dist[u] + weight)
			{
				if (heap.Get(v) != std::make_pair(IN_FINITY, IN_FINITY) && dist[u] != IN_FINITY && weight + dist[u] < dist[v])
				{ //check each distance
					dist[v] = dist[u] + weight;
					heap.DecKey(v, dist[v]);
				}

				int i = 0;
				for (i = 0; IN_FINITY != path[u][i]; i++) {
					path[v][i] = path[u][i];
					if (i == m_vSize - 1) break;
				}
				path[v][i] = v;
			}
		}
	}
	return path[endVertexKey];
}

vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	vector<int> dist(m_vSize, IN_FINITY);//Declare dist
	vector<vector<int> > path(m_vSize, vector<int>(m_vSize, IN_FINITY));//Declare path
	bool check_cycle; //for checking negative cycle

	for (int i = 0; i != m_vSize; i++)//initialize
		path[i][0] = startVertexKey;
	
	dist[startVertexKey] = 0;
	//////////check all edge//////////
	for (int i = 0; i < m_vSize; i++) 
	{
		check_cycle = false;
		for (int j = 0; j < m_vSize; j++)
		{
			Edge* Etmp = FindVertex(j)->GetHeadOfEdge();
			for (; Etmp; Etmp = Etmp->GetNext())
			{
				int v = Etmp->GetKey();//Declare v
				int weight = Etmp->GetWeight();//Declare weight

				if (dist[j] != IN_FINITY && dist[v] > dist[j] + weight) 
				{ //dist[j] is not infinity and dist[v] bigger than dist[j]+weight
					dist[v] = dist[j] + weight;
					check_cycle = true;
				
					int k;
					for (k = 0; IN_FINITY != path[j][k]; k++)
					{
						path[v][k] = path[j][k];
						if (k == m_vSize - 1) break;//if k is m_vSize, break loop
					}
					path[v][k] = v;
				}
			}
		}
	}
	if (check_cycle == true)//check negative cycle
		return vector<int>(0, 0); 

	return path[endVertexKey];
}

std::vector<vector<int>> Graph::FindShortestPathFloyd() //function of floyd
{
	std::vector<std::vector<int> > paths(m_vSize, std::vector<int>(m_vSize, IN_FINITY));
	int i = 0, j = 0, k = 0;

	Vertex *tmp = m_pVHead; //Head of vertex
	Edge*Etmp;
	//////////////////////setting table//////////////////////
	for (int vtime = 0, i = 0; vtime < m_vSize; vtime++, i++)
	{
		Etmp = tmp->GetHeadOfEdge();//Edge head
		for (int etime = 0, j = 0; etime < m_vSize; etime++, j++)
		{
			if (etime == vtime)
				paths[i][j] = 0;

			else if (Etmp == NULL)
				paths[i][j] = IN_FINITY;

			else if (etime == Etmp->GetKey())
			{
				paths[i][j] = Etmp->GetWeight();
				Etmp = Etmp->GetNext();
			}

			else
				paths[i][j] = IN_FINITY;
		}
		tmp = tmp->GetNext();
	}

	for (int k = 0; k < m_vSize ; k++) //Floyd algorithm
		for (int i = 0; i < m_vSize; i++)
			for (int j = 0; j < m_vSize; j++)
				paths[i][j] = min( paths[i][j], paths[i][k] + paths[k][j] );

	return paths;
}

void Graph::sortingpath(int *path, int size) //for sorting path
{
	if (size < 7) //check size of segment
	{
		for (int j = 2; j <= size; j++) //repeat function
		{
			int tmp = path[j];
			Insertsort(tmp,path,j-1);
		}
	}

	else //segment size > 7
		Quicksort(path,1,size);

	return;
}

void Graph::Insertsort(int e, int* path, int i) //Insertion sort
{
	path[0] = e; //save e to path[0]
	while (e < path[i]) //find area to place value
	{
		path[i + 1] = path[i];//make area
		i--;
	}
	path[i + 1] = e;//place value of e
	
	return;
}

void Graph::Quicksort(int* path, int left, int right) //Quick sort
{
	if (left < right) //check left, right
	{
		int i = left, j = right + 1; //setting
		int pivot = path[left];

		do //do while
		{
			do i++; while (path[i] < pivot);
			do j--; while (path[j] > pivot);
			if (i < j) swap(path[i], path[j]);
		} while (i < j);

		swap(path[left], path[j]); //swap value

		Quicksort(path, left, j - 1); //reculsive function
		Quicksort(path, j + 1, right);
		return;
	}
}



int Graph::min(int a, int b) //for return small value
{
	if (a < b)
		return a;
	else 
		return b;
}
