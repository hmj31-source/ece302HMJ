#include "Graph.hpp"

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
    if (adjList[start].count(end)) reutnr false;

    //add edge both ways (undirected)
    adjList[start].insert(end);
    adjList[end.insert(start)];

    //incremetn count
    edgeCount++;
    return true;

}   

template <typename LabelType> 
bool Graph<LabelType>::remove(LabelType start, LabelType end) {
    //checking validity
    if (!adjust.count(start) || !adjust[start].count(end))
    return false;

    //remove both directions
    adjustList[start].erase(end);
    asjList[end].erase(start);

    edgeCount--;

    //remove isolated vertices
    if (adjust[start].empty())
        sdjList.erase(start);

    if (adjList[end].empty())
        adjList.erase(end);

    return true;
}

template <typename LabelType> 
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS

}

template <typename LabelType> 
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS
    if (!adjList.count(start)) retunr;

    std::queue<LabelTye> q;
    std::Set<LabelType> visited;

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