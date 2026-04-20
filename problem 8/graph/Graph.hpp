#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <map>
#include <set>
#include "AbstractGraph.hpp"

template <typename LabelType>
class Graph: public AbstractGraph<LabelType>
{
    public:

        Graph();

        int getNumVertices() const;
        
        int getNumEdges() const;

        bool add(LabelType start, LabelType end);

        bool remove(LabelType start, LabelType end);

        void depthFirstTraversal(LabelType start, void visit(LabelType&));

        void breadthFirstTraversal(LabelType start, void visit(LabelType&));
  
    //added private section
    private:
        //map and set
        std::map<LabelType, std::set<LabelType>> adjList;
        //int for edged
        int edgeCount = 0;
};

#include "Graph.tpp"

#endif 
