/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}


/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if (this->findVertex(in) == NULL)
	{
		vertexSet.push_back(new Vertex<T>(in));
		return true;
	}
	else
		return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	

	Vertex<T>* s = findVertex(sourc);
	Vertex<T>* d = findVertex(dest);
	if (d == NULL || s == NULL)
	{
		return false;
	}
	
	s->addEdge(d, w);
	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(*(new Edge<T>(d, w)));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	Vertex<T>* s = findVertex(sourc);
	Vertex<T>* d = findVertex(dest);
	if (d == NULL || s == NULL)
	{
		return false;
	}
	return s->removeEdgeTo(d);
	
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	for (vector<Edge<T>>::iterator it = adj.begin(); it != adj.end(); it++)
	{
		if (it->dest == d)
		{
			adj.erase(it);
			return true;
		}
	}
	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	// TODO (10 lines)
	// HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
	// HINT: take advantage of "removeEdgeTo" to remove incoming edges.

	Vertex<T>* v = findVertex(in);
	if(v == NULL)
		return false;
	vector<Vertex<T> *>::iterator obj;
	for (vector<Vertex<T> *>::iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		if (*it == v)
		{
			obj = it;
		}
		else
		{
			(*it)->removeEdgeTo(v);
		}
	}
	vertexSet.erase(obj);
	return true;
	
	
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	// TODO (7 lines)
	vector<T> res;
	for (vector<Vertex<T>*>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		(*it)->visited = false;
	}
	for (vector<Vertex<T>*>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		if ((*it)->visited == false)
		{
			dfsVisit(*it, res);
		}
	}
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (vector<Edge<T>>::iterator it = v->adj.begin(); it!= v->adj.end(); it++)
	{
		if ((*it).dest->visited == false)
			dfsVisit((*it).dest, res);

	}
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
	queue<Vertex <T>*> q;
	Vertex<T>* src = findVertex(source);

	if (src == NULL)
		return res;

	for (vector<Vertex<T>*>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		(*it)->visited = false;
	}
	q.push(src);
	src->visited = true;

	while (!q.empty())
	{
		Vertex<T>* v = q.front();
		res.push_back(v->info);
		q.pop();
		for (int i = 0; i < v->adj.size(); i++)
		{
			if (v->adj.at(i).dest->visited == false)
			{
				q.push((v->adj.at(i).dest));
				v->adj.at(i).dest->visited = true;
			}
		}
	}
	
	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;
	for (vector<Vertex<T>*>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		(*it)->indegree = 0;
	}
	for (vector<Vertex<T>*>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		for (int i = 0; i < (*it)->adj.size(); i++)
		{
			(*it)->adj.at(i).dest->indegree++;
		}
	}
	queue<Vertex<T>*> q;
	for (vector<Vertex<T>*>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
	{
		if ((*it)->indegree == 0)
		{
			q.push(*it);
		}
	}
	while (!q.empty())
	{
		Vertex<T>* v = q.front();
		q.pop();
		res.push_back(v->info);
		for (int i = 0; i < v->adj.size(); i++)
		{
			v->adj.at(i).dest->indegree--;
			if(v->adj.at(i).dest->indegree == 0)
			{
				q.push(v->adj.at(i).dest);
			}
		}
		
	}

	if (res.size() != vertexSet.size())
	{
		vector<T> res_empty;
		return res_empty;
	}
	return res;
}



#endif /* GRAPH_H_ */
