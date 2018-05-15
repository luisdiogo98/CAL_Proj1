/*
* Graph.h
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <float.h>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF DBL_MAX

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;
	vector<Edge<T> *> incoming;
	bool visited;
	double dist = 0;
	Vertex<T> *path = NULL;
	vector<T> fullpath;
	double filling = 0; 
	int queueIndex = 0;

	bool processing = false;
	Edge<T> * addEdge(Vertex<T> *dest, double w, string n);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const;
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
	friend class Company;
};


template <class T>
Vertex<T>::Vertex(T in) : info(in) {}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *d, double w, string n) {
	Edge<T> * e = new Edge<T>(this, d, w, n);
	this->outgoing.push_back(e);
	d->incoming.push_back(e);
	return e;
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
	string name;		   // edge name
public:
	Edge(Vertex<T> *o, Vertex<T> *d, double w, string n);
	void setName(string n);
	friend class Graph<T>;
	friend class Vertex<T>;
	friend class Company;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, string n) : orig(o), dest(d), weight(w), name(n) {}

template <class T>
void Edge<T>::setName(string n) { name = n; }


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double w, string n);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	vector<T> dfs() const;
	void dijkstraShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;
	Vertex<T> * initSingleSource(const T &origin);
	Vertex<T> * initSingleSourceNegative(const T &origin);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	void dfsVisit(Vertex<T> *v, vector<T> & res) const;
	friend class Company;
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> *Graph<T>::addEdge(const T &sourc, const T &dest, double w, string n) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, w, n);
}

template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
	    if (! v->visited)
	    	dfsVisit(v, res);
	return res;
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto e : v->outgoing) {
		auto w = e->dest;
	    if ( ! w->visited)
	    	dfsVisit(w, res);
	}
}

template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

template<class T>
Vertex<T> * Graph<T>::initSingleSourceNegative(const T &origin) {
	for (auto v : vertexSet) 
	{
		v->dist = INF;
		v->fullpath.clear();
		v->filling = 0;
	}
	auto s = findVertex(origin);
	s->dist = INF/2;
	return s;
}

template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while (!q.empty()) {
		auto v = q.extractMin();
		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF)
		return res;
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}


#endif /* GRAPH_H_ */
