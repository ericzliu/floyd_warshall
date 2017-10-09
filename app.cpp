#include "adjacency_list.h"
#include "floyd_warshall.h"
#include <iostream>

int shortest_shortest_path(floyd_warshall::cost_matrix& cmatrix) {
   int node_num = cmatrix.get_node_num();
   int shortest = floyd_warshall::infinity;
   for (int s = 1; s <= node_num; s++) {
      for (int t = 1; t <= node_num; t++) {
         if (cmatrix.get_cost(s, t) < shortest) {
            shortest = cmatrix.get_cost(s, t);
         }
      }
   }
   return shortest;
}

int main(int argc, char** argv) {
   if (argc != 2)
   {
      return 1;
   }
   std::unique_ptr<adjacency_list> graph = read_graph(argv[1]);
   floyd_warshall::cost_matrix cmatrix(graph->get_node_num());
   bool well_formed = floyd_warshall().run(graph.get(), cmatrix);
   if (well_formed)
   {
      std::cout << shortest_shortest_path(cmatrix) << std::endl;
   }
   else
   {
      std::cout << "NULL" << std::endl;
   }
   return 0;
}
