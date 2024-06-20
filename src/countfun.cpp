#include "countfun.h"

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <mutex>
#include <set>
#include <stdexcept>
#include <thread>
std::mutex mtx;  // 互斥锁

void process_edges(Graph *graph,
                   std::unordered_map<unsigned long, Edge *>::iterator start,
                   std::unordered_map<unsigned long, Edge *>::iterator end) {
  for (auto it = start; it != end; ++it) {
    Edge *e = it->second;
    Vertex *v1 = e->src_v;
    Vertex *v2 = e->dst_v;
    std::set<unsigned long> inter_set;
    std::set_intersection(v1->nbr_set.begin(), v1->nbr_set.end(),
                          v2->nbr_set.begin(), v2->nbr_set.end(),
                          std::inserter(inter_set, inter_set.begin()));
    unsigned long inter_size = inter_set.size();
    mtx.lock();
    v1->tri_num += inter_size;
    v2->tri_num += inter_size;
    mtx.unlock();
  }
}



/**
 * 遍历每个边，计算两个顶点的交集大小，并发送给这两个顶点
 */
void edges_to_vertexes(Graph *graph) {
  std::vector<std::thread> threads;
  auto start = graph->edge_list.begin();
  auto end = graph->edge_list.end();
  auto part_size = std::distance(start, end) / 16;
  for (int i = 0; i < 16; ++i) {
    auto part_end = std::next(start, part_size);
    if (i == 15) {  // 最后一部分，包含所有剩余的边
      part_end = end;
    }
    threads.push_back(std::thread(process_edges, graph, start, part_end));
    start = part_end;  // 下一部分的开始
  }
  for (auto &th : threads) {
    th.join();
  }
}
unsigned long count_triangles(Graph *graph) {
  clock_t start_t, edges_t, vertexes_t;
  start_t = clock();
  edges_to_vertexes(graph);
  edges_t = clock();
  printf("传播时间: %fs\n", (double)(edges_t - start_t) / CLOCKS_PER_SEC);
  unsigned long tri_num;

  tri_num = add_vertexes(graph);
  vertexes_t = clock();
  printf("计算时间: %fs\n", (double)(vertexes_t - edges_t) / CLOCKS_PER_SEC);
  return tri_num;
}
unsigned long add_vertexes(Graph *graph) {
  unsigned long total_num = 0;
  for (auto &pair : graph->vertex_list) {
    Vertex *v = pair.second;
    unsigned long tri_num = v->tri_num;
    tri_num /= 2;
    total_num += tri_num;
  }
  if (total_num % 3 != 0) {
    throw std::runtime_error("不是3的倍数!\n");
  }
  return total_num / 3;
}