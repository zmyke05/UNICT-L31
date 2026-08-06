#include <iostream>
#include "AGraph.h"

int main()
{
	AGraph<char> g (10);
	g.addVertex('a');
	g.addVertex('b');
	g.addVertex('c');
	g.addVertex('d');
	g.addVertex('e');
	g.addVertex('f');
	g.addVertex('g');
	g.setSourcePosition(0);	

	g.addEdge('a', 'b');
	g.addEdge('a', 'c');	
	g.addEdge('b', 'd');
	g.addEdge('b', 'e');
	g.addEdge('c', 'f');
	g.addEdge('c', 'g');
	g.addEdge('g', 'a');

	cout << "The vertices are:" << endl;
	g.printVertices();
	cout << "Adjacency Matrix:" << endl;
	g.printAdjMatrix();
	cout << "BFS" << endl;
	g.BFS();
	cout << "DFS" << endl;
	g.DFS();
	return 0;
}