#include <iostream>      
#include <vector>        
#include <cstdlib>      
#include <ctime>         
#include <iomanip>      
#include <set>          
#include <queue>        
#include <fstream>      
#include <random>

using namespace std;    



void writeAdjListCSV(const string& filename, const vector<vector<int>>& adjList) ;
// Output adjacency matrix
void printAdjMatrix(const vector<vector<int>>& matrix);
// Output adjacency list
void printAdjList(const vector<vector<int>>& adjList);
// DFS
void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited,
         vector<vector<int>>& dfsTreeMatrix, vector<vector<int>>& dfsTreeList);
// BFS
void bfs(int start, const vector<vector<int>>& graph,vector<bool>& visited,
         vector<vector<int>>& bfsTreeMatrix, vector<vector<int>>& bfsTreeList);
// Generate random graph
void generateRandomGraph(int n, int e, vector<vector<int>>& adjMatrix, vector<vector<int>>& adjList);
// cout
void exportGraph(const string& name, const vector<vector<int>>& matrix, const vector<vector<int>>& list);
// Building a DFS tree
void buildDFSTree(const vector<vector<int>>& adjList, vector<vector<int>>& dfsMatrix, vector<vector<int>>& dfsList);
//Build the BFS tree
void buildBFSTree(const vector<vector<int>>& adjList, vector<vector<int>>& bfsMatrix, vector<vector<int>>& bfsList);


int main() {
    int n, e;  
    cout << "Enter number of vertices: ";  // Input vertices
    cin >> n;  

    cout << "Enter number of edges: "; // Input of edges
    cin >> e;  

    // Calculate the maximum number of edges 
    int maxEdges = n * (n - 1) / 2;
    if (e > maxEdges) {  
        cout << "Too many edges! Maximum for a simple undirected graph is " << maxEdges << ".\n";
        return 1;  
    }

    // Initialize the adjacency matrix
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    // Initialize the adjacency list
    vector<vector<int>> adjList(n);

    // Generate a random graph and fill in the adjacency matrix and adjacency list
    generateRandomGraph(n, e, adjMatrix, adjList);
    // cout
    exportGraph("OriginalGraph.csv", adjMatrix, adjList);

    // Initialize the adjacency matrix of the DFS tree
    vector<vector<int>> dfsMatrix(n, vector<int>(n, 0));
    // Initialize the adjacency list of the DFS tree
    vector<vector<int>> dfsList(n);

    buildDFSTree(adjList, dfsMatrix, dfsList);
    // cout DFS tree
    exportGraph("DFSTree.csv", dfsMatrix, dfsList);


    vector<vector<int>> bfsMatrix(n, vector<int>(n, 0));

    vector<vector<int>> bfsList(n);

    buildBFSTree(adjList, bfsMatrix, bfsList);
    // cout BFS tree
    exportGraph("BFSTree.csv", bfsMatrix, bfsList);

    cout << "\ndone\n";  
    return 0;  
}




void generateRandomGraph(int n, int e, vector<vector<int>>& adjMatrix, vector<vector<int>>& adjList) {
    srand(time(0));  
    set<pair<int, int>> addedEdges;  // Use set to store the added edges to avoid duplication

    while (addedEdges.size() < e) {  // Continue looping when the number of added edges is less than the target number of edges
        int u = rand() % n;  
        int v = rand() % n;  

        if (u == v || u > v) continue;  // Exclude self-loops and repeated sequences
        if (addedEdges.count({u, v}) == 0) {  // If this edge has not been added yet
            // Add edges to the adjacency matrix
            adjMatrix[u][v] = adjMatrix[v][u] = 1;
            // Add edges to the adjacency list
            adjList[u].push_back(v);
            adjList[v].push_back(u);
            // Record the added edges
            addedEdges.insert({u, v});
        }
    }
}



void exportGraph(const string& name, const vector<vector<int>>& matrix, const vector<vector<int>>& list) {
    cout << "\n=== " << name << " ===";  
    printAdjMatrix(matrix);  
    printAdjList(list);  
    writeAdjListCSV(name, list);  
}


