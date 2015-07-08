#ifndef _GRAPH_H
#define _GRAPH_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "disjoint_set.h"

using namespace std;

// #define DEBUG

template <class T>
class Edge
{
	public:
		T src, dest;
		int cost;
		
		Edge(T src, T dest, int cost) : src(src), dest(dest), cost(cost)
		{
		}
		
		Edge(const Edge &e)
		{
			this->operator=(e);
		}
		
		void operator=(const Edge &e)
		{
			src = e.src;
			dest = e.src;
			cost = e.cost;
		}
};

/*
 * Source        : graph.h
 * Description   : Implementation of Graph algorithms in one class
 * Author        : Suresh. P
 * Email         : sureshsonait@gmail.com
 * Copyright     : This library is free to distribute provided that this comment part is not removed.
 */

template <class T>
class Graph
{
	private:
	
		class Vertex
		{
			private:
				T label;
				multiset<pair<Vertex *, int> > adj;
				multiset<Vertex *> rev; // This is maintained to remove edges, when a vertex, with which the edge is incident on, is removed. It also helps to find the indegree 
				
				typename multiset<pair<Vertex *, int> >::iterator findVertex(Vertex *dest);
	
			public:
				Vertex(T label);
				~Vertex();
	
				void setLabel(T label);
				T getLabel();
	
				bool checkLabel(T label);
				multiset<pair<Vertex *, int> > getAdjacentNodes();
				multiset<Vertex *> getReverseNodes();
	
				void addEdge(Vertex *dest, int cost);
				bool removeEdge(Vertex *dest, int cost);
				bool removeEdge(Vertex *dest);
				void addEdgesInBatch(multiset<pair<Vertex *, int> > new_adj);
				
				bool edgeExists(Vertex *dest);
				bool edgeExists(Vertex *dest, int cost);
				
				unsigned int countEdge(Vertex *dest);
				unsigned int countEdge(Vertex *dest, int cost);
				
				int edgeCost(Vertex *dest);
				vector<int> edgeCosts(Vertex *dest);
				
				int indegree();
				int outdegree();
				
				bool hasNegativeWeightedEdge();
	
				void changeAdjacent(Vertex *dest);
				void removeFromReverse(Vertex *dest);
		};

		map<T, Vertex *> vertices;
		bool directed;
		
		Vertex * findVertex(T label);
		
		vector<Vertex *> findVerticesWithIndegreeZero();
	
	public:
		Graph(bool directed);
		Graph(const Graph<T> &g);
		~Graph();
		
		bool addVertex(T label);
		bool removeVertex(T label);
		
		bool addEdge(T head, T tail, int cost = 1);
		bool removeEdge(T head, T tail, int cost = 1);
		
		int countEdge(T head, T tail);
		int countEdge(T head, T tail, int cost);
		
		bool edgeExists(T head, T tail);
		bool edgeExists(T head, T tail, int cost);
		
		bool pathExists(T start, T end);
		
		vector<int> edgeCosts(T head, T tail);
		
		void operator=(const Graph<T> &g);
		
		int indegree(T label);
		int outdegree(T label);
		
		unsigned int numVertices();
		unsigned int numEdges();
		
		void removeSelfLoops();
		
		bool mergeVertices(T first, T second, T new_label);
		
		T pickRandomVertex();
		Edge<T> * pickRandomEdge();
		
		int minCut();
		
		vector<T> topologicalSort();
		
		vector<T> dfs();
		vector<T> dfs(T start);
		
		vector<T> bfs();
		vector<T> bfs(T start);
		
		map<T, unsigned int> hop_distance(T from);

		pair<vector<T>, vector<vector<int> > > adjacencyList();
		pair<vector<T>, vector<vector<bool> > > connectivityList();
		
		bool isDirected();
		bool isWeighted();
		bool isConnected();
		bool isAcyclic();
		bool isSimple();
		
		bool hasNegativeWeightedEdge();
		
		map<T, pair<T, int> > bfsShortestPath(T source);
		map<T, pair<T, int> > topologicalShortestPath(T source);
		map<T, pair<T, int> > dijkstraShortestPath(T source);
		map<T, pair<T, int> > bellmanFordShortestPath(T source);
		
		map<T, pair<T, int> > shortestPath(T source);
		pair<vector<T>, vector<vector<pair<T, int> > > > shortestPath();
		
		Graph<T> minimumSpanningTree();
		
		void printPath(ostream &out, map<T, pair<T, int> > path);
		void printPath(ostream &out, pair<vector<T>, vector<vector<pair<T, int> > > > dist);
		
		map<T, int> assignVertexNumbers();
		
		vector<T> getVertices();
		vector<pair<T, pair<T, int> > > getEdges();
		
		vector<vector<T> > getVerticesComponentwise();
		vector<Graph<T> > getConnectedComponents();
		
