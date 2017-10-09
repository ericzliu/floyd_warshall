#include "floyd_warshall.h"
#include <algorithm>

int floyd_warshall::infinity = std::numeric_limits<int>::max();

floyd_warshall::floyd_warshall()
{
}


floyd_warshall::~floyd_warshall()
{
}

bool floyd_warshall::run(adjacency_list* graph, floyd_warshall::cost_matrix& matrix)
{
   int node_num = graph->get_node_num();
   floyd_warshall::cost_matrix m0(node_num);
   floyd_warshall::cost_matrix m1(node_num);
   // iteration 0
   // base case
   for (int i = 1; i <= node_num; i++) {
      for (int j = 1; j <= node_num; j++) {
         if (i == j) {
            m0.set_cost(i, j, 0);
         }
         else {
            int cost = graph->edge_cost(i, j);
            if (cost == adjacency_list::infinity) {
               m0.set_cost(i, j, floyd_warshall::infinity);
            }
            else {
               m0.set_cost(i, j, cost);
            }
         }
      }
   }

   for (int k = 1; k <= node_num; k++)
   {
      floyd_warshall::cost_matrix* m1_ = (k % 2 == 1) ? &m1 : &m0;
      floyd_warshall::cost_matrix* m0_ = (m1_ == &m1) ? &m0 : &m1;
      for (int i = 1; i <= node_num; i++) {
         for (int j = 1; j <= node_num; j++) {
            int v = m0_->get_cost(i, j);
            int w0 = m0_->get_cost(i, k);
            int w1 = m0_->get_cost(k, j);
            int w = floyd_warshall::infinity;
            if (w0 != floyd_warshall::infinity && w1 != floyd_warshall::infinity)
            {
               w = w0 + w1;
            }
            m1_->set_cost(i, j, std::min(v, w));
            if (i == j && m1_->get_cost(i, j) < 0)
            {
               return false;
            }
         }
      }
   }

   cost_matrix* last = (node_num % 2 == 1) ? &m1 : &m0;
   for (int i = 1; i <= node_num; i++) {
      for (int j = 1; j <= node_num; j++) {
         matrix.set_cost(i, j, last->get_cost(i, j));
      }
   }
   return true;
}
