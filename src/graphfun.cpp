#include "graphfun.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

/**
 * 初始化图
 */
void graph_init(Graph *graph) {
  graph->vertex_num = 0;
  graph->edge_num = 0;
	graph->directed_edge_num = 0;
}
void vertex_init(Vertex *vertex) {
  vertex->id = 0;
  vertex->tri_num = 0;
  vertex->nbr_set.clear();
}

void edge_init(Edge *edge) {
  edge->id = 0;
  edge->src_v = nullptr;
  edge->dst_v = nullptr;
}

/**
 * 从目录中构建图
 */
Graph *graph_from_dir(const char *dir, bool print_all, int tnum) {
  Graph *g = new Graph();
  graph_init(g);
  for (const auto &entry : fs::directory_iterator(dir)) {
    std::ifstream file(entry.path());
    std::string line;

    while (std::getline(file, line)) {
      std::istringstream iss(line);
      if (line[0] == '#') continue;
      unsigned long id1, id2;
      if (!(iss >> id1 >> id2)) {
        // 解析错误
        std::cout << id1 << id2;
        throw std::runtime_error("解析错误1\n");
      }
			g->directed_edge_num++; // 包括自边，重复边等，只要检测到边就加入
			
      if (id1 == id2) {
        // 自环,忽略该边
        add_vertex_to_graph(id1, g);
        continue;
      } else if (id1 > id2) {
        // printf("id1: %lu id2: %lu\n", id1, id2);
        unsigned long tmp = id1;
        id1 = id2;
        id2 = tmp;
      }
      // 确保id1 < id2
      if (find_edge(id1, id2, g)) {
        // 重复边,说明该边和两个顶点都已加入表中
        continue;
      }
      // 加入边表
      Edge *e = new Edge();
      edge_init(e);
      g->edge_num++;
      e->id = g->edge_num;  // 从1开始
      g->edge_list[g->edge_num] = e;
      add_vertexes_to_graph(id1, id2, e, g);  // 加入顶点表
    }
  }
  // printf("图构建完成\n");
  return g;
}

/**
 * 添加两个顶点
 */
void add_vertexes_to_graph(unsigned long id1, unsigned long id2, Edge *e,
                           Graph *g) {
  if (g->vertex_list.find(id1) == g->vertex_list.end()) {
    Vertex *v1 = new Vertex();
    vertex_init(v1);
    v1->id = id1;
    v1->nbr_set.insert(id2);
    g->vertex_list[id1] = v1;
    g->vertex_num++;
    e->src_v = v1;
  } else {
    g->vertex_list[id1]->nbr_set.insert(id2);
    e->src_v = g->vertex_list[id1];
  }
  if (g->vertex_list.find(id2) == g->vertex_list.end()) {
    Vertex *v2 = new Vertex();
    vertex_init(v2);
    v2->id = id2;
    v2->nbr_set.insert(id1);
    g->vertex_list[id2] = v2;
    g->vertex_num++;
    e->dst_v = v2;
  } else {
    g->vertex_list[id2]->nbr_set.insert(id1);
    e->dst_v = g->vertex_list[id2];
  }
}

/**
 * 添加一个顶点
 * 若为新顶点，不添加邻居
 */
void add_vertex_to_graph(unsigned long id, Graph *g) {
  if (g->vertex_list.find(id) == g->vertex_list.end()) {
    Vertex *v = new Vertex();
    vertex_init(v);
    v->id = id;
    g->vertex_list[id] = v;
    g->vertex_num++;
  }
}

/**
 * 查找边
 * 不确保顶点表包含id1, id2
 * 若包含id1, id2，则确保id1, id2的邻居列表包含对方
 * 确保id1<id2
 */
bool find_edge(unsigned long id1, unsigned long id2, Graph *g) {
	if (id1 > id2) 
		throw std::runtime_error("id1 > id2\n");
  Vertex *v1;
  if (g->vertex_list.find(id1) == g->vertex_list.end()) {
    return false;
  } else {
    v1 = g->vertex_list[id1];
    if (g->vertex_list.find(id2) == g->vertex_list.end()) {
      return false;
    } else if (v1->nbr_set.find(id2) == v1->nbr_set.end()) {
      return false;
    }
  }
  return true;
}

void print_graph(Graph *graph, bool print_all) {
  printf("顶点数：%lu 无向边数: %lu \n", graph->vertex_num, graph->edge_num);
	// printf("有向边数: %lu\n", graph->directed_edge_num);
  // 顶点信息
  if (print_all) {
    for (auto &pair : graph->vertex_list) {
      print_vertex(pair.second);
    }
    // 边信息
    for (auto &pair : graph->edge_list) {
      print_edge(pair.second);
    }
  }
}

void print_vertex_list(
    std::unordered_map<unsigned long, Vertex *> &vertex_list) {
  for (auto &pair : vertex_list) {
    print_vertex(pair.second);
  }
}
void print_edge_list(std::unordered_map<unsigned long, Edge *> &edge_list) {
  for (auto &pair : edge_list) {
    print_edge(pair.second);
  }
}

inline void print_vertex(Vertex *vertex) {
  printf("顶点id: %lu  ", vertex->id);
  printf("邻居数：%lu  ", vertex->nbr_set.size());
  for (auto &nbr : vertex->nbr_set) {
    printf("邻居id: %lu ", nbr);
  }
  printf("\n");
}

inline void print_edge(Edge *edge) {
  printf("边id: %lu ", edge->id);
  printf("src: %lu -> ", edge->src_v->id);
  printf("dst: %lu\n", edge->dst_v->id);
}