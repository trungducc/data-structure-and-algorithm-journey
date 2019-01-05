#pragma once

#include "graph.h"

#include <queue>
#include <stack>
#include <map>
#include <unordered_set>

namespace td {

// Undirected graph implementation by using adjacency map.
template <typename LabelType>
class UndirectedGraph : public Graph<LabelType> {
 public:
  UndirectedGraph() = default;
  UndirectedGraph(std::initializer_list<LabelType>&& labels);

  ~UndirectedGraph() override;

  void add_vertex(const LabelType& label) override;
  void add_edge(const LabelType& source, const LabelType& destination) override;

  std::vector<LabelType> bfs(const LabelType& label) override;
  std::vector<LabelType> dfs_recursive(const LabelType& label) override;
  std::vector<LabelType> dfs_iterative(const LabelType& label) override;

 private:
  // Representation of a vertex on undirected graph.
  struct Vertex {
    LabelType label;
    std::map<LabelType, Vertex*> neighbors;

    Vertex() = default;
    Vertex(const LabelType& l) : label(l) {}
  };

  // If there is a vertex with given label in graph, return true. Otherwise,
  // return false.
  bool has_vertex(const LabelType& label);

  // Depth first traversal from vertex with given label recursively.
  void dfs_recursive_impl(const LabelType& label,
                          std::vector<LabelType>& result,
                          std::unordered_set<LabelType>& visited);

  // Vertexs stored in graph.
  std::map<LabelType, Vertex*> vertexs_;
};

}  // namespace td

/****************  Undirected Graph implementation ****************/
namespace td {

template <typename LabelType>
UndirectedGraph<LabelType>::~UndirectedGraph() {
  for (auto kv : vertexs_)
    delete kv.second;
}

template <typename LabelType>
UndirectedGraph<LabelType>::UndirectedGraph(
    std::initializer_list<LabelType>&& il) {
  for (LabelType label : il)
    add_vertex(label);
}

template <typename LabelType>
void UndirectedGraph<LabelType>::add_vertex(const LabelType& label) {
  if (has_vertex(label))
    return;
  vertexs_[label] = new Vertex(label);
}

template <typename LabelType>
void UndirectedGraph<LabelType>::add_edge(const LabelType& source,
                                          const LabelType& destination) {
  if (!has_vertex(source))
    add_vertex(source);
  if (!has_vertex(destination))
    add_vertex(destination);

  vertexs_[source]->neighbors[destination] = vertexs_[destination];
  vertexs_[destination]->neighbors[source] = vertexs_[source];
}

template <typename LabelType>
std::vector<LabelType> UndirectedGraph<LabelType>::bfs(const LabelType& label) {
  if (!has_vertex(label))
    return {};

  std::vector<LabelType> result;
  std::unordered_set<LabelType> visited;
  std::queue<Vertex*> to_visit;
  to_visit.push(vertexs_[label]);

  while (!to_visit.empty()) {
    Vertex* v = to_visit.front();
    to_visit.pop();

    if (visited.find(v->label) != visited.end())
      continue;

    result.push_back(v->label);
    visited.insert(v->label);

    for (auto kv : v->neighbors)
      to_visit.push(kv.second);
  }
  return result;
}

template <typename LabelType>
std::vector<LabelType> UndirectedGraph<LabelType>::dfs_recursive(
    const LabelType& label) {
  if (!has_vertex(label))
    return {};
  std::vector<LabelType> result;
  std::unordered_set<LabelType> visited;
  dfs_recursive_impl(label, result, visited);
  return result;
}

template <typename LabelType>
std::vector<LabelType> UndirectedGraph<LabelType>::dfs_iterative(
    const LabelType& label) {
  if (!has_vertex(label))
    return {};

  std::vector<LabelType> result;
  std::unordered_set<LabelType> visited;
  std::stack<Vertex*> to_visit;
  to_visit.push(vertexs_[label]);

  while (!to_visit.empty()) {
    Vertex* v = to_visit.top();
    to_visit.pop();

    if (visited.find(v->label) != visited.end())
      continue;

    result.push_back(v->label);
    visited.insert(v->label);

    for (auto iter = v->neighbors.rbegin(); iter != v->neighbors.rend(); ++iter)
      to_visit.push(iter->second);
  }
  return result;
}

template <typename LabelType>
bool UndirectedGraph<LabelType>::has_vertex(const LabelType& label) {
  return vertexs_.find(label) != vertexs_.end();
}

template <typename LabelType>
void UndirectedGraph<LabelType>::dfs_recursive_impl(
    const LabelType& label,
    std::vector<LabelType>& result,
    std::unordered_set<LabelType>& visited) {
  if (visited.find(label) != visited.end())
    return;

  result.push_back(label);
  visited.insert(label);

  for (auto kv : vertexs_[label]->neighbors)
    dfs_recursive_impl(kv.first, result, visited);
}

}  // namespace td
