#include"graph.h"

void graph_init(Graph *graph);
void vertex_init(Vertex *vertex);
void edge_init(Edge *edge);
Graph *graph_from_dir(const char *dir, bool prnit_all);
void print_graph(Graph *graph);
void print_vertex(Vertex *vertex);
void print_edge(Edge *edge);