		friend ostream &operator<<(ostream &out, Graph &g)
		{	
			out << (g.isDirected()? "Directed, ": "Undirected, ");
			out << (g.isWeighted()? "Weighted, ": "Unweighted, ");
			out << (g.isAcyclic()? "Acyclic, ": "Cyclic, ");
			out << (g.isConnected()? "Connected, ": "Disconnected, ");
			out << (g.isSimple()? "Simple ": "Non simple ");
			out << "graph" << endl;			

			for(typename map<T, Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
			{	
				out << v->second->getLabel() << " --->  ";
				
				multiset<pair<Vertex *, int> > nbh = v->second->getAdjacentNodes();
				
				for(typename multiset<pair<Vertex *, int> >::iterator adj = nbh.begin(); adj != nbh.end(); adj++)
				{
					out << (*adj).first->getLabel() << "(" << (*adj).second << "), ";
				}
				
				out << "\b\b " << endl;
			}
			
			#ifdef DEBUG
			for(typename map<T, Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
			{
				multiset<Vertex *> nbh = v->second->getReverseNodes();
					
				out << v->second->getLabel() << "(" << nbh.size() << " nodes) --->  ";
				
				for(typename multiset<Vertex *>::iterator adj = nbh.begin(); adj != nbh.end(); adj++)
				{
					out << (*adj)->getLabel() << ", ";
				}
				
				out << "\b\b " << endl;
			}
			#endif
			
			return out;
		}

};

template <class T>
Graph<T>::Vertex::Vertex(T label) : label(label)
{
}

template <class T>
Graph<T>::Vertex::~Vertex()
{
	adj.clear();
	
	// Remove all the edges corresponding to this vertex
	for(typename multiset<Vertex *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		(*v)->removeEdge(this);
	}
	
	rev.clear();
}

template <class T>
void Graph<T>::Vertex::setLabel(T label)
{
	this->label = label;
}

template <class T>
T Graph<T>::Vertex::getLabel()
{
	return label;
}

template <class T>
multiset<pair<typename Graph<T>::Vertex *, int> > Graph<T>::Vertex::getAdjacentNodes()
{
	return adj;
}

template <class T>
multiset<typename Graph<T>::Vertex *> Graph<T>::Vertex::getReverseNodes()
{
	return rev;
}

template <class T>
typename multiset<pair<typename Graph<T>::Vertex *, int> >::iterator Graph<T>::Vertex::findVertex(Graph<T>::Vertex *dest)
{
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->first == dest)
		{
			return itr;
		}
	}
		
	return adj.end();
}

template <class T>
bool Graph<T>::Vertex::checkLabel(T label)
{
	return (label == this->label);
}

template <class T>
void Graph<T>::Vertex::addEdge(Graph<T>::Vertex *dest, int cost)
{
	if(dest != NULL)
	{
		this->adj.insert(make_pair(dest, cost));
		dest->rev.insert(this);
	}
}

template <class T>
bool Graph<T>::Vertex::removeEdge(Graph<T>::Vertex *dest, int cost)
{
	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = adj.find(make_pair(dest, cost));
	
	if(pos == adj.end())
	{
		return false;
	}
	
	this->adj.erase(pos); // This is done so that only one copy of the edge is deleted
	dest->rev.erase(dest->rev.find(this));
	
	return true;
}

template <class T>
bool Graph<T>::Vertex::removeEdge(Graph<T>::Vertex *dest)
{
	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = findVertex(dest);
	
	if(pos == adj.end())
	{
		return false;
	}
	
	this->adj.erase(pos); // This is done so that only one copy of the edge is deleted
	dest->rev.erase(dest->rev.find(this));
	
	return true;
}

template <class T>
void Graph<T>::Vertex::addEdgesInBatch(multiset<pair<Graph<T>::Vertex *, int> > new_adj)
{
	// adj.insert() is not used intentionally because, backword pointers are needed for deletion
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator v = new_adj.begin(); v != new_adj.end(); v++)
	{
		addEdge(v->first, v->second);
	}
}

template <class T>
bool Graph<T>::Vertex::edgeExists(Graph<T>::Vertex *dest, int cost)
{
	return adj.find(make_pair(dest, cost)) != adj.end();
}

template <class T>
unsigned int Graph<T>::Vertex::countEdge(Graph<T>::Vertex *dest, int cost)
{
	return adj.count(make_pair(dest, cost));
}

template <class T>
bool Graph<T>::Vertex::edgeExists(Graph<T>::Vertex *dest)
{
	return findVertex(dest) != adj.end();
}

template <class T>
unsigned int Graph<T>::Vertex::countEdge(Graph<T>::Vertex *dest)
{
	unsigned int count = 0;
	
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->first == dest)
		{
			count++;
		}
	}
		
	return count;
}

template <class T>
int Graph<T>::Vertex::edgeCost(Graph<T>::Vertex *dest)
{
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->first == dest)
		{
			return itr->second;
		}
	}
	
	return (int) INFINITY;
}

template <class T>
vector<int> Graph<T>::Vertex::edgeCosts(Graph<T>::Vertex *dest)
{
	vector<int> res;
	
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->first == dest)
		{
			res.push_back(itr->second);
		}
	}
	
	return res;
}

template <class T>
int Graph<T>::Vertex::indegree()
{
	return rev.size();
}

template <class T>
int Graph<T>::Vertex::outdegree()
{
	return adj.size();
}

template <class T>
bool Graph<T>::Vertex::hasNegativeWeightedEdge()
{
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->second < 0)
		{
			return true;
		}
	}
	
	return false;
}

