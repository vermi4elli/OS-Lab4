#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Vertice {
	vector<int> children;
	vector<int> predeccessors;
	int weight;
	int criticalTime;

public:
	Vertice(int weight)
	{
		this->weight = weight;
		this->criticalTime = -1;
	}
	void AddChild(int child) {
		children.push_back(child);
	}
	vector<int> GetChildren() {
		return children;
	}
	vector<int> GetPreds() {
		return predeccessors;
	}
	int GetWeight() {
		return weight;
	}
	int GetCriticalTime() {
		return criticalTime;
	}
	void AddPred(int pred) {
		predeccessors.push_back(pred);
	}
	void SetCriticalTime(int crit) {
		criticalTime = crit;
	}
};

class Graph {
	int verticesAmount;
	Vertice* start, * end;
	vector<Vertice*> vertices;
public:
	Graph(vector<int> verticeWeights)
	{
		this->verticesAmount = verticeWeights.size();

		for (const auto& v : verticeWeights) {
			this->vertices.push_back(new Vertice(v));
		}

		start = vertices.front();
		end = vertices.back();
	}
	Graph(int verticesAmount)
	{
		this->verticesAmount = verticesAmount;

		this->vertices.push_back(new Vertice(0)); // the beginning node
		for (int i = verticesAmount - 2; i > 0; i--)
		{
			this->vertices.push_back(new Vertice(rand() % 7 + 1));
		}
		this->vertices.push_back(new Vertice(0)); // the end node

		start = vertices.front();
		end = vertices.back();
	}
	void AddEdge(int startV, int finishV) {
		vertices[startV]->AddChild(finishV);
		vertices[finishV]->AddPred(startV);
	}
	int GetSize() {
		return verticesAmount;
	}
	vector<Vertice*> GetVertices() {
		return vertices;
	}
	void PrintGraph() {
		cout << "\n" << endl;
		for (int i = 0; i < verticesAmount; i++) {
			cout << "The vertice #" << i << "; Weight: " << vertices[i]->GetWeight() <<
				"; Critical weight: " << (vertices[i]->GetCriticalTime() == -1 ?
					"not found yet..." :
					to_string(vertices[i]->GetCriticalTime())) << endl;
			for (const auto& v : vertices[i]->GetChildren()) {
				cout << "===> #" << v << "; Critical weight: " << (vertices[v]->GetCriticalTime() == -1 ?
					"not found yet..." :
					to_string(vertices[v]->GetCriticalTime())) << endl;
			}
		}
		cout << "\n" << endl;
	}
	void CalculateVerticeCriticalTime(int v) {
		int crit_temp = vertices[v]->GetWeight();
		
		// check if the children of that node are critical-time-checked'r'not
		if (!vertices[v]->GetChildren().empty()) {
			for (const auto& v_temp : vertices[v]->GetChildren()) {
				if (vertices[v_temp]->GetCriticalTime() == -1) {
					CalculateVerticeCriticalTime(v_temp);
				}
			}

			vector<int> sortedCritical = vertices[v]->GetChildren();
			sort(sortedCritical.begin(), sortedCritical.end(), [this](int a, int b) {
				return vertices[a]->GetCriticalTime() > vertices[b]->GetCriticalTime();
			});
			crit_temp = sortedCritical.empty() ?
				crit_temp :
				crit_temp + vertices[*sortedCritical.begin()]->GetCriticalTime();
		}

		
		vertices[v]->SetCriticalTime(crit_temp);

		if (!vertices[v]->GetPreds().empty()) {
			for (const auto& v_temp : vertices[v]->GetPreds()) {
				if (vertices[v_temp]->GetCriticalTime() == -1) {
					CalculateVerticeCriticalTime(v_temp);
				}
			}
		}
	}
	void PrintCriticalPath(int v) {
		if (vertices[v]->GetChildren().empty()) {
			cout << v << endl;
		}
		else {
			vector<int> sortedCritical = vertices[v]->GetChildren();
			sort(sortedCritical.begin(), sortedCritical.end(), [this](int a, int b) {
				return vertices[a]->GetCriticalTime() > vertices[b]->GetCriticalTime();
			});
			cout << v << " -> ";
			PrintCriticalPath(*sortedCritical.begin());
		}
	}
};

void Example1() {
	Graph graph({ 0, 2, 3, 4, 0 });
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(1, 3);
	graph.AddEdge(2, 3);
	graph.AddEdge(3, 4);
	graph.PrintGraph();
	graph.CalculateVerticeCriticalTime(graph.GetSize() - 1);
	graph.PrintGraph();
	graph.PrintCriticalPath(0);
}
void Example2() {
	Graph graph({ 0, 5, 3, 2, 4, 6, 4, 3, 0 });
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(0, 3);
	graph.AddEdge(1, 4);
	graph.AddEdge(2, 4);
	graph.AddEdge(2, 5);
	graph.AddEdge(3, 5);
	graph.AddEdge(4, 6);
	graph.AddEdge(5, 6);
	graph.AddEdge(5, 7);
	graph.AddEdge(6, 8);
	graph.AddEdge(7, 8);
	graph.PrintGraph();
	graph.CalculateVerticeCriticalTime(graph.GetSize() - 1);
	graph.PrintGraph();
	graph.PrintCriticalPath(0);
}

int main() {
	//Example1();
	Example2();

	return 0;
}
