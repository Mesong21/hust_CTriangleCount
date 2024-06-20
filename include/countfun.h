#ifndef COUNTFUN_H
#define COUNTFUN_H

#include "graph.h"

unsigned long count_triangles(Graph *graph, int tnum);
void edges_to_vertexes(Graph *graph, int tnum);
unsigned long add_vertexes(Graph *graph);
void process_edges(Graph *graph,
                   std::unordered_map<unsigned long, Edge *>::iterator start,
                   std::unordered_map<unsigned long, Edge *>::iterator end);

#endif