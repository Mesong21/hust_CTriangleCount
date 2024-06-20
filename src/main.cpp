#include <sys/time.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdexcept>

#include "countfun.h"
#include "graphfun.h"

int main(int argc, char **argv) {
  char dir[30];
  bool print_all = true;
  int tnum = 1;
  Graph *graph = NULL;
  printf("argc: %d\n", argc);
  if (argc == 3) {
		tnum = atoi(argv[2]);
    if (strcmp(argv[1], "t1") == 0) {
      printf("运行测试\n");
      strcpy(dir, "/share/triCount/data/test1");
      print_all = false;
    } else if (strcmp(argv[1], "mt") == 0) {
      printf("运行我的小图测试\n");
      strcpy(dir, "/share/triCount/data/mytest");
      print_all = true;
    } else if (strcmp(argv[1], "r") == 0) {
      printf("运行大数据\n");
      strcpy(dir, "/share/triCount/data/tmp");
      print_all = false;
    } else
      throw std::runtime_error("参数错误\n");
  } else
    throw std::runtime_error("参数错误\n");
  

  struct timeval start_t, graph_t, calc_t;
  gettimeofday(&start_t, NULL);
  // 建图
  graph = graph_from_dir(dir, print_all, tnum);
  print_graph(graph, print_all);
  gettimeofday(&graph_t, NULL);
  double graph_time = (graph_t.tv_sec - start_t.tv_sec) +
                      (graph_t.tv_usec - start_t.tv_usec) / 1000000.0;
  printf("建图时间: %fs\n", graph_time);

  // 计数
  unsigned long tri_num = count_triangles(graph, tnum);
  gettimeofday(&calc_t, NULL);
  double calc_time = (calc_t.tv_sec - graph_t.tv_sec) +
                     (calc_t.tv_usec - graph_t.tv_usec) / 1000000.0;
  printf("计数时间: %fs\n", calc_time);
  printf("三角形数量: %lu\n", tri_num);

  printf("总时间: %fs\n", (graph_time + calc_time));
  return 0;
}