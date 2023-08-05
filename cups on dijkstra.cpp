
// Формализация задачи:
// Дан взевешенный (максимально провозимым грузом) неориентированный граф, и время прохождения каждого ребра.
// Необходимо найти какой максимальный груз можно провезти из начальной вершины в конечную, с учётом глобального ограничения на время Т.
// Вход:
// Граф, начальная и конечная вершина, вес каждого ребра (w_i), время прохождения каждого ребра (t_i) и глобальное ограничение на время T.

// Управление:
// Путь

// Допустимость:
// Время пути(S) < T

// Функционал:
// min(w_i | w_i ∈ S) -> max

// Описание алгоритма:
// Для ответа строим фронтальный обход, с выбором ведущей вершины, которая имеет максимальный вес. (Алгоритм Дейкстры)

// Трудоёмкость:
// Поскольку в реализации Дейкстры используется очередь с приоритетом — трудоёмкость O(m * log(n)).



#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

struct edge {
    int vert;
    int weight;
    int time;
};

class IGraph {
public:
    IGraph(int n) {
        graph.resize(n);
        for (int i = 0; i < n; i++) {
            graph[i].resize(0);
        }
    }
 
    int get_weight(int x, int y) {
        return graph[x][y].weight;
    }          // получение пропускной способности между городами

    int get_time(int x, int y) {
        return graph[x][y].time;
    }          // получение времени между городами
 
    void add_edge(int x, int y, int w, int t) {
        edge e;
        e.vert = y;
        e.weight = w;
        e.time = t;
        graph[x].emplace_back(e);
    }          // добавление ребра
 
    vector<int> neighbors(int top) {
        vector<int> res;
        for (size_t i = 0; i < graph[top].size(); i++)
            res.push_back(graph[top][i].vert);
        return res;
    }          // получение связанных городов
 
    int get_number(int x, int y) {
        return graph[x][y].vert;
    }          // получение номера вершины
 
    int neighbors_size(int top) {
        return graph[top].size();
    }          // получение колличества связанных городов
 
private:
    vector<vector<edge>> graph;
};
 
struct Comp {
    bool operator()(edge a, edge b) {
        return a.weight > b.weight;
    }
};
 
int dijkstra(int n, int begin_node, int end_node, IGraph graph) {
    vector<pair<int, int>> max_cups_and_time;
    priority_queue<edge, vector<edge>, Comp> pq;
    max_cups_and_time.resize(n, make_pair(0, 1441));

    max_cups_and_time[begin_node].first = 10000000;    // кружек - максимально возможно
    max_cups_and_time[begin_node].second = 0;          // время до неё самой 0

    edge queue_start_node{begin_node, 10000000, 0};
    pq.push(queue_start_node);
 
    while (!pq.empty()) {
        auto top = pq.top();                      // получили вершину
        pq.pop();                                 // убрали ее из очереди
        int source_node = top.vert;
        int neighbors_size = graph.neighbors_size(source_node);
        if (top.weight < max_cups_and_time[source_node].first)
            continue;
        for (int i = 0; i < neighbors_size; i++) {
            int new_cups = min(max_cups_and_time[source_node].first, graph.get_weight(source_node, i));
            int new_time = max_cups_and_time[source_node].second +  graph.get_time(source_node, i);
            int dest_node = graph.get_number(source_node, i);
            if (new_cups > max_cups_and_time[dest_node].first && new_time < 1441) {
                max_cups_and_time[dest_node].first = new_cups;   // обновление
                max_cups_and_time[dest_node].second = new_time;
                edge new_edg;
                new_edg.vert = dest_node;
                new_edg.weight = new_cups;
                new_edg.time = new_time;
                pq.push(new_edg);
            }
        }
    }
    // вывод максимального количества кружек и весов для всех вершин, а не только для end_node
    // for (int i = 0; i < n; ++i) {
    //     std::cout << std::setw(13) << i + 1;
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < n; ++i) {
    //     std::cout << std::setw(13) << max_cups_and_time[i].first;
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < n; ++i) {
    //     std::cout << std::setw(13) << max_cups_and_time[i].second;
    // }
    // std::cout << std::endl;
    return max_cups_and_time[end_node].first;
}



int main(void) {
    int n, m;
    std::cin >> n >> m;
    
    long a, b;
    long time_cur, weight_cur;
    IGraph graph(n);
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> time_cur >> weight_cur;
        //нормализация весов по количеству кружек
        weight_cur = (weight_cur - 3000000) / 100;
        --a;
        --b;
        graph.add_edge(a, b, weight_cur, time_cur);
        graph.add_edge(b, a, weight_cur, time_cur);
    }

    cout << dijkstra(n, 0, n - 1, graph) << endl;
    return 0;
}