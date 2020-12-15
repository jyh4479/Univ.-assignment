#include "Manager.h"
#include <cstring>

Manager::~Manager() //structor
{
	if (fout.is_open())
		fout.close();
}

void Manager::Run(const char* filepath) //Run
{
	fout.open(RESULT_LOG_PATH); //log file

	fstream command; //for get command from txt
	command.open(filepath);

	if (!command)
	{
		fout << "=======SYSTEM=======" << endl;
		fout << "CommandFileNotExist" << endl;
		fout << "====================" << endl;
		PrintError(CommandFileNotExist);
		return;
	}

	char cmd[50];//variable for getting data of command
	char *Parameter;
	char *Parameter2;
	char *Parameter3;

	while (!command.fail())//check for Linux
	{
		int Load_flag = 0; //flag for defence run Load twice
		command.getline(cmd, 50); //load command

		if (strlen(cmd)<2) break; // white space skip

		if (cmd[strlen(cmd) - 1] == '\r')
			cmd[strlen(cmd) - 1] = '\0';//for run in Linux

		Parameter = strtok(cmd, " ");//command

		if (strcmp(Parameter, "LOAD") == 0 && Load_flag == 0)//check command and flag
		{
			Result tmp;//for check result
			Parameter2 = strtok(NULL, " ");//name of data txt
			Load_flag = 1;
			tmp = Load(Parameter2);//load

			if (tmp != Success)//if fail load
				Load_flag = 0;

			PrintError(tmp);
		}

		else if (strncmp(Parameter, "PRINT", 5) == 0)//print
		{
			Result tmp;//for check result

			tmp = Print();//run print function

			PrintError(tmp);
		}

		else if (strncmp(Parameter, "DFS", 3) == 0)//DFS function
		{
			Result tmp;//for check result
			fout << "=========DFS=========" << endl;
			Parameter2 = strtok(NULL, " ");//paramter of vertex
			Parameter3 = strtok(NULL, " ");
			if (Parameter2 == NULL || Parameter3 == NULL)
			{
				fout << "VertexKeyNotExist" << endl;
				fout << "=====================" << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}

			int start, end;
			start = atoi(Parameter2);//change type of variable
			end = atoi(Parameter3);

			tmp = FindPathDfs(start, end);//run DFS
			fout << "=====================" << endl;

			PrintError(tmp);
		}

		else if (strncmp(Parameter, "DIJKSTRA", 8) == 0)
		{
			Result tmp;
			fout << "=======DIJKSTRA=======" << endl;
			Parameter2 = strtok(NULL, " ");//paramter of vertex
			Parameter3 = strtok(NULL, " ");
			if (Parameter2 == NULL || Parameter3 == NULL)
			{
				fout << "VertexKeyNotExist" << endl;
				fout << "=====================" << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}

			int start, end;
			start = atoi(Parameter2);//change type of variable
			end = atoi(Parameter3);

			tmp = FindShortestPathDijkstraUsingSet(start, end);//run Dijkstra
			fout << "=====================" << endl;

			PrintError(tmp);
		}

		else if (strncmp(Parameter, "DIJKSTRAMIN", 11) == 0)
		{
			Result tmp;
			fout << "=======DIJKSTRAMIN=======" << endl;
			Parameter2 = strtok(NULL, " ");//paramter of vertex
			Parameter3 = strtok(NULL, " ");

			if (Parameter2 == NULL || Parameter3 == NULL)
			{
				fout << "VertexKeyNotExist" << endl;
				fout << "=====================" << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			int start, end;
			start = atoi(Parameter2);//change type of variable
			end = atoi(Parameter3);

			tmp = FindShortestPathDijkstraUsingMinHeap(start, end);//run Dijkstra
			fout << "=====================" << endl;

			PrintError(tmp);
		}

		else if (strncmp(Parameter, "BELLMANFORD", 11) == 0)
		{
			Result tmp;
			fout << "=====BELLMANFORD=====" << endl;
			Parameter2 = strtok(NULL, " ");//paramter of vertex
			Parameter3 = strtok(NULL, " ");

			if (Parameter2 == NULL || Parameter3 == NULL)
			{
				fout << "VertexKeyNotExist" << endl;
				fout << "=====================" << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}

			int start, end;
			start = atoi(Parameter2);//change type of variable
			end = atoi(Parameter3);

			tmp = FindShortestPathBellmanFord(start, end);//run BellmanFord
			fout << "=====================" << endl;

			PrintError(tmp);
		}

		else if (strncmp(Parameter, "FLOYD", 5) == 0)
		{
			Result tmp;
			fout << "========FLOYD========" << endl;
			tmp = FindShortestPathFloyd();//run Floyd
			fout << "=====================" << endl;

			PrintError(tmp);
		}

		else
		{
			fout << "========" << Parameter << "========" << endl;
			fout << "NonDefinedCommand" << endl;
			fout << "================" << endl;

			PrintError(NonDefinedCommand);
		}
	}
	return;
}
void Manager::PrintError(Result result) //for print error code
{
	fout << "=================" << endl;
	fout << "Error code: " << result << std::endl;
	fout << "=================" << endl;
}


Result Manager::Load(const char* filepath) //The function of load
{
	fstream datafile; //for getting information of data
	datafile.open(filepath);

	if (datafile.fail()) //check file of data
	{
		fout << "======LOAD======" << endl;
		fout << "LoadFileNotExist" << endl;
		fout << "================" << endl;
		return LoadFileNotExist;
	}

	char data[5];
	int vertex_number;//atoi data
	int weight_number;//atoi data
	int vertex_key;
	int edge_key;

	datafile >> data;//get data
	vertex_number = atoi(data); //change type

								////////////create linked list////////////
	for (vertex_key = 0; vertex_key<vertex_number; vertex_key++)
	{
		m_graph.AddVertex(vertex_key);//add vertex

		for (edge_key = 0; edge_key < vertex_number; edge_key++)
		{
			datafile >> data;
			weight_number = atoi(data); //change type

			if (weight_number != 0)
				m_graph.FindVertex(vertex_key)->AddEdge(edge_key, weight_number);//add edge
		}
	}

	fout << "======LOAD======" << endl;
	fout << "Success" << endl;
	fout << "================" << endl;

	return Success;
}

Result Manager::Print() //for print function
{
	if (m_graph.getHead() == NULL)
	{
		fout << "======PRINT======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=================" << endl;
		return GraphNotExist;
	}

	m_graph.Print(fout);//call function of print
	return Success;
}

Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { fout << "GraphNotExist" << endl; return GraphNotExist; } //check graph

	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{ //check parameter
		fout << "InvalidVertexKey" << endl;
		return InvalidVertexKey;
	}

	std::vector<int> path = m_graph.FindPathDfs(startVertexKey, endVertexKey); //run DFS

	if (path.size() == 0) { fout << "InvalidAlgorithm" << endl; return InvalidAlgorithm; } //cehck neagative weight

																						   ////////////////for sorting////////////////
	int sortpath[50];
	for (int i = 0; i < path.size(); i++) //copy data of path
		sortpath[i + 1] = path[i];

	int sum = 0;
	int i;

	fout << "shortest path: ";
	for (i = 0; i < path.size() - 1; i++)//for print path
	{
		fout << path[i] << " ";
		sum += m_graph.FindEdge(path[i], path[i + 1])->GetWeight(); //calculate distance
	}
	fout << path[i] << " " << endl; //last path


	fout << "sorted nodes: ";
	m_graph.sortingpath(sortpath, path.size());//run sorting function
	for (int i = 0; i < path.size(); i++) //print
		fout << sortpath[i + 1] << " ";
	fout << endl;

	fout << "path length: ";
	fout << sum << std::endl; //distance
	return Success;
}

Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { fout << "GraphNotExist" << endl; return GraphNotExist; } //for check graph

	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{//check parameter
		fout << "InvalidVertexKey" << endl;
		return InvalidVertexKey;
	}

	std::vector<int> path = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);//run Dijkstra

	if (path.size() == 0) { fout << "InvalidAlgorithm" << endl; return InvalidAlgorithm; }//check negative weight

																						  ////////////////for sorting////////////////
	int sortpath[50] = { NULL };
	for (int i = 0; i < path.size(); i++) //copy data of path
		sortpath[i + 1] = path[i];

	int sum = 0;
	int i;

	fout << "shortest path: ";
	for (i = 0; i < m_graph.Size() - 1; i++)
	{ //for print path
		if (path[i + 1] == IN_FINITY) break;
		sum += m_graph.FindEdge(path[i], path[i + 1])->GetWeight();
		fout << path[i] << " ";
	}
	fout << path[i] << endl;

	fout << "sorted nodes: "; //for print sorted path
	m_graph.sortingpath(sortpath, path.size()); //run sorting
	for (int i = 0; i < path.size() && path[i] != IN_FINITY; i++)//print path
		fout << sortpath[i + 1] << " ";
	fout << endl;

	fout << "path length: ";
	fout << sum << endl;
	return Success;
}

Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { fout << "GraphNotExist" << endl; return GraphNotExist; } //check graph
	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{ //check parameter
		fout << "InvalidVertexKey" << endl;
		return InvalidVertexKey;
	}
	vector<int> path = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);//run Dijkstra

	if (path.size() == 0) { fout << "InvalidAlgorithm" << endl; return InvalidAlgorithm; }//check negative weight

																						  ////////////////for sorting////////////////
	int sortpath[50] = { NULL };
	for (int i = 0; i < path.size(); i++) //copy data of path
		sortpath[i + 1] = path[i];

	int sum = 0;
	int i;

	fout << "shortest path: ";
	for (i = 0; i < m_graph.Size() - 1; i++)
	{//for print path
		if (path[i + 1] == IN_FINITY) break;
		sum += m_graph.FindEdge(path[i], path[i + 1])->GetWeight();
		fout << path[i] << " ";
	}
	fout << path[i] << endl;

	fout << "sorted nodes: "; //for print sorted path
	m_graph.sortingpath(sortpath, path.size());
	for (int i = 0; i < path.size() && path[i] != IN_FINITY; i++)
		fout << sortpath[i + 1] << " ";
	fout << endl;

	fout << "path length: ";
	fout << sum << endl;
	return Success;
}

Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { fout << "GraphNotExist" << endl; return GraphNotExist; }//for check graph
	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{//for check parameter
		fout << "InvalidVertexKey" << endl;
		return InvalidVertexKey;
	}
	vector<int> path = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);//run BellmanFord

	if (path.size() == 0) { fout << "NegativeCycleDetected" << endl; return NegativeCycleDetected; }//for check negative weight

 ////////////////for sorting////////////////
	int sortpath[50] = { NULL };
	for (int i = 0; i < path.size(); i++) //copy data of path
		sortpath[i + 1] = path[i];

	int sum = 0;
	int i;

	fout << "shortest path: ";
	for (i = 0; i != m_graph.Size() - 1; i++) {//for print path
		if (path[i + 1] == IN_FINITY) break;
		sum += m_graph.FindEdge(path[i], path[i + 1])->GetWeight();
		fout << path[i] << " ";
	}
	fout << path[i] << endl;

	fout << "sorted nodes: ";
	m_graph.sortingpath(sortpath, path.size());
	for (int i = 0; i < path.size() && path[i] != IN_FINITY; i++)//for print sorted path
		fout << sortpath[i + 1] << " ";
	fout << endl;

	fout << "path length: ";
	fout << sum << endl;
	return Success;
}

