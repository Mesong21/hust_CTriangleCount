#include"graph.h"

void graph_init(Graph *graph);
void vertex_init(Vertex *vertex);
void edge_init(Edge *edge);
Graph *graph_from_dir(const char *dir, bool prnit_all);
void add_vertexes_to_graph(unsigned long id1, unsigned long id2, Edge *e, Graph *g);
void add_vertex_to_graph(unsigned long id, Graph *g);
bool find_edge(unsigned long id1, unsigned long id2, Graph *g);
void print_graph(Graph *graph, bool print_all);
void print_vertex(Vertex *vertex);
void print_edge(Edge *edge);

