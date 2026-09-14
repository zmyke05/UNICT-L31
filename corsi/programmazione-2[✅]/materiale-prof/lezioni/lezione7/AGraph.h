using namespace std;

#include <limits.h>
#include "../Lezione5/LList.h"

template<class T> class AGraph
{
private:
	T** data;
	bool** adj;
	size_t size;
	size_t capacity;
	int source;
	int* findVertices(const T& first, const T& second) const
	{
		int* ret = new int[2]{ -1,-1 };
		for (size_t i = 0; i < size; i++)
		{
			if (*data[i] == first && ret[0] == -1)
				ret[0] = i;
			else if (*data[i] == second && ret[1] == -1)
				ret[1] = i;
			if (ret[0] != -1 && ret[1] != -1)
				return ret;
		}
		return ret;
	}

	bool checkAdjacency(const size_t& pos1, const size_t& pos2)
	{
		if (pos1 < size && pos2 < size)
		{
			return adj[pos1][pos2];
		}
		return false;
	}

	

	void BreadthFirstSearch(const size_t& source)
	{		
		int* color = new int[this->getSize()];
		int* distances = new int[this->getSize()];
		int* predecessors = new int [this->getSize()];		
		//init algorithm
		for (size_t i = 0; i < this->getSize(); i++)
		{
			if (i != source)
			{
				color[i] = 0;
				distances[i] = INT_MIN;
			}
			else
			{
				color[1] = 1;
				distances[i] = 0;
			}
			predecessors[i] = -1;
		}
		//core
		LinkedList<size_t>* queue = new LinkedList<size_t>();
		queue->insertTail(new LinkedNode<size_t>(source)); //enqueue		
		cout << "Visiting: ";
		while (queue->isEmpty() == false)
		{
			LinkedNode<size_t>* head = queue->removeHead(); //dequeue				
			for (size_t i = 0; i < this->getSize(); i++)
				if (this->checkAdjacency(head->getKey(), i))
				{
					if (color[i] == 0) //If white
					{
						color[i]++; //GRAY
						distances[i]++;
						predecessors[i] = head->getKey();
						queue->insertTail(new LinkedNode<size_t>(i));
					}

				}
			color[head->getKey()]++; //BLACK
			cout <<  data[head->getKey()] << " ";
			delete head;
		}
		
		cout << endl;
		for (size_t i = 0; i < size; i++)
		{
			string s = (predecessors[i] >= 0) ? data[predecessors[i]] : "Null";
			cout << "Precedessors of " << data[i] << " is " << s << endl;
		}
		//cleaning up
		delete[]color;
		delete[]predecessors;
		delete queue;
	}


	void DepthFirstSearchVisit(size_t& vertex, int& time,  int color[], int discovered[], int finished[], int predecessors[])
	{
		time++;
		discovered[vertex] = time;
		color[vertex]++; //GRAY
		cout << data[vertex] << " ";
		for (size_t i = 0; i < this->getSize(); i++)
			if (this->checkAdjacency(vertex, i))
			{
				if (color[i] == 0) //If white
				{
					predecessors[i] = vertex;
					DepthFirstSearchVisit(i, time, color, discovered, finished, predecessors);
				}
			}
		color[vertex]++; //black
		time++;
		finished[vertex] = time;		
	}

	void DepthFirstSearch()
	{		
		int* color = new int[this->getSize()];		
		int* predecessors = new int[this->getSize()];
		int* discovered = new int[this->getSize()];
		int* finished = new int[this->getSize()];
		int time = 0;
		/*
		   init algorithm
		*/
		for (size_t i = 0; i < size; i++)
		{
			color[i] = 0;
			predecessors[i] = -1;
			discovered[i] = 0;
			finished[i] = 0;
		}
		cout << "Visiting: ";
		for (size_t i = 0; i < size; i++)		
			if (color[i] == 0)			
				DepthFirstSearchVisit(i, time, color, discovered, finished, predecessors);					
		cout << endl;
		for (size_t i = 0; i < size; i++)
		{
			string s = (predecessors[i] >= 0) ? data[predecessors[i]] : "Null";
			cout << "Precedessors of " << data[i] << " is " << s << endl;
		}
		//cleaning up
		delete[] color;
		delete[] discovered;
		delete[] finished;
		delete[] predecessors;
	}

public:
	AGraph() : data{ new T * [0] }, adj{ new bool[0] }, size{ 0 }, capacity{ 0 }, source{-1} {}
	AGraph(size_t capacity) : size{ 0 }, capacity { capacity }, source{-1}
	{
		data = new T * [capacity];
		adj = new bool* [capacity];
		for (size_t i = 0; i < capacity; i++)
			adj[i] = new bool[capacity] {0};
	}
	size_t getSize() const { return size; }
	size_t getCapacity() const { return capacity; }
	int getSourcePosition() { return source; }	
	bool setSourcePosition(const int& source)
	{		
		if (source < size)
		{
			this->source = source;
			return true;
		}
		return false;
	}
	
	
	int findVertex(const T& vertex) const
	{
		int ret = -1;
		for (size_t i = 0; i < size; i++)
		{
			if (*data[i] == vertex)
			{
				ret = i;
				break;
			};
		}
		return ret;
	}

	int addVertex(const T& vertex)	
	{
		T* val = new T(vertex);
		if (size < capacity)
		{			
			data[size] = val;
			size++;
			return size-1;
		}
		return -1;
	}
		

	bool addEdge(const T& first, const T& second)
	{
		int* pos = findVertices(first, second);
		bool ret = false;
		if (pos[0] != -1 && pos[1] != -1)
		{
			adj[pos[0]][pos[1]] = true;
			ret = true;
		}
		delete[] pos;
		return ret;
	
	}

	void printVertices()
	{
		for (size_t i = 0; i < size; i++)
			cout << *(data[i]) << " ";
		cout << endl;
	}

	void printAdjMatrix()
	{
		for (size_t i = 0; i < size; i++)
			cout << "    " << i ;
		cout << endl;
		for (size_t i = 0; i < size; i++)
			{
			 cout << i  << " ";
			 for (size_t j = 0; j < size; j++)			
				cout << (adj[i][j] ? "True" : "False") << " ";
			 cout << endl;
			}
		cout << endl;
	}

	void BFS()
	{	  
      if(source>=0)
		 BreadthFirstSearch(static_cast<size_t>(source));
	}

	void DFS()
	{				
		DepthFirstSearch();				
	}
};