template <class T>
void Graph<T>::Vertex::changeAdjacent(Graph<T>::Vertex *dest)
{
	for(typename multiset<Graph<T>::Vertex *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		typename multiset<pair<Graph<T>::Vertex *, int> >::iterator fd = (*v)->findVertex(this);
		if(fd != (*v)->adj.end())
		{
			(*v)->addEdge(dest, fd->second);
			(*v)->removeEdge(fd->first, fd->second);
		}
	}
}

template <class T>
void Graph<T>::Vertex::removeFromReverse(Graph<T>::Vertex *dest)
{
	vector<typename multiset<Graph<T>::Vertex *>::iterator> vec;
	
	for(typename multiset<Graph<T>::Vertex *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		if(*v == dest)
		{
			vec.push_back(v);
		}
	}
	
	const int sz = vec.size();
	
	for(int i = 0; i < sz; i++)
	{
		rev.erase(vec[i]);
	} 
}

template <class T>
Graph<T>::Graph(bool directed) : directed(directed)
{
}

template <class T>
Graph<T>::Graph(const Graph<T> &g)
{
	this->operator=(g);
}

template <class T>
Graph<T>::~Graph()
{
	for(typename map<T, Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		delete v->second;
	}
	
	vertices.clear();
}

template <class T>
void Graph<T>::operator=(const Graph<T> &g)
{
	directed = g.directed;

	map<T, Vertex *> tmp_vertices = g.vertices;
	
	for(typename map<T, Vertex *>::iterator v = tmp_vertices.begin(); v != tmp_vertices.end(); v++)
	{
		addVertex(v->first);
	}
	
	for(typename map<T, Vertex *>::iterator v = tmp_vertices.begin(); v != tmp_vertices.end(); v++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = v->second->getAdjacentNodes();
		
		for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			// Graph<T>::addEdge() is intentionally not called, because it might cause problems in case of undirected graph
			findVertex(v->first)->addEdge(findVertex(a->first->getLabel()), a->second);
		}
	}
}

template <class T>
typename Graph<T>::Vertex * Graph<T>::findVertex(T label)
{
	if(vertices.find(label) == vertices.end())
	{
		return NULL;
	}
	
	return vertices[label];
}

template <class T>
int Graph<T>::indegree(T label)
{
	if(findVertex(label) == NULL)
	{
		return -1;
	}
	
	return vertices[label]->indegree();
}

template <class T>
int Graph<T>::outdegree(T label)
{
	if(findVertex(label) == NULL)
	{
		return -1;
	}
	
	return vertices[label]->outdegree();
}

template <class T>
unsigned int Graph<T>::numVertices()
{
	return vertices.size();
}

template <class T>
unsigned int Graph<T>::numEdges()
{
	unsigned int cnt = 0;
	
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		cnt += itr->second->outdegree();
	}
	
	return directed? cnt: (cnt >> 1);
}

template <class T>
vector<typename Graph<T>::Vertex *> Graph<T>::findVerticesWithIndegreeZero()
{
	vector<typename Graph<T>::Vertex *> res;
	
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if(itr->second->indegree() == 0)
		{
			res.push_back(itr->second);
		}
	}
	
	return res;
}

template <class T>
bool Graph<T>::addVertex(T label)
{
	// Node with same name already exists
	if(findVertex(label) != NULL)
	{
		return false;
	}
	
	Vertex *new_node = new Vertex(label);
	
	// Memory full
	if(new_node == NULL)
	{
		return false;
	}
	
	vertices[label] = new_node;
	return true;
}

template <class T>
bool Graph<T>::removeVertex(T label)
{
	Vertex* node = findVertex(label);
	
	// Label does not exist
	if(node == NULL)
	{
		return false;
	}

	delete node;
	vertices.erase(label);
	
	return true;
}

template <class T>
bool Graph<T>::addEdge(T head, T tail, int cost)
{	
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return false;
	}
	
	hd->addEdge(tl, cost);
	
	if(!directed)
	{
		if(hd != tl)		// To avoid adding self loops twice
		{
			tl->addEdge(hd, cost);
		}
	}
	
	return true;
}

template <class T>
bool Graph<T>::removeEdge(T head, T tail, int cost)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return false;
	}
	
	bool forward = true, backword = true;
	
	forward = hd->removeEdge(tl, cost);
	
	if(!directed)
	{
		if(hd != tl)		// To avoid removing self loops twice
		{
			backword = tl->removeEdge(hd, cost);
		}
	}
	
	return (forward && backword);
}

template <class T>
bool Graph<T>::edgeExists(T head, T tail, int cost)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return false;
	}
	
	return hd->edgeExists(tl, cost);
}

template <class T>
bool Graph<T>::edgeExists(T head, T tail)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return false;
	}
	
	return hd->edgeExists(tl);
}

template <class T>
vector<int> Graph<T>::edgeCosts(T head, T tail)
{
	vector<int> empty;
	
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return empty;
	}
	
	return hd->edgeCosts(tl);
}

template <class T>
int Graph<T>::countEdge(T head, T tail, int cost)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return -1;
	}
	
	return hd->countEdge(tl, cost);
}

template <class T>
int Graph<T>::countEdge(T head, T tail)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == NULL) || (tl == NULL))
	{
		return -1;
	}
	
	return hd->countEdge(tl);
}

