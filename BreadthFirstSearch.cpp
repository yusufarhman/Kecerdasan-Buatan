#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Struktur node untuk graf
struct TreeNode {
    string name;
    vector<TreeNode*> neighbors; // Daftar tetangga (bukan anak)

    TreeNode(string n) : name(n) {}
};

// Kelas Graf
class Graph {
public:
    unordered_map<string, TreeNode*> nodes; // Menyimpan semua node dalam graf

    // Tambah edge ke dalam graf (undirected)
    void addEdge(string node1, string node2) {
        // Membuat node jika belum ada
        if (nodes.find(node1) == nodes.end()) nodes[node1] = new TreeNode(node1);
        if (nodes.find(node2) == nodes.end()) nodes[node2] = new TreeNode(node2);
        
        // Menambahkan hubungan dua arah
        nodes[node1]->neighbors.push_back(nodes[node2]);
        nodes[node2]->neighbors.push_back(nodes[node1]);
    }

    // BFS untuk mencari jalur terpendek dari start ke end
    void bfs(string start, string end) {
        if (nodes.find(start) == nodes.end()) {
            cout << "Kota awal " << start << " tidak ditemukan dalam graf!" << endl;
            return;
        }
        if (nodes.find(end) == nodes.end()) {
            cout << "Kota tujuan " << end << " tidak ditemukan dalam graf!" << endl;
            return;
        }

        queue<TreeNode*> q;
        unordered_map<TreeNode*, TreeNode*> parent; // Menyimpan jalur
        unordered_set<TreeNode*> visited; // Menandai kota yang sudah dikunjungi

        TreeNode* startNode = nodes[start];
        q.push(startNode);
        visited.insert(startNode);
        parent[startNode] = nullptr; // Start tidak memiliki parent

        bool found = false;
        while (!q.empty() && !found) {
            TreeNode* currentNode = q.front();
            q.pop();

            cout << "Mengunjungi kota: " << currentNode->name << endl;

            if (currentNode->name == end) {
                found = true;
                break;
            }

            // Kunjungi semua tetangga
            for (TreeNode* neighbor : currentNode->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent[neighbor] = currentNode;
                    q.push(neighbor);
                }
            }
        }

        if (!found) {
            cout << "Tidak ada jalur dari " << start << " ke " << end << endl;
            return;
        }

        // Rekonstruksi jalur
        vector<string> path;
        TreeNode* current = nodes[end];
        while (current != nullptr) {
            path.push_back(current->name);
            current = parent[current];
        }

        reverse(path.begin(), path.end());

        cout << "Jalur terpendek: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
};


int main() {
    Graph graph;
    
    // Membangun graf dengan hubungan dua arah
    graph.addEdge("Arad", "Timisoara");
    graph.addEdge("Arad", "Sibiu");
    graph.addEdge("Arad", "Zerind");
    
    graph.addEdge("Timisoara", "Lugoj");
    graph.addEdge("Sibiu", "Rimnicu Vilea");
    graph.addEdge("Sibiu", "Fagaras");
    graph.addEdge("Zerind", "Oradea");
    
    graph.addEdge("Lugoj", "Mehadia");
    graph.addEdge("Rimnicu Vilea", "Craiova");
    graph.addEdge("Rimnicu Vilea", "Pitesti");
    graph.addEdge("Fagaras", "Bucharest");
    graph.addEdge("Oradea", "Sibiu");
    
    graph.addEdge("Mehadia", "Dobreta");
    graph.addEdge("Craiova", "Dobreta");
    graph.addEdge("Craiova", "Pitesti");
    graph.addEdge("Pitesti", "Bucharest");
    graph.addEdge("Bucharest", "Giurgiu");
    graph.addEdge("Bucharest", "Urziceni");
    
    graph.addEdge("Urziceni", "Hirsova");
    graph.addEdge("Urziceni", "Vaslui");
    
    graph.addEdge("Hirsova", "Eforie");
    graph.addEdge("Vaslui", "Iasi");
    
    graph.addEdge("Iasi", "Neamt");

    // Input pengguna
    string start, destination;
    cout << "Masukan Kota Awal: ";
    cin >> start;
    cout << "Masukan Kota Tujuan: ";
    cin >> destination;

    graph.bfs(start, destination);

    return 0;
}