Result Manager::FindShortestPathFloyd()
{
	if (m_graph.Size() == 0) { fout << "GraphNotExist" << endl; return GraphNotExist; }

	Vertex *vtmp = m_graph.FindVertex(0); //load head
	Edge *etmp;

	/////////////start Floyd function/////////////
	std::vector<std::vector<int> > result;
	std::vector<std::vector<int> > check_cycle;

	result = m_graph.FindShortestPathFloyd();//Save result of Floyd
	check_cycle = result;

	for (int k = 0; k < m_graph.Size(); k++) //Floyd algorithm
		for (int i = 0; i < m_graph.Size(); i++)
			for (int j = 0; j < m_graph.Size(); j++)
				check_cycle[i][j] = min(check_cycle[i][j], check_cycle[i][k] + check_cycle[k][j]);
	
		for (int i = 0; i<m_graph.Size(); i++) //For checking negative cycle
			for (int j = 0; j<m_graph.Size(); j++)
				if (result[i][j] != check_cycle[i][j]) { fout << "NegativeCycleDetected" << endl; return NegativeCycleDetected; }



	for (int i = 0; i < m_graph.Size(); i++) //Print
	{
		for (int j = 0; j < m_graph.Size(); j++)
			fout << result[i][j] << " ";
		fout << endl;
	}
	return Success;
}

int Manager::min(int a, int b) //for check small value
{
	if (a < b)
		return a;
	else
		return b;
}