template <class T>
bool Graph<T>::pathExists(T start, T end)
{
	Vertex *st = findVertex(start);
	Vertex *ed = findVertex(end);
	
	if((st == NULL) || (ed == NULL))
	{
		return false;
	}
	
	// Create and initialize table
	map<T, bool> visited;
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}
	
	stack<Vertex *> stk;
	
	stk.push(st);
	
	while(!stk.empty())
	{
		Vertex *vtx = stk.top();
		stk.pop();
		
		if(vtx->getLabel() == end)
		{
			return true;
		}
		
		if(!visited[vtx->getLabel()])
		{
			visited[vtx->getLabel()] = true;
	
			multiset<pair<Graph<T>::Vertex *, int> > adj = vtx->getAdjacentNodes();
			for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				stk.push(a->first);
			}
		}
	}
	
	return false;
}

template <class T>
void Graph<T>::removeSelfLoops()
{
	for(typename map<T, Graph<T>::Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		while(edgeExists(v->second->getLabel(), v->second->getLabel()))
		{
			v->second->removeEdge(v->second);
		}
	}
}

template <class T>
vector<T> Graph<T>::topologicalSort()
{
	if(!directed)
	{
		throw "Not a directed graph";
	}
	
	vector<Vertex *> l = findVerticesWithIndegreeZero();
	unsigned int k = 0;
	
	if(l.size() == 0)
	{
		throw "Not an acyclic graph";
	}	
	
	queue<Vertex *> q;
	vector<T> res;
	const unsigned int sz = vertices.size();
	
	// Create and initialize table
	map<T, unsigned int> indegree_table;
	for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		indegree_table[itr->first] = itr->second->indegree();
	}
	
	q.push(l[k++]);
	
	while(res.size() < sz)
	{
		if(q.empty())
		{
			if(k >= l.size())
			{
				throw "Not an acyclic graph";
			}
			
			q.push(l[k++]);
		}
		
		Vertex *ft = q.front();
		q.pop();
		
		res.push_back(ft->getLabel());
		
		multiset<pair<Graph<T>::Vertex *, int> > adj = ft->getAdjacentNodes();
		for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			indegree_table[a->first->getLabel()]--;
			
			if(indegree_table[a->first->getLabel()] == 0)
			{
				q.push(a->first);
			}
		}
	}
	
	return res;
}

template <class T>
vector<T> Graph<T>::dfs()
{
	vector<T> v;
	
	if(vertices.size() == 0)
	{
		return v;
	}
	
	return dfs(vertices.begin()->first);
}

template <class T>
vector<T> Graph<T>::dfs(T start)
{
	vector<T> res;
	Vertex *vtx = findVertex(start);

	if(vtx == NULL)
	{
		return res;
	}	
	
	// Create and initialize table
	map<T, bool> visited;
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}
	
	stack<Vertex *> stk;
	
	stk.push(vtx);
	
	while(!stk.empty())
	{
		vtx = stk.top();
		stk.pop();
		
		if(!visited[vtx->getLabel()])
		{
			res.push_back(vtx->getLabel());
			visited[vtx->getLabel()] = true;
	
			multiset<pair<Graph<T>::Vertex *, int> > adj = vtx->getAdjacentNodes();
			for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				stk.push(a->first);
			}
		}
	}
	
	return res;
}
		
template <class T>
vector<T> Graph<T>::bfs()
{
	vector<T> v;
	
	if(vertices.size() == 0)
	{
		return v;
	}
	
	return bfs(vertices.begin()->first);
}

template <class T>
vector<T> Graph<T>::bfs(T start)
{
	vector<T> res;
	Vertex *vtx = findVertex(start);

	if(vtx == NULL)
	{
		return res;
	}	
	
	// Create and initialize table
	map<T, bool> visited;
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}
	
	queue<Vertex *> q;
	
	q.push(vtx);
	
	while(!q.empty())
	{
		vtx = q.front();
		q.pop();
		
		if(!visited[vtx->getLabel()])
		{
			res.push_back(vtx->getLabel());
			visited[vtx->getLabel()] = true;
	
			multiset<pair<Graph<T>::Vertex *, int> > adj = vtx->getAdjacentNodes();
			for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				q.push(a->first);
			}
		}
	}
	
	return res;
}

template <class T>
map<T, unsigned int> Graph<T>::hop_distance(T from)
{
	map<T, unsigned int> res;
	Vertex *vtx = findVertex(from);

	if(vtx == NULL)
	{
		return res;
	}	
	
	// Create and initialize table
	map<T, bool> visited;
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}
	
	queue<pair<Vertex *, unsigned int> > q;
	
	q.push(make_pair(vtx, 0));
	
	while(!q.empty())
	{
		pair<Vertex *, unsigned int> pr = q.front();
		q.pop();
		
		if(!visited[pr.first->getLabel()])
		{
			res[pr.first->getLabel()] = pr.second;
			visited[pr.first->getLabel()] = true;
	
			multiset<pair<Graph<T>::Vertex *, int> > adj = pr.first->getAdjacentNodes();
			for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				q.push(make_pair(a->first, pr.second + 1));
			}
		}
	}
	
	return res;
}

template <class T>
map<T, int> Graph<T>::assignVertexNumbers()
{
	map<T, int> res;
	
	int cnt = 0;
	
	for(typename map<T, Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		res[itr->first] = ++cnt;
	}
	
	return res;
}

