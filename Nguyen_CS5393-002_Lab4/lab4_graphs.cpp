#include <iostream>
#include <list>
#include <vector>

// constant Graph_Size
const int Graph_Size = 6;

class GraphDFS {
private:
    std::vector<std::list<int>> adjList;  // adjacency list representation

    // preorder DFS traversal helper
    void dfsPreorderHelper(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << v << " "; // visit node first
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsPreorderHelper(neighbor, visited);
            }
        }
    }

    // inorder DFS traversal helper (for binary tree)
    void dfsInorderHelper(int v, std::vector<bool>& visited) {
        if (adjList[v].size() > 2) return; // handle binary tree case

        auto it = adjList[v].begin();
        if (it != adjList[v].end() && !visited[*it]) { // left child
            dfsInorderHelper(*it, visited);
        }

        visited[v] = true;
        std::cout << v << " "; // visits node

        ++it;
        if (it != adjList[v].end() && !visited[*it]) { // right child
            dfsInorderHelper(*it, visited);
        }
    }

    // postorder DFS traversal helper
    void dfsPostorderHelper(int v, std::vector<bool>& visited) {
        visited[v] = true;
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsPostorderHelper(neighbor, visited);
            }
        }
        std::cout << v << " "; // visits node after children
    }

public:
    // constructor
    GraphDFS() {
        adjList.resize(Graph_Size); // initialize adjacency list with 6 nodes
    }

    // function for add an edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // for undirected graph
    }

    // preorder DFS
    void dfsPreorder(int start) {
        std::vector<bool> visited(Graph_Size, false);
        dfsPreorderHelper(start, visited);
        std::cout << "\n";
    }

    // inorder DFS (for binary tree)
    void dfsInorder(int start) {
        std::vector<bool> visited(Graph_Size, false);
        dfsInorderHelper(start, visited);
        std::cout << "\n";
    }

    // postorder DFS
    void dfsPostorder(int start) {
        std::vector<bool> visited(Graph_Size, false);
        dfsPostorderHelper(start, visited);
        std::cout << "\n";
    }

    // prints the adjacency list
    void printGraph() {
        std::cout << "Adjacency List Representation:\n";
        for (int i = 0; i < Graph_Size; i++) {
            std::cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    GraphDFS graph;

    // create edges based on the dataset [0, 1, 2, 3, 4, 5]
    // example of a tree-like graph structure for DFS
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);

    // print adjacency list
    graph.printGraph();

    // perform DFS traversals starting from node 0
    std::cout << "\nDFS Preorder Traversal:\n";
    graph.dfsPreorder(0);

    std::cout << "\nDFS Inorder Traversal:\n";
    graph.dfsInorder(0);

    std::cout << "\nDFS Postorder Traversal:\n";
    graph.dfsPostorder(0);

    return 0;
}
