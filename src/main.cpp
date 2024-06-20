#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdexcept>

#include "graphfun.h"
#include "countfun.h"

int main(int argc, char **argv) {
  char dir[30];
  bool print_all = true;
  Graph *graph = NULL;
  printf("argv[1]: %s\n", argv[1]);
  if (argc > 1) {
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
  clock_t start_t, graph_t, calc_t;
  start_t = clock();
	// 建图
  graph = graph_from_dir(dir, print_all);
  print_graph(graph, print_all);
  graph_t = clock();
  printf("建图时间: %fs\n", (double)(graph_t - start_t) / CLOCKS_PER_SEC);

	// 计数
	unsigned long tri_num = count_triangles(graph);
	calc_t = clock();
	// printf("计算时间: %fms\n", (double)(calc_t - graph_t) / CLOCKS_PER_SEC * 1000);
	printf("三角形数量: %lu\n", tri_num);

	printf("总时间: %fs\n", (double)(calc_t - start_t) / CLOCKS_PER_SEC);
  return 0;
}