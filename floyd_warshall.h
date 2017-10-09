#pragma once

#include "adjacency_list.h"
#include <vector>
#include <limits>

class floyd_warshall
{
public:
   static int infinity;

   struct cost_matrix
   {
   private:
      std::vector< std::vector< int > > _costs;
   public:
      int get_node_num() {
         return _costs.size() - 1;
      }
      cost_matrix(int node_num)
         : _costs(1 + node_num, std::vector< int >())
      {
         for (int i = 0; i <= node_num; i++)
         {
            _costs[i] = std::vector<int>(1 + node_num, infinity);
         }
      }
      void set_cost(int s, int t, int cost) {
         _costs[s][t] = cost;
      }
      int get_cost(int s, int t) {
         return _costs[s][t];
      }
   };

   floyd_warshall();
   ~floyd_warshall();
   bool run(adjacency_list* graph, cost_matrix& matrix);
};


