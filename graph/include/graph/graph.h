#pragma once

#include <vector>
#include "utils/macros.h"

namespace td {

// Graph interface
template <typename LabelType>
class Graph {
 public:
  Graph() = default;

  virtual ~Graph() = default;

  // Add a vertex with given label to graph.
  virtual void add_vertex(const LabelType& label) = 0;

  // Add an edge to graph. If |source| or |destination| doesn't exist in graph,
  // add them.
  virtual void add_edge(const LabelType& source,
                        const LabelType& destination) = 0;

  // Breadth first traversal from vertex with given label.
  virtual std::vector<LabelType> bfs(const LabelType& label) = 0;

  // Depth first traversal from vertex with given label recursively.
  virtual std::vector<LabelType> dfs_recursive(const LabelType& label) = 0;

  // Depth first traversal from vertex with given label iteratively.
  virtual std::vector<LabelType> dfs_iterative(const LabelType& label) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Graph);
};

}  // namespace td