template <class T>
pair<vector<T>, vector<vector<int> > > Graph<T>::adjacencyList()
{
	vector<T> v;
	vector<vector<int> > res;
	
	if(isSimple())
	{
		for(typename map<T, Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			v.push_back(itr->first);
		}
	
		for(typename vector<T>::iterator i = v.begin(); i != v.end(); i++)
		{
			vector<int> l;
		
			for(typename vector<T>::iterator j = v.begin(); j != v.end(); j++)
			{
				if(*i == *j)
				{
					l.push_back(0);
				}
				else
				{
					l.push_back(findVertex(*i)->edgeCost(findVertex(*j)));
				}
			}
		
			res.push_back(l);
		}
	}
		
	return make_pair(v, res);
}

template <class T>
pair<vector<T>, vector<vector<bool> > > Graph<T>::connectivityList()
{
	vector<T> v;
	vector<vector<bool> > res;
	
	for(typename map<T, Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		v.push_back(itr->first);
	}

	for(typename vector<T>::iterator i = v.begin(); i != v.end(); i++)
	{
		vector<bool> l;

		for(typename vector<T>::iterator j = v.begin(); j != v.end(); j++)
		{
			if(*i == *j)
			{
				l.push_back(true);
			}
			else
			{
				l.push_back(findVertex(*i)->edgeExists(findVertex(*j)));
			}
		}
	
		res.push_back(l);
	}

	return make_pair(v, res);
}

template <class T>
bool Graph<T>::isDirected()
{
	return directed;
}

template <class T>
bool Graph<T>::isWeighted()
{
	for(typename map<T, Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = itr->second->getAdjacentNodes();
		for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			if(a->second != 1)
			{	
				return true;
			}
		}
	}
	
	return false;
}

template <class T>
bool Graph<T>::isConnected()
{
	if(numVertices() == 0)
	{
		return true;
	}
	
	if(directed)
	{
		pair<vector<T>, vector<vector<bool> > > pr = connectivityList();
		vector<vector<bool> > curr_matrix = pr.second;
		vector<vector<bool> > prev_matrix;
		const unsigned int n = numVertices();
		
		for(int k = 0; k < n; k++)
		{
			prev_matrix = curr_matrix;
			
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
				{
					curr_matrix[i][j] = prev_matrix[i][j] || (prev_matrix[i][k] && prev_matrix[k][j]);
				}
			}
		}
		
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(!curr_matrix[i][j])
				{
					return false;
				}
			}
		}
		
		return true;
	}
		
	// Undirected graph
	Vertex *vtx = vertices.begin()->second;

	// Create and initialize table
	map<T, bool> visited;
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}
	
	stack<Vertex *> stk;
	
	stk.push(vtx);
	
	while(!stk.empty())
	{
		vtx = stk.top();
		stk.pop();
		
		if(!visited[vtx->getLabel()])
		{
			visited[vtx->getLabel()] = true;
	
			multiset<pair<Graph<T>::Vertex *, int> > adj = vtx->getAdjacentNodes();
			for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				stk.push(a->first);
			}
		}
	}
	
	for(typename map<T, bool>::iterator itr = visited.begin(); itr != visited.end(); itr++)
	{
		if(!itr->second)
		{
			return false;
		}
	}
	
	return true;
}

template <class T>
bool Graph<T>::isAcyclic()
{
	if(numVertices() == 0)
	{
		return true;
	}
	
	if(directed)
	{
		vector<Vertex *> l = findVerticesWithIndegreeZero();
		unsigned int k = 0;
		unsigned int cnt = 0;
			
		// Cycle exists
		if(l.size() == 0)
		{
			return false;
		}	
	
		queue<Vertex *> q;
		const unsigned int sz = vertices.size();
	
		// Create and initialize table
		map<T, int> indegree_table;
		for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			indegree_table[itr->first] = itr->second->indegree();
		}
	
		q.push(l[k++]);
	
		while(cnt < sz)
		{
			if(q.empty())
			{
				if(k >= l.size())
				{
					return false;
				}
				
				q.push(l[k++]);
			}
		
			Vertex *ft = q.front();
			q.pop();

			cnt++;		
		
			indegree_table[ft->getLabel()]--; // This is done to denote that the vertex is already processed
			
			multiset<pair<Graph<T>::Vertex *, int> > adj = ft->getAdjacentNodes();
			for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				indegree_table[a->first->getLabel()]--;
			
				if(indegree_table[a->first->getLabel()] == 0)
				{
					q.push(a->first);
				}
			}
		}
	
		return true;
	}
	
	// Undirected graph
	
	if(numEdges() > numVertices() - 1)
	{
		return false;
	}
	
	Graph<T> g = *this;
	map<T, int> m = g.assignVertexNumbers();
	DisjointSet s(g.vertices.size());
	
	for(typename map<T, Graph<T>::Vertex *>::iterator itr = g.vertices.begin(); itr != g.vertices.end(); itr++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = itr->second->getAdjacentNodes();
		
		for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator it = adj.begin(); it != adj.end(); it++)
		{
			if(s.connected(m[itr->second->getLabel()] - 1, m[it->first->getLabel()] - 1))
			{
				return false;
			}
			
			s.join(m[itr->second->getLabel()] - 1, m[it->first->getLabel()] - 1);
			itr->second->removeEdge(it->first);
			it->first->removeEdge(itr->second);
		}
	}
	
	return true;
}

