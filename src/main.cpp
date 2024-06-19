#include <cstdio>
#include <cstring>
#include <stdexcept>

#include "fun.h"

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
  graph = graph_from_dir(dir, print_all);
  return 0;
}