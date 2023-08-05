
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
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
    int vert_out;
    int vert_in;
    int weight;
    int time;
};

int main(void) {
    int n, m;
    cin >> n >> m;

    vector<edge> edge_list;
    int a, b, time_cur;
    long weight_cur_long;
    vector<int> weight_sorted;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> time_cur >> weight_cur_long;
        //нормализация весов по количеству кружек
        int weight_cur = (weight_cur_long - 3000000) / 100;
        weight_sorted.push_back(weight_cur);
        --a;
        --b;

        edge cur;
        cur.vert_out = a;
        cur.vert_in = b;
        cur.weight = weight_cur;
        cur.time = time_cur;

        edge_list.emplace_back(cur);
    }
    sort(weight_sorted.begin(), weight_sorted.end());
    auto last = unique(weight_sorted.begin(), weight_sorted.end());
    weight_sorted.erase(last, weight_sorted.end());

    //Начинаем бин поиск

    int l = 0;
    int r = weight_sorted.size();
    int mid;

    if (r == 0) {
        r = 1;
        weight_sorted.push_back(10000000);
    }

    if (true) {
        bool path_exist = false;

        // Строим подграф
        vector<vector<pair<int,int>>> graph(n);
        for (size_t i = 0; i < edge_list.size(); ++i) {
            if (edge_list[i].weight >= weight_sorted[0]) {
                graph[edge_list[i].vert_out].emplace_back(make_pair(edge_list[i].vert_in, edge_list[i].time));
                graph[edge_list[i].vert_in].emplace_back(make_pair(edge_list[i].vert_out, edge_list[i].time));
            }
        }

        // Дейкстра по минимальному времени
        int start = 0;
        vector<int> time(n, 1441);
        time[start] = 0;
        priority_queue<pair<int,int>> queue;
        queue.push(make_pair(0, start));
        while (!queue.empty()) {
            int v = queue.top().second,  cur_t = -queue.top().first;
            queue.pop();
            if (cur_t > time[v])  continue;
            for (size_t j = 0; j < graph[v].size(); ++j) {
                int to = graph[v][j].first,
                    len = graph[v][j].second;
                if (time[v] + len < time[to]) {
                    time[to] = time[v] + len;
                    queue.push (make_pair (-time[to], to));
                }
            }
        }

        if (time[n - 1] < 1441)
            path_exist = true;

        // Если не существует пути в исходном графе - ответ 0
        if (!path_exist) {
            cout << 0 << endl;
            return 0;
        }
    }

    // Основной цикл бин поиска
    while (r - l != 1) {
        mid = (l + r) / 2;

        bool path_exist = false;

        // Строим подграф
        vector<vector<pair<int,int>>> graph(n);
        for (size_t i = 0; i < edge_list.size(); ++i) {
            if (edge_list[i].weight >= weight_sorted[mid]) {
                graph[edge_list[i].vert_out].emplace_back(make_pair(edge_list[i].vert_in, edge_list[i].time));
                graph[edge_list[i].vert_in].emplace_back(make_pair(edge_list[i].vert_out, edge_list[i].time));
            }
        }

        // Дейкстра по минимальному времени
        int start = 0;
        vector<int> time(n, 1441);
        time[start] = 0;
        priority_queue<pair<int,int>> queue;
        queue.push(make_pair(0, start));
        while (!queue.empty()) {
            int v = queue.top().second,  cur_t = -queue.top().first;
            queue.pop();
            if (cur_t > time[v])  continue;
            for (size_t j = 0; j < graph[v].size(); ++j) {
                int to = graph[v][j].first,
                    len = graph[v][j].second;
                if (time[v] + len < time[to]) {
                    time[to] = time[v] + len;
                    queue.push (make_pair (-time[to], to));
                }
            }
        }

        if (time[n - 1] < 1441)
            path_exist = true;

        // Сдвигаем границы бин поиска
        // Если нашли путь длиною меньше 24 часа значит
        // сдвигаем левую границу к середине отрезка, иначе правую
        if (path_exist)
            l = mid;
        else
            r = mid;
    }

    // Выводим неотрицательный результат бин поиска
    if (weight_sorted[l] >= 0)
        cout << weight_sorted[l] << endl;
    else
        cout << 0 << endl;
    return 0;
}