void buildDFSTree(const vector<vector<int>>& adjList, vector<vector<int>>& dfsMatrix, vector<vector<int>>& dfsList) {
    vector<bool> visited(adjList.size(), false);  // Initialize access token

    for(int i=0;i<adjList.size();++i){
        if(!visited[i]){
            dfs(i, adjList, visited, dfsMatrix, dfsList);  // Start DFS from vertex 0
        }
    }
}


void buildBFSTree(const vector<vector<int>>& adjList, vector<vector<int>>& bfsMatrix, vector<vector<int>>& bfsList) {
    vector<bool> visited(adjList.size(), false);
    for(int i=0;i<adjList.size();++i){
        if(!visited[i]){
            bfs(i, adjList, visited, bfsMatrix, bfsList);  
        }
    }
}



void writeAdjListCSV(const string& filename, const vector<vector<int>>& adjList) {
    ofstream file(filename);
    file << "Node,Neighbors\n";  

    for (int i = 0; i < adjList.size(); ++i) {
        file << i << ",";
        for (int j = 0; j < adjList[i].size(); ++j) {
            file << adjList[i][j];
            if (j != adjList[i].size() - 1)
                file << " ";  
        }
        file << "\n";
    }

    file.close();
}



void printAdjMatrix(const vector<vector<int>>& matrix) {
    cout << "\nAdjacency Matrix:\n   "; 
    for (int i = 0; i < matrix.size(); ++i)  
        cout << setw(2) << i << " ";
    cout << "\n";

    for (int i = 0; i < matrix.size(); ++i) { 
        cout << setw(2) << i << " "; 
        for (int j = 0; j < matrix.size(); ++j)  
            cout << setw(2) << matrix[i][j] << " ";  // Output matrix
        cout << "\n";  
    }
}


void printAdjList(const vector<vector<int>>& adjList) {
    cout << "\nAdjacency List:\n";  
    for (int i = 0; i < adjList.size(); ++i) {  
        cout << "[" << i << "] -> ";  
        for (int v : adjList[i])  
            cout << v << " ";  
        cout << "\n";  
    }
}


void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited,
         vector<vector<int>>& dfsTreeMatrix, vector<vector<int>>& dfsTreeList) {
    visited[node] = true;  // Mark the current vertex as visited
    for (int neighbor : graph[node]) {  // Traverse all neighbors of the current vertex
        if (!visited[neighbor]) {  // If the neighbor has not been visited yet
            // Add edges to the adjacency matrix of the DFS tree
            dfsTreeMatrix[node][neighbor] = dfsTreeMatrix[neighbor][node] = 1;
            // Add the edge to the adjacency list of the DFS tree
            dfsTreeList[node].push_back(neighbor);
            dfsTreeList[neighbor].push_back(node);
            // Recursively visit neighbor vertices
            dfs(neighbor, graph, visited, dfsTreeMatrix, dfsTreeList);
        }
    }
}


void bfs(int start, const vector<vector<int>>& graph,vector<bool>& visited,
         vector<vector<int>>& bfsTreeMatrix, vector<vector<int>>& bfsTreeList) { 
    queue<int> q;  
    q.push(start);  
    visited[start] = true;  // Mark the starting vertex as visited

    while (!q.empty()) {  // Continue looping while the queue is not empty
        int node = q.front(); q.pop();  // Take the vertex at the head of the queue
        for (int neighbor : graph[node]) {  // Iterate over all neighbors of this vertex
            if (!visited[neighbor]) {  // If the neighbor has not yet visited
                visited[neighbor] = true;  // Mark neighbor as visited
                // Add edges to the adjacency matrix of the BFS tree
                bfsTreeMatrix[node][neighbor] = bfsTreeMatrix[neighbor][node] = 1;
                // Add the edge to the adjacency list of the BFS tree
                bfsTreeList[node].push_back(neighbor);
                bfsTreeList[neighbor].push_back(node);
                // Add neighbors to the queue
                q.push(neighbor);
            }
        }
    }
}