#pragma once

#include "graph.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace td {

// Undirected graph implementation by using adjacency map.
template <typename LabelType>
class UndirectedGraph : public Graph<LabelType> {
 public:
  ~UndirectedGraph() override = default;

  void add_vertex(const LabelType& label) override;
  void add_edge(const LabelType& source, const LabelType& destination) override;

  std::vector<LabelType> bfs(const LabelType& label) override;
  std::vector<LabelType> dfs_recursive(const LabelType& label) override;
  std::vector<LabelType> dfs_iterative(const LabelType& label) override;

 private:
  // Representation of a vertex on undirected graph.
  struct Vertex {
    LabelType label;
    std::unordered_map<LabelType, Vertex> neighbors;

    Vertex() = default;
    Vertex(const LabelType& l) : label(l) {}
  };

  // Vertexs stored in graph.
  std::unordered_map<LabelType, Vertex> vertexs_;
};

}  // namespace td

/****************  Undirected Graph implementation ****************/
namespace td {

template <typename LabelType>
void UndirectedGraph<LabelType>::add_vertex(const LabelType& label) {
  if (vertexs_.find(label) != vertexs_.end())
    return;
  vertexs_[label] = Vertex(label);
}

template <typename LabelType>
void UndirectedGraph<LabelType>::add_edge(const LabelType& source,
                                          const LabelType& destination) {
  if (vertexs_.find(source) == vertexs_.end())
    add_vertex(source);
  if (vertexs_.find(destination) == vertexs_.end())
    add_vertex(destination);

  vertexs_[source].neighbors[destination] = vertexs_[destination];
  vertexs_[destination].neighbors[source] = vertexs_[source];
}

template <typename LabelType>
std::vector<LabelType> UndirectedGraph<LabelType>::bfs(const LabelType& label) {
  if (vertexs_.find(label) == vertexs_.end())
    return {};

  std::vector<LabelType> result;
  std::unordered_set<LabelType> visited;
  std::queue<Vertex> frontier;
  frontier.push(vertexs_[label]);

  while (!frontier.empty()) {
    Vertex v = frontier.front();
    frontier.pop();

    if (visited.find(v.label) != visited.end())
      continue;

    result.push_back(v.label);
    visited.insert(v.label);

    for (auto kv : v.neighbors)
      frontier.push(kv.second);
  }
  return result;
}

template <typename LabelType>
std::vector<LabelType> UndirectedGraph<LabelType>::dfs_recursive(
    const LabelType& label) {
  return {label};
}

template <typename LabelType>
std::vector<LabelType> UndirectedGraph<LabelType>::dfs_iterative(
    const LabelType& label) {
  return {label};
}

}  // namespace td
