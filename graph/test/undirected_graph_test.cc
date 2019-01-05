#include "graph/undirected_graph.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

typedef std::string LabelType;
typedef UndirectedGraph<LabelType> GraphType;

TEST(UndirectedGraphTest, InitializerListConstructor) {
  Graph<LabelType>* graph = new GraphType({"D", "B", "C"});
  EXPECT_EQ(std::vector<LabelType>({"D"}), graph->bfs("D"));
  EXPECT_EQ(std::vector<LabelType>({"B"}), graph->bfs("B"));
  EXPECT_EQ(std::vector<LabelType>({"C"}), graph->bfs("C"));
  EXPECT_EQ(std::vector<LabelType>(), graph->bfs("A"));

  delete graph;
}

TEST(UndirectedGraphTest, AddVertex) {
  Graph<LabelType>* graph = new GraphType();

  graph->add_vertex("A");
  EXPECT_EQ(std::vector<LabelType>({"A"}), graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>(), graph->bfs("D"));

  graph->add_vertex("A");
  graph->add_vertex("B");
  EXPECT_EQ(std::vector<LabelType>({"A"}), graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>({"B"}), graph->bfs("B"));
  EXPECT_EQ(std::vector<LabelType>(), graph->bfs("C"));

  delete graph;
}

TEST(UndirectedGraphTest, AddEdge) {
  Graph<LabelType>* graph = new GraphType({"A", "B"});
  graph->add_edge("A", "B");
  graph->add_edge("C", "D");
  graph->add_edge("A", "C");
  graph->add_edge("C", "B");
  EXPECT_EQ(std::vector<LabelType>({"A", "B", "C", "D"}), graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>({"B", "A", "C", "D"}), graph->bfs("B"));
  EXPECT_EQ(std::vector<LabelType>({"C", "A", "B", "D"}), graph->bfs("C"));
  EXPECT_EQ(std::vector<LabelType>({"D", "C", "A", "B"}), graph->bfs("D"));

  graph->add_edge("A", "E");
  EXPECT_EQ(std::vector<LabelType>({"A", "B", "C", "E", "D"}), graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>({"D", "C", "A", "B", "E"}), graph->bfs("D"));

  delete graph;
}

TEST(UndirectedGraphTest, BFS) {
  Graph<LabelType>* graph = new GraphType({"A", "B", "C", "D", "E", "F"});
  graph->add_edge("A", "B");
  graph->add_edge("C", "D");
  graph->add_edge("A", "C");
  graph->add_edge("C", "B");
  graph->add_edge("A", "F");
  graph->add_edge("B", "F");
  graph->add_edge("C", "F");
  graph->add_edge("B", "E");
  graph->add_edge("D", "E");

  EXPECT_EQ(std::vector<LabelType>({"A", "B", "C", "F", "E", "D"}),
            graph->bfs("A"));
  EXPECT_EQ(std::vector<LabelType>({"B", "A", "C", "E", "F", "D"}),
            graph->bfs("B"));
  EXPECT_EQ(std::vector<LabelType>({"C", "A", "B", "D", "F", "E"}),
            graph->bfs("C"));
  EXPECT_EQ(std::vector<LabelType>({"D", "C", "E", "A", "B", "F"}),
            graph->bfs("D"));
  EXPECT_EQ(std::vector<LabelType>({"E", "B", "D", "A", "C", "F"}),
            graph->bfs("E"));
  EXPECT_EQ(std::vector<LabelType>({"F", "A", "B", "C", "E", "D"}),
            graph->bfs("F"));

  delete graph;
}

TEST(UndirectedGraphTest, DFSRecursive) {
  Graph<LabelType>* graph = new GraphType({"A", "B", "C", "D", "E", "F"});
  graph->add_edge("A", "B");
  graph->add_edge("C", "D");
  graph->add_edge("C", "B");
  graph->add_edge("A", "F");
  graph->add_edge("B", "F");
  graph->add_edge("D", "E");

  EXPECT_EQ(std::vector<LabelType>({"A", "B", "C", "D", "E", "F"}),
            graph->dfs_recursive("A"));
  EXPECT_EQ(std::vector<LabelType>({"B", "A", "F", "C", "D", "E"}),
            graph->dfs_recursive("B"));
  EXPECT_EQ(std::vector<LabelType>({"C", "B", "A", "F", "D", "E"}),
            graph->dfs_recursive("C"));
  EXPECT_EQ(std::vector<LabelType>({"D", "C", "B", "A", "F", "E"}),
            graph->dfs_recursive("D"));
  EXPECT_EQ(std::vector<LabelType>({"E", "D", "C", "B", "A", "F"}),
            graph->dfs_recursive("E"));
  EXPECT_EQ(std::vector<LabelType>({"F", "A", "B", "C", "D", "E"}),
            graph->dfs_recursive("F"));

  delete graph;
}

TEST(UndirectedGraphTest, DFSIterative) {
  Graph<LabelType>* graph = new GraphType({"A", "B", "C", "D", "E", "F"});
  graph->add_edge("A", "B");
  graph->add_edge("C", "D");
  graph->add_edge("C", "B");
  graph->add_edge("A", "F");
  graph->add_edge("B", "F");
  graph->add_edge("D", "E");

  EXPECT_EQ(std::vector<LabelType>({"A", "B", "C", "D", "E", "F"}),
            graph->dfs_iterative("A"));
  EXPECT_EQ(std::vector<LabelType>({"B", "A", "F", "C", "D", "E"}),
            graph->dfs_iterative("B"));
  EXPECT_EQ(std::vector<LabelType>({"C", "B", "A", "F", "D", "E"}),
            graph->dfs_iterative("C"));
  EXPECT_EQ(std::vector<LabelType>({"D", "C", "B", "A", "F", "E"}),
            graph->dfs_iterative("D"));
  EXPECT_EQ(std::vector<LabelType>({"E", "D", "C", "B", "A", "F"}),
            graph->dfs_iterative("E"));
  EXPECT_EQ(std::vector<LabelType>({"F", "A", "B", "C", "D", "E"}),
            graph->dfs_iterative("F"));

  delete graph;
}

}  // namespace
