#include "graph/undirected_graph.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

typedef std::string LabelType;
typedef UndirectedGraph<LabelType> GraphType;

TEST(UndirectedGraphTest, AddVertex) {
  Graph<LabelType> *graph = new GraphType();

  graph->add_vertex("A");
  EXPECT_EQ(std::vector<LabelType>({"A"}), graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>(), graph->bfs("D"));

  graph->add_vertex("A");
  graph->add_vertex("B");
  EXPECT_EQ(std::vector<LabelType>({"A"}), graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>({"B"}), graph->bfs("B"));
  EXPECT_EQ(std::vector<LabelType>(), graph->bfs("C"));
}

}  // namespace