#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int x, y, cost;
    vector<vector<int>> goal;
};

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int heuristic(vector<vector<int>>& state, vector<vector<int>>& goal) {
    int dist = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state[i][j] != 0) {
                for (int x = 0; x < 3; x++)
                    for (int y = 0; y < 3; y++)
                        if (state[i][j] == goal[x][y])
                            dist += abs(i - x) + abs(j - y);
            }
    return dist;
}

bool isGoal(vector<vector<int>>& a, vector<vector<int>>& b) {
    return a == b;
}

struct PQCompare {
    bool operator()(const pair<int, Node>& a, const pair<int, Node>& b) const {
        return a.first > b.first; 
    }
};

void solve(vector<vector<int>> start, vector<vector<int>> goal) {
    priority_queue<pair<int, Node>, vector<pair<int, Node>>, PQCompare> pq;

    int x = 0, y = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (start[i][j] == 0) { x = i; y = j; }

    int hstart = heuristic(start, goal);
    Node startNode = {start, x, y, hstart, goal};
    pq.push(make_pair(hstart, startNode));

    set<vector<vector<int>>> visited;
    while (!pq.empty()) {
        auto top = pq.top(); 
        pq.pop();
        int h = top.first;
        Node node = top.second;

        if (isGoal(node.state, goal)) {
            for (auto& row : node.state) {
                for (int v : row) cout << v << " ";
                cout << "\n";
            }
            return;
        }

        visited.insert(node.state);

        for (int i = 0; i < 4; i++) {
            int nx = node.x + dx[i], ny = node.y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3) {
                auto newState = node.state;
                swap(newState[node.x][node.y], newState[nx][ny]);
                if (!visited.count(newState)) {
                    int hval = heuristic(newState, goal);
                    Node newNode = {newState, nx, ny, hval, goal};
                    pq.push(make_pair(hval, newNode));
                }
            }
        }
    }

    cout << "No solution found\n";
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {4, 0, 6}, {7, 5, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    solve(start, goal);
    return 0;
}
