#include "Graph.hpp"
#include <queue>

template <typename LabelType>
Graph<LabelType>::Graph() {}

template <typename LabelType> 
int Graph<LabelType>::getNumVertices() const {
    return adjList.size();
}

template <typename LabelType> 
int Graph<LabelType>::getNumEdges() const {
    return edgeCount;
}
        
template <typename LabelType> 
bool Graph<LabelType>::add(LabelType start, LabelType end) { 
    //check if lenght is 0
    if (start == end) return false;

    //if edge already exists -> reject
    if (adjList[start].count(end)) return false;

    //add edge both ways (undirected)
    adjList[start].insert(end);
    adjList[end].insert(start);

    //incremetn count
    edgeCount++;
    return true;

}   

template <typename LabelType> 
bool Graph<LabelType>::remove(LabelType start, LabelType end) {
    //checking validity
    if (!adjList.count(start) || !adjList[start].count(end))
    return false;

    //remove both directions
    adjList[start].erase(end);
    adjList[end].erase(start);

    edgeCount--;

    //remove isolated vertices
    if (adjList[start].empty())
        adjList.erase(start);

    if (adjList[end].empty())
        adjList.erase(end);

    return true;
}

template <typename LabelType>
void Graph<LabelType>::dfsHelper(LabelType current,
                                 std::set<LabelType>& visited,
                                 void visit(LabelType&)) {

    visited.insert(current);
    visit(current);

    for (const auto& neighbor : adjList[current]) {
        if (!visited.count(neighbor)) {
            dfsHelper(neighbor, visited, visit);
        }
    }
}

template <typename LabelType> 
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {

    if (!adjList.count(start)) {
        return;
    }

    std::set<LabelType> visited;
    dfsHelper(start, visited, visit);
}

template <typename LabelType> 
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS
    if (!adjList.count(start)) return;

    std::queue<LabelType> q;
    std::set<LabelType> visited;

    q.push(start);
    visited.insert(start);

    while(!q.empty()) {
        LabelType current = q.front();
        q.pop();

        visit(current);

        for (const auto& neighbor : adjList[current]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}