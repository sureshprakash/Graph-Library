#ifndef _GRAPH_H
#define _GRAPH_H

#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

#define DEBUG

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
				
				int indegree();
				int outdegree();
	
				void changeAdjacent(Vertex *dest);
				void removeFromReverse(Vertex *dest);
		};

		map<T, Vertex *> vertices;
		bool directed;
		
		Vertex * findVertex(T label);
		
		Vertex * findFirstVertexWithIndegreeZero();
	
	public:
		Graph(bool directed);
		Graph(Graph<T> &g);
		~Graph();
		
		bool addVertex(T label);
		bool removeVertex(T label);
		
		bool addEdge(T head, T tail, int cost = 1);
		bool removeEdge(T head, T tail, int cost = 1);
		
		int countEdge(T head, T tail);
		int countEdge(T head, T tail, int cost);
		
		bool edgeExists(T head, T tail);
		bool edgeExists(T head, T tail, int cost);
		
		void operator=(Graph<T> &g);
		
		int indegree(T label);
		int outdegree(T label);
		
		void removeSelfLoops();
		
		bool mergeVertices(T first, T second, T new_label);
		
		T pickRandomVertex();
		Edge<T> * pickRandomEdge();
		
		int minCut();
		
		vector<T> topologicalSort();
		
		friend ostream &operator<<(ostream &out, Graph &g)
		{	
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
Graph<T>::Graph(Graph<T> &g)
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
void Graph<T>::operator=(Graph<T> &g)
{
	directed = g.directed;

	for(typename map<T, Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		vertices[v->first] = new Vertex(v->first);
	}
	
	for(typename map<T, Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = v->second->getAdjacentNodes();
		
		for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
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
typename Graph<T>::Vertex * Graph<T>::findFirstVertexWithIndegreeZero()
{
	for(typename map<T, typename Graph<T>::Vertex *>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if(itr->second->indegree() == 0)
		{
			return itr->second;
		}
	}
	
	return NULL;
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
	
	Vertex *ft = findFirstVertexWithIndegreeZero();
	
	if(ft == NULL)
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
	
	q.push(ft);
	
	while(res.size() < sz)
	{
		if(q.empty())
		{
			throw "Not an acyclic graph";
		}
		
		ft = q.front();
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
