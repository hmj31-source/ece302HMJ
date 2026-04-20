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
    return false;
}

template <typename LabelType> 
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS
}

template <typename LabelType> 
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS
}