template <class T>
bool Graph<T>::isSimple()
{
	for(typename map<T, Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if(itr->second->edgeExists(findVertex(itr->first)))
		{
			return false;
		}
		
		for(typename map<T, Graph<T>::Vertex *>::iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			if(itr->second->countEdge(findVertex(it->first)) > 1)
			{
				return false;
			}
		}
	}
	
	return true;
}

template <class T>
bool Graph<T>::hasNegativeWeightedEdge()
{
	for(typename map<T, Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if(itr->second->hasNegativeWeightedEdge())
		{
			return true;
		}
	}
	
	return false;
}

template <class T>
map<T, pair<T, int> > Graph<T>::bfsShortestPath(T source)
{
	map<T, pair<T, int> > res;
	
	if(!isDirected() && !isWeighted())
	{
		Vertex *vtx = findVertex(source);

		if(vtx != NULL)
		{
			// Create and initialize table
			map<T, bool> visited;
			for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				visited[itr->first] = false;
			}
	
			queue<pair<Vertex *, pair<T, int> > > q;
	
			q.push(make_pair(vtx, make_pair(source, 0)));
	
			while(!q.empty())
			{
				pair<Vertex *, pair<T, int> > pr = q.front();
				q.pop();
		
				if(!visited[pr.first->getLabel()])
				{
					res[pr.first->getLabel()] = pr.second;
					visited[pr.first->getLabel()] = true;
	
					multiset<pair<Graph<T>::Vertex *, int> > adj = pr.first->getAdjacentNodes();
					for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
					{
						q.push(make_pair(a->first, make_pair(pr.first->getLabel(), pr.second.second + 1)));
					}
				}
			}
			
			for(typename map<T, bool>::iterator itr = visited.begin(); itr != visited.end(); itr++)
			{
				if(!itr->second)
				{
					res[itr->first] = make_pair(itr->first, INFINITY);
				}
			}
		}	
	}
	
	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::topologicalShortestPath(T source)
{
	map<T, pair<T, int> > res;
	
	if(isDirected() && isAcyclic())
	{
		if(findVertex(source) != NULL)
		{
			vector<T> ord = topologicalSort();
			const unsigned int sz = ord.size();
			int pos = -1;
			
			assert(sz == numVertices());
			
			for(int i = 0; i < sz; i++)
			{
				if(ord[i] == source)
				{
					pos = i;
					break;
				}
			}
			
			assert(pos != -1);
			
			for(int i = 0; i < sz; i++)
			{
				res[ord[i]] = make_pair(ord[i], (int) INFINITY);
			}
			
			res[ord[pos]] = make_pair(ord[pos], 0);
			
			for(int i = pos; i < sz; i++)
			{
				Vertex *cur = findVertex(ord[i]);
				
				assert(cur != NULL);
				
				multiset<pair<Graph<T>::Vertex *, int> > adj = cur->getAdjacentNodes();
				for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
				{
					// First condition is checked to avoid overflow
					if((res[ord[i]].second != (int) INFINITY) && (res[ord[i]].second + a->second < res[a->first->getLabel()].second))
					{
						res[a->first->getLabel()] = make_pair(ord[i], res[ord[i]].second + a->second);
					}
				}
			}
		}
	}
	
	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::dijkstraShortestPath(T source)
{
	map<T, pair<T, int> > res;
	
	if(!hasNegativeWeightedEdge())
	{
		if(findVertex(source) != NULL)
		{
			map<T, bool> visited;
			
			for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				res[itr->first] = make_pair(itr->first, (int) INFINITY);
				visited[itr->first] = false;
			}
			
			res[source] = make_pair(source, 0);

			while(1)
			{
				int min_dist = INFINITY;
				T curr;
				
				for(typename map<T, pair<T, int> >::iterator itr = res.begin(); itr != res.end(); itr++)
				{
					if(!visited[itr->first] && (itr->second.second < min_dist))
					{
						min_dist = itr->second.second;
						curr = itr->first;
					}
				}
				
				if(min_dist == (int) INFINITY)
				{
					break;
				}
				
				visited[curr] = true;
				
				multiset<pair<Vertex *, int> > adj = findVertex(curr)->getAdjacentNodes();
				for(typename multiset<pair<Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
				{
					if(res[curr].second + a->second < res[a->first->getLabel()].second)
					{
						res[a->first->getLabel()] = make_pair(curr, res[curr].second + a->second);
					}
				}
			}
		}
	}
	
	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::bellmanFordShortestPath(T source)
{
	map<T, pair<T, int> > emp, res;
	int iter = numVertices() - 1;
	
	for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		res[itr->first] = make_pair(itr->first, (int) INFINITY);
	}
	
	res[source] = make_pair(source, 0);
	
	while(iter--)
	{
		for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
			for(typename multiset<pair<Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				// First condition is checked to avoid overflow
				if((res[itr->first].second != (int) INFINITY) && (res[itr->first].second + a->second < res[a->first->getLabel()].second))
				{
					res[a->first->getLabel()] = make_pair(itr->first, res[itr->first].second + a->second);
				}
			}
		}
	}	
	
	for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
		for(typename multiset<pair<Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			// First condition is checked to avoid overflow
			if((res[itr->first].second != (int) INFINITY) && (res[itr->first].second + a->second < res[a->first->getLabel()].second))
			{
				// Graph contains negative cycle(s)
				return emp;
			}
		}
	}
	
	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::shortestPath(T source)
{
	map<T, pair<T, int> > res;
	
	// Invalid source vertex
	if(findVertex(source) == NULL)
	{
		return res;
	}
	
	res = bfsShortestPath(source);
	
	if(res.size() != 0)
	{
		return res;
	}
	
	res = topologicalShortestPath(source);
	
	if(res.size() != 0)
	{
		return res;
	}
	
	res = dijkstraShortestPath(source);
	
	if(res.size() != 0)
	{
		return res;
	}
	
	// If the graph has negative cycles, it will be handled by Bellman-Ford algorithm
	return bellmanFordShortestPath(source);
}

