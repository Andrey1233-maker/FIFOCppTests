// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>

using namespace std;

#define matrix vector<vector<int>>

matrix readMatrix() {
    setlocale(LC_ALL, "Russian");

    try {
        int pointCount, linkCount;
        cout << "Введите количество вершин: ";
        cin >> pointCount;

        cout << "\nВведите количесвто рёбер: ";
        cin >> linkCount;
        matrix graph(pointCount, vector<int>(pointCount, -1));

        cout << "\nВведите рёбра по шаблону (<начальная вершина> <конечная вершина> <длина>): ";
        for (int i = 0; i < linkCount; i++) {
            int start, end, leight;
            cout << "\n " << i << ": ";
            cin >> start >> end >> leight;

            if (start >= pointCount) { throw exception("Недопустимая стартовая точка"); }
            if (end >= pointCount) { throw exception("Недопустимая стартовая точка"); }
            if (leight <= 0) { throw exception("Недопустимая длина маршрута"); }
            
            graph[start][end] = leight;
            graph[end][start] = leight;
        }

        return graph;
    }
    catch (exception e) {
        throw e;
    }
}


vector<bool> graphBreadthFirstSearch(matrix graph) {
    queue<int> q;
    vector<bool> result(graph.size(), false);

    q.push(0);
    result[0] = true;

    while (!q.empty()) {
        int currentStart = q.front();
        q.pop();
        for (int i = 0; i < result.size(); i++) {
            if (graph[currentStart][i] > 0 && !result[i]) {
                q.push(i);
                result[i] = true;
            }
        }

    }

    return result;
}

void writeResult(vector<bool> result) {
    bool d = true;
    for (int i = 0; i < result.size(); i++) {
        d = result[i];
        if (!d) {
            cout << "Граф не связный";
            return;
        }
    }
    cout << "Граф связный";
}

int main()
{
    try {
        matrix graph = readMatrix();
        vector<bool> result = graphBreadthFirstSearch(graph);
        writeResult(result);
    }
    catch (exception e) {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(console, FOREGROUND_RED);
        cout << e.what();
        SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        return 0;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
