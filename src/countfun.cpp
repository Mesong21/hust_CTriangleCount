#include "countfun.h"

#include <algorithm>
#include <cstdio>
#include <set>
#include <stdexcept>



unsigned long count_triangles(Graph *graph) {
	edges_to_vertexes(graph);
	unsigned long tri_num;
	tri_num = add_vertexes(graph);
	return tri_num;
}



/**
 * 遍历每个边，计算两个顶点的交集大小，并发送给这两个顶点
 */
void edges_to_vertexes(Graph *graph) {
	for (auto &pair: graph->edge_list) {
		Edge *e = pair.second;
		Vertex *v1 = e->src_v;
		Vertex *v2 = e->dst_v;
		std::set<unsigned long> inter_set;
		std::set_intersection(v1->nbr_set.begin(), v1->nbr_set.end(), v2->nbr_set.begin(), v2->nbr_set.end(), std::inserter(inter_set, inter_set.begin()));
		// 得到交集大小
		unsigned long inter_size = inter_set.size();
		// printf("交集大小：%lu\n", inter_size);
		v1->tri_num += inter_size;
		v2->tri_num += inter_size;
	}
}

unsigned long add_vertexes(Graph *graph) {
	unsigned long total_num = 0;
	for (auto &pair: graph->vertex_list) {
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