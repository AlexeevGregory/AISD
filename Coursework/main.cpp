#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Edge {
    char node1, node2;
    int weight;
};

class Graph {
    vector<Edge*> edges;
public:
    

    void addEdge(char from, char to, int weightEdge) {
        Edge* NewEdge = new Edge();
        NewEdge->node1 = from;
        NewEdge->node2 = to;
        NewEdge->weight = weightEdge;
        edges.push_back(NewEdge);
    }
    void printEdges() {
        for (int i = 0; i < edges.size(); i++) {
            cout << edges[i]->node1 << "->" << edges[i]->node2 << " : " << edges[i]->weight << endl;
        }
    }
    void CreateGraph() {
        string line = "";
        vector<vector<int>> values;
        int count = 0;
        string name;
        vector<char> names;

        ifstream inputFile("input.txt");
        getline(inputFile, line);
        //имена вершин, списываемые с файла
        for (auto& c : line) {
            if (c == ' ') {
                if (!name.empty()) names.push_back(name[0]);
                name.clear();
                count++;
            }
            else {
                name += c;
            }
        }
        names.push_back(name[0]);

        //считывание значений ребер
        while (getline(inputFile, line)) {
            vector<int> row;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] != ' ') {
                    row.push_back(line[i] - '0');
                }
            }
            values.push_back(row);
        }
        //проверка на верность считывания
        /*for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                cout << values[i][j] << " ";
            }
            cout << endl;
        }
        */
        //добавление ребер в граф
        for (int i = 0; i < count; i++) {
            for (int j = i; j < count; j++) {
                if (values[i][j] != 0) addEdge(names[i], names[j], values[i][j]);
            }
        }
        
        //printEdges();
        inputFile.close();
    }
    bool findNode(vector<char> Nodes, char Node) {
        for (int i = 0; i < Nodes.size(); i++) {
            if (Node == Nodes[i]) return 1;
        }
        return 0;
    }
    vector<Edge*> sort(vector<Edge*> Edges) {
        for (int j = 0; j < Edges.size(); j++) {
            for (int i = j; i < Edges.size()-1; i++) {
                if (Edges[i]->weight > Edges[i + 1]->weight) {
                    Edge* SwapElem = Edges[i];
                    Edges[i] = Edges[i+1];
                    Edges[i + 1] = SwapElem;
                }
            }
            for (int i = Edges.size()-1; i >j; i--) {
                if (Edges[i]->weight < Edges[i - 1]->weight) {
                    Edge* SwapElem = Edges[i];
                    Edges[i] = Edges[i - 1];
                    Edges[i - 1] = SwapElem;
                }
            }
        }
        return Edges;
    }
    void KruskalAlgorithm() {
        vector<Edge*> sortEdges;
        vector<Edge*> SkeletonEdges;
        vector<char> usedNodes;
        for (int i = 0; i < edges.size(); i++) {
            sortEdges.push_back(edges[i]);
        }
        sortEdges = sort(sortEdges);
        cout << "Отсортированные ребра:" << endl;
        for (int i = 0; i < sortEdges.size(); i++) {
            cout << sortEdges[i]->node1 << "->" << sortEdges[i]->node2 << " : " << sortEdges[i]->weight << endl;
        }

        SkeletonEdges.push_back(sortEdges[0]);
        usedNodes.push_back(SkeletonEdges[0]->node1);
        auto iter = sortEdges.cbegin();
        sortEdges.erase(iter);
        for (int i = 0; i < sortEdges.size(); i++) {
            if (findNode(usedNodes, sortEdges[i]->node2) == 0) {
                SkeletonEdges.push_back(sortEdges[i]);
                if (findNode(usedNodes, SkeletonEdges[SkeletonEdges.size() - 1]->node1) == 0) usedNodes.push_back(sortEdges[i]->node1);
                if (findNode(usedNodes, SkeletonEdges[SkeletonEdges.size() - 1]->node2) == 0) usedNodes.push_back(sortEdges[i]->node2);
            }
        }
        

        ofstream outputFile("output.txt", ios_base::trunc);

        if (!outputFile.is_open()) {
            cerr << "Output File doesn't open" << endl;
        }
        usedNodes.clear();
        int count = 0;
        outputFile << "Минмальное остовное дерево:" << endl;
        for (int i = 0; i < SkeletonEdges.size(); i++) {
            outputFile << SkeletonEdges[i]->node1 << " " << SkeletonEdges[i]->node2 << endl;
            count += SkeletonEdges[i]->weight;
        }
        outputFile << "Вес остова: " << count << endl;
        outputFile.close();
    }
};

int main() {
    setlocale(0, "");
    Graph Obj;
    Obj.CreateGraph();
    Obj.KruskalAlgorithm();

}