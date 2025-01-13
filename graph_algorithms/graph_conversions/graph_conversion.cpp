#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> readAdjacencyMatrixFromFile(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open the file!" << endl;
        return vector<vector<int>>();
    }

    vector<vector<int>> graph;
    string line;

    if (getline(file, line)) {}

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        int value;

        ss >> value;

        while (ss >> value) {
            row.push_back(value);
        }

        graph.push_back(row);
    }

    file.close();
    return graph;
}

void printAdjacencyMatrix(const vector<vector<int>>& graph) {
    int size = graph.size();

    cout << "  ";
    for (int i = 0; i < size; ++i) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < size; ++i) {
        cout << i << " ";
        for (int value : graph[i]) {
            cout << value << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> readNodeListGraphFromFile(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open the file!" << endl;
        return vector<vector<int>>();
    }

    vector<vector<int>> graph;
    string line;

    while (getline(file, line)) {
        vector<int> neighbors;
        stringstream ss(line);
        string token;

        ss >> token;

        while (getline(ss, token, ',')) {
            stringstream valueStream(token);
            int neighbor;
            if (valueStream >> neighbor) {
                neighbors.push_back(neighbor);
            }
        }

        graph.push_back(neighbors);
    }

    file.close();
    return graph;
}

void printNodeListGraph(const vector<vector<int>>& graph) {
    for (size_t i = 0; i < graph.size(); ++i) {
        cout << "Node(" << i << "): ";
        for (size_t j = 0; j < graph[i].size(); ++j) {
            cout << graph[i][j];
            if (j < graph[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

vector<vector<int>> convertAdjacencyMatrixToNodeListGraph(const vector<vector<int>>& adjacencyMatrix) {
    vector<vector<int>> nodeListGraph;
    int size = adjacencyMatrix.size();

    for (int i = 0; i < size; ++i) {
        vector<int> neighbors;
        for (int j = 0; j < size; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                neighbors.push_back(j);
            }
        }
        nodeListGraph.push_back(neighbors);
    }
    return nodeListGraph;
}

vector<vector<int>> convertNodeListGraphToAdjacencyMatrix(const vector<vector<int>>& nodeListGraph) {
    int size = nodeListGraph.size();
    vector<vector<int>> adjacencyMatrix(size, vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int neighbor : nodeListGraph[i]) {
            adjacencyMatrix[i][neighbor] = 1;
        }
    }
    return adjacencyMatrix;
}

int main() {
    vector<vector<int>> adjacencyMatrix = readAdjacencyMatrixFromFile("adjacencyMatrix.txt");
    cout << "Adjacency Matrix: " << endl;
    printAdjacencyMatrix(adjacencyMatrix);

    cout << endl;
    vector<vector<int>> nodeListGraph = readNodeListGraphFromFile("nodeListGraph.txt");
    cout << "Node List Graph:" << endl;
    printNodeListGraph(nodeListGraph);

    cout << endl;

    vector<vector<int>> convertedToNodeListGraph = convertAdjacencyMatrixToNodeListGraph(adjacencyMatrix);
    cout << "Adjacency Matrix to Node List Graph:" << endl;
    printNodeListGraph(convertedToNodeListGraph);

    cout << endl;

    vector<vector<int>> convertedToAdjacencyMatrix = convertNodeListGraphToAdjacencyMatrix(nodeListGraph);
    cout << "Node List Graph to Adjacency Matrix:" << endl;
    printAdjacencyMatrix(convertedToAdjacencyMatrix);

    return 0;
}