template <class T>
pair<vector<T>, vector<vector<pair<T, int> > > > Graph<T>::shortestPath()
{
	if(isSimple())
	{
		pair<vector<T>, vector<vector<int> > > pr = adjacencyList();
		vector<vector<int> > curr_matrix = pr.second;
		vector<vector<int> > prev_matrix;
		vector<vector<pair<T, int> > > path;
		const unsigned int n = numVertices();
	
		for(int i = 0; i < n; i++)
		{
			vector<pair<T, int> > tmp;
			
			for(int j = 0; j < n; j++)
			{
				tmp.push_back(make_pair(pr.first[j], (int) INFINITY));
			}
			
			path.push_back(tmp);
		}
		
		for(int k = 0; k < n; k++)
		{
			prev_matrix = curr_matrix;
		
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
				{
					// First two conditions are to avoid overflow
					if((prev_matrix[i][k] == (int) INFINITY) || (prev_matrix[k][j] == (int) INFINITY) || (prev_matrix[i][j] <= prev_matrix[i][k] + prev_matrix[k][j]))
					{
						curr_matrix[i][j] = prev_matrix[i][j];
						path[i][j] = make_pair(path[i][j].first, curr_matrix[i][j]);
					}
					else
					{
						curr_matrix[i][j] = prev_matrix[i][k] + prev_matrix[k][j];
						path[i][j] = make_pair(pr.first[k], curr_matrix[i][j]);
					}
				}
			}
		}
	
		return make_pair(pr.first, path);
	}
	
	return make_pair(vector<T>(), vector<vector<pair<T, int> > >());
}

template <class T>
void Graph<T>::printPath(ostream &out, map<T, pair<T, int> > path)
{
	for(typename map<T, pair<T, int> >::iterator itr = path.begin(); itr != path.end(); itr++)
	{
		out << itr->first << " =====> ";
		
		if(itr->second.second == (int) INFINITY)
		{
			out << "(Unreachable)" << endl;
		}
		else
		{
			stack<T> stk;
			
			T curr = itr->first;
			T prev;
			
			do
			{
				prev = curr;
				stk.push(curr);
				curr = path[curr].first;
			}while(prev != curr);
			
			while(!stk.empty())
			{
				out << stk.top() << ", ";
				stk.pop();
			}
			
			out << "\b\b (" << itr->second.second << ")" << endl; 
		}
	}
}

template <class T>
void Graph<T>::printPath(ostream &out, pair<vector<T>, vector<vector<pair<T, int> > > > dist)
{
	const int n = numVertices();
	
	assert(dist.first.size() == n);
	
	out << "Path: " << endl;
		
	for(int i = 0; i < n; i++)
	{
		out << "\t" << i+1;
	}
	
	out << endl;

	for(int i = 0; i < n; i++)
	{
		out << "____________";
	}
	
	out << endl;
	
	for(int i = 0; i < n; i++)
	{
		out << dist.first[i] << "(" << i+1 << ") | ";
		
		for(int j = 0; j < n; j++)
		{
			if(dist.second[i][j].second == (int) INFINITY)
			{
				out << "\t---";
			}
			else
			{
				out << "\t" << dist.second[i][j].first;
			}
		}
		
		out << endl;
	}
	
	out << "Distance: " << endl;
	
	for(int i = 0; i < n; i++)
	{
		out << "\t" << i+1;
	}
	
	out << endl;
	
	for(int i = 0; i < n; i++)
	{
		out << "____________";
	}
	
	out << endl;
	
	for(int i = 0; i < n; i++)
	{
		out << dist.first[i] << "(" << i+1 << ") | ";
		
		for(int j = 0; j < n; j++)
		{
			if(dist.second[i][j].second == (int) INFINITY)
			{
				out << "\tinf";
			}
			else
			{
				out << "\t" << dist.second[i][j].second;
			}
		}
		
		out << endl;
	}
}

template <class T>		
vector<T> Graph<T>::getVertices()
{
	vector<T> res;
	
	for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		res.push_back(itr->first);
	}
	
	return res;
}

template <class T>
vector<pair<T, pair<T, int> > > Graph<T>::getEdges()
{
	vector<pair<T, pair<T, int> > > res;
	
	for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
		
		for(typename multiset<pair<Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			res.push_back(make_pair(itr->first, make_pair(a->first->getLabel(), a->second)));
		}
	}
		
	return res;
}

