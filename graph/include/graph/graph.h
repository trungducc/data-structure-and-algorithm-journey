#pragma once

#include <vector>
#include "utils/macros.h"

namespace td {

template <typename LabelType>
class Graph {
 public:
  virtual void add_vertex(const LabelType& label) = 0;
  virtual void add_edge(const LabelType& source, const LabelType& destination) = 0;
  virtual std::vector<LabelType> bfs() = 0;
  virtual std::vector<LabelType> dfs_recursive() = 0;
  virtual std::vector<LabelType> dfs_iterative() = 0;
 private:
  DISALLOW_COPY_AND_ASSIGN(Graph);
};

}  // namespace td
