#include "fun.h"

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
Graph *graph_from_dir(const char *dir) {
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

      // 设置边
      Edge *e = new Edge();
      edge_init(e);
      g->edge_num++;
      e->id = g->edge_num;  // 从1开始

      // 加入顶点表
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

      // 加入边表
      if (g->edge_list.find(g->edge_num) == g->edge_list.end()) {
        g->edge_list[g->edge_num] = e;
      }
    }
  }
  print_graph(g);
  return g;
}

void print_graph(Graph *graph) {
  printf("顶点数：%lu 边数: %lu\n", graph->vertex_num, graph->edge_num);
  // 顶点信息
  for (auto &pair : graph->vertex_list) {
		print_vertex(pair.second);
  }
  // 边信息
  for (auto &pair : graph->edge_list) {
    print_edge(pair.second);
  }
}

void print_vertex(Vertex *vertex) {
  printf("顶点id: %lu  ", vertex->id);
  printf("邻居数：%lu  ", vertex->nbr_set.size());
  for (auto &nbr : vertex->nbr_set) {
    printf("邻居id: %lu ", nbr);
  }
  printf("\n");
}

void print_edge(Edge *edge) {
  printf("边id: %lu ", edge->id);
  printf("src: %lu -> ", edge->src_v->id);
  printf("dst: %lu\n", edge->dst_v->id);
}