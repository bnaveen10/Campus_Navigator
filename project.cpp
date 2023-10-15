#include <bits/stdc++.h>
using namespace std;

// List of different locations in Sreenidhi Institute of Science and Technology
vector<string> nodes = {
    "College Gate", "Pole", "Canteen", "Admin Block", "First Year Block", "Ground", "Stationary", "Library", "CSE Block", "ECE Block", "Drawing Lab", "FSD Lab",
    "Parking", "Comfort Hostel", "Dhruv Hostel", "Joyz Pizza", "Reddy's Hostel", "RTC Bus stop", "Picnic Restaurant", "University Building"};

void print()
{
    int maxItemWidth = 0;
    for (string &item : nodes)
    {
        maxItemWidth = max(maxItemWidth, static_cast<int>(item.length()));
    }

    cout << "=======================~ CAMPUS NAVIGATOR ~=======================" << endl;
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (i < 9)
            cout << "!  " << i + 1 << ". " << nodes[i] << string(59 - nodes[i].length(), ' ') << "!" << endl;
        else
            cout << "!  " << i + 1 << ". " << nodes[i] << string(58 - nodes[i].length(), ' ') << "!" << endl;
    }
    cout << endl;
}

string direction(int d)
{
    if (d == 1)
        return "towards North";
    else if (d == -1)
        return "towards South ";
    else if (d == 2)
        return "towards East ";
    else
        return "towards West ";
}

void dijkstra(vector<vector<pair<int, int>>> &graph, int source, int destination, vector<unordered_map<int, int>> d)
{
    int numNodes = graph.size();

    vector<int> distance(numNodes, 10000);
    vector<bool> visited(numNodes, false);
    vector<int> previous(numNodes, -1); // Store the previous node in the shortest path

    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, source});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        if (u == destination)
            break;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if ((!visited[v]) && (distance[u] + weight < distance[v]))
            {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    stack<int> path;
    stack<int> dist;
    stack<int> dir;
    int current = destination;
    while (current != -1)
    {
        if (current != source)
        {
            dist.push((distance[current] - distance[previous[current]]));
            dir.push(d[previous[current]][current]);
        }
        path.push(current);
        current = previous[current];
    }
    cout << endl;
    cout << " ==> "
         << "Shortest Distance between " << nodes[source] << " and " << nodes[destination] << " : " << distance[destination] << " meters" << endl
         << endl;
    cout << " ==> "
         << "Shortest path: " << endl
         << endl;
    int x = 0;
    while (!path.empty())
    {
        cout << nodes[path.top()];
        if (path.top() != destination)
        {
            cout << "( " << direction(dir.top()) << " " << dist.top() << " meters"
                 << ")";
        }
        dist.pop();
        dir.pop();
        path.pop();
        if (!path.empty())
        {
            cout << " --> ";
        } 
        if (x == 2)
        {
            cout << endl<<endl;
            x = -1;
        }
        x++;
    }
    cout << endl
         << endl;
}

int main()
{
    vector<vector<pair<int, int>>> map;
    int source, destination;
    map = {
        {{12, 30}, {1, 20}, {13, 200}},
        {{9, 20}, {3, 10}, {2, 10}, {0, 20}},
        {{1, 10}, {4, 5}},
        {{1, 10}, {8, 10}, {9, 20}, {7, 30}},
        {{5, 10}, {8, 5}, {2, 5}},
        {{11, 20}, {6, 20}, {7, 20}, {4, 10}},
        {{5, 20}, {7, 10}, {10, 10}},
        {{6, 10}, {9, 10}, {19, 10}, {3, 30}, {5, 20}},
        {{7, 10}, {3, 10}, {4, 5}},
        {{1, 20}, {3, 20}, {19, 10}},
        {{6, 10}, {11, 15}},
        {{10, 15}, {5, 20}},
        {{0, 30}},
        {{0, 200}, {15, 300}, {14, 200}},
        {{15, 200}, {13, 200}, {16, 600}},
        {{14, 200}, {13, 300}, {17, 400}},
        {{14, 600}, {17, 150}},
        {{18, 500}, {16, 150}, {15, 400}},
        {{17, 500}},
        {{9, 10}, {7, 30}}};
    vector<unordered_map<int, int>> d = {
        {{12, -2}, {1, 1}, {13, -2}},
        {{9, -2}, {3, 1}, {2, 2}, {0, -1}},
        {{1, -1}, {4, 1}},
        {{1, -1}, {8, 2}, {9, -2}, {7, 1}},
        {{5, 1}, {8, -2}, {2, -1}},
        {{11, 1}, {6, -2}, {7, -2}, {4, 1}},
        {{5, 2}, {7, -1}, {10, 1}},
        {{6, 1}, {9, 2}, {19, -2}, {3, -1}, {5, 2}},
        {{7, -2}, {3, -2}, {4, 2}},
        {{1, -1}, {3, 2}, {19, 1}, {12, 1}},
        {{6, -1}, {11, 2}},
        {{10, -2}, {5, -1}},
        {{0, 2}, {9, -1}},
        {{0, 2}, {15, -2}, {14, 1}},
        {{15, -2}, {13, -1}, {16, 1}},
        {{14, 2}, {13, 2}, {17, 1}},
        {{14, -1}, {17, -2}},
        {{18, 1}, {16, 2}, {15, -1}},
        {{17, 1}},
        {{9, -1}, {7, 2}}};
    print();

    while (true)
    {
        cout << " >>> Enter the source and destination blocks:";
        cin >> source;
        cin >> destination;
        if (source == 0 || destination == 0)
            break;
        cout << endl;
        dijkstra(map, source - 1, destination - 1, d);
    }
}
