#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>

#include <map>
#include <set>
#include <unordered_map>
#define MAX_VERTEX_NUM 10000000
#define MAX_EDGE_NUM 100000000

typedef struct Vertex {
  unsigned long id;                 // 顶点id
  unsigned long tri_num;            // 得到的三角形计数
  std::set<unsigned long> nbr_set;  // 所有邻居集合，储存邻居id

  bool operator<(const Vertex &other) const {
    // set操作
    return id < other.id;
  }

} Vertex;
// typedef std::map<unsigned long, Vertex> VertexList;
typedef std::unordered_map<unsigned long, Vertex *> VertexList;

typedef struct Edge {
  unsigned long id;  // 边id
  Vertex *src_v;
  Vertex *dst_v;
} Edge;
// typedef std::map<unsigned long, Edge> EdgeList;
typedef std::unordered_map<unsigned long, Edge *> EdgeList;

typedef struct Graph {
  unsigned long vertex_num;  // 顶点数
  unsigned long edge_num;    // 无向边数
	unsigned long directed_edge_num; // 有向边数
  VertexList vertex_list;    // 顶点列表
  EdgeList edge_list;        // 边列表
} Graph;

#endif