template <class T>
vector<vector<T> > Graph<T>::getVerticesComponentwise()
{
	vector<vector<T> > res;
	map<T, bool> visited;
	
	if(isDirected())
	{
		return res;
	}
	
	for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}
	
	while(1)
	{
		T source;
		bool unvisited = false;
		
		for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			if(!visited[itr->first])
			{
				source = itr->first;
				unvisited = true;
				break;
			}
		}
		
		if(!unvisited)
		{
			break;
		}
		
		vector<T> vlist = dfs(source);
		
		const int sz = vlist.size();
		for(int i = 0; i < sz; i++)
		{
			visited[vlist[i]] = true;
		}
		
		res.push_back(vlist);
	}
	
	return res;
}

template <class T>
vector<Graph<T> > Graph<T>::getConnectedComponents()
{
	vector<Graph<T> > res;
	vector<vector<T> > vertices_compwise = getVerticesComponentwise();
	
	for(typename vector<vector<T> >::iterator i = vertices_compwise.begin(); i != vertices_compwise.end(); i++)
	{
		Graph<T> g(directed);
		
		for(typename vector<T>::iterator j = i->begin(); j != i->end(); j++)
		{
			g.addVertex(*j);
		}
		
		for(typename vector<T>::iterator j = i->begin(); j != i->end(); j++)
		{
			multiset<pair<Vertex *, int> > adj = findVertex(*j)->getAdjacentNodes();
			
			for(typename multiset<pair<Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
			{
				g.findVertex(*j)->addEdge(g.findVertex(a->first->getLabel()), a->second);
			}
		}
		
		res.push_back(g);
	}
	
	return res;
}

template <class T>
Graph<T> Graph<T>::minimumSpanningTree()
{
	Graph<T> t(directed);
	
	if(!isDirected() && isConnected())
	{
		if(vertices.size() != 0)
		{
			map<T, bool> visited;
			
			for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				visited[itr->first] = false;
				t.addVertex(itr->first);
			}
			
			visited[vertices.begin()->first] = true;

			while(1)
			{
				int min_dist = (int) INFINITY;
				pair<T, T> curr;
				
				for(typename map<T, Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
				{
					if(visited[itr->first])
					{
						multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
						for(typename multiset<pair<Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
						{
							if(!visited[a->first->getLabel()] && a->second < min_dist)
							{
								min_dist = a->second;
								curr = make_pair(itr->first, a->first->getLabel());
							}
						}
					}
				}
				
				if(min_dist == (int) INFINITY)
				{
					break;
				}
				
				visited[curr.second] = true;
				t.addEdge(curr.first, curr.second, min_dist);
			}
		}
	}
	
	return t;
}

template <class T>
bool Graph<T>::mergeVertices(T first, T second, T new_label)
{
	Vertex * ft = findVertex(first);
	Vertex * sd = findVertex(second);
	Vertex * nw = findVertex(new_label);
	
	// One of the lables does not exist
	if((ft == NULL) || (sd == NULL))
	{
		return false;
	}
	
	// Cannot merge a vertex with itself
	if(ft == sd)
	{	
		return false;
	}
	
	// Node with same name already exists (and it does not match with one of the nodes being merged
	if((nw != NULL) && (ft != nw) && (sd != nw))
	{
		return false;
	}
	
	ft->setLabel(new_label);
	vertices.erase(first);
	vertices[new_label] = ft;
	
	ft->addEdgesInBatch(sd->getAdjacentNodes());

	sd->changeAdjacent(ft);
	
	delete sd;
	vertices.erase(second);

	ft->removeFromReverse(sd);
	
	return true;
}

template <class T>
T Graph<T>::pickRandomVertex()
{
	int rnd = rand() % vertices.size();
	typename map<T, Graph<T>::Vertex *>::const_iterator it(vertices.begin());
	advance(it, rnd);
	
	return it->first;
}

template <class T>
Edge<T> * Graph<T>::pickRandomEdge()
{
	Vertex *hd;
	multiset<pair<Graph<T>::Vertex *, int> > adj;
	int cnt = 0;
	const int double_num_vertices = 4 * vertices.size();
	
	do
	{
		hd = findVertex(pickRandomVertex());
		adj = hd->getAdjacentNodes();
		cnt ++;
	} while((adj.size() == 0) && (cnt < double_num_vertices));

	// Adjacency list empty
	if(adj.size() == 0)
	{
		return NULL;
	}
		
	int rnd = rand() % adj.size();
	typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator it(adj.begin());
	advance(it, rnd);
	
	Vertex *tl = it->first;
	
	return new Edge<T>(hd->getLabel(), tl->getLabel(), it->second);
}

template <class T>
int Graph<T>::minCut()
{
	if(directed)
	{
		return -1;
	}
	
	int rep = 2000;
	int min = vertices.size() + 2;
	
	for(int i = 0; i < rep; i++)
	{
		Graph<T> g = *this;
		
		srand(i);

		g.removeSelfLoops();

		while(g.vertices.size() > 2)
		{		
			Edge<T> * rn = g.pickRandomEdge();
			
			if(rn == NULL)
			{
				break;
			}
			
			g.mergeVertices(rn->src, rn->dest, rn->src);
			g.removeSelfLoops();
		}

		if(g.vertices.size() == 2)
		{
			int loc_min = g.vertices.begin()->second->getAdjacentNodes().size();
			
			if(loc_min < min)
			{
				min = loc_min;
			}
		}	
	}
	
	return min;
}

#endif
