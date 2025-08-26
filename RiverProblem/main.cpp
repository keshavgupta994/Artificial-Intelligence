#include <bits/stdc++.h>
using namespace std;

int n, m; // grid size
vector<vector<int>> grid;
vector<vector<int>> visited;

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0 && !visited[x][y]);
}

int bfs(pair<int,int> start, pair<int,int> goal) {
    queue<pair<int,int>> q;
    visited[start.first][start.second] = 1;
    q.push(start);

    // distance matrix to track shortest path length
    vector<vector<int>> dist(n, vector<int>(m, -1));
    dist[start.first][start.second] = 0;

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == goal.first && y == goal.second) {
            return dist[x][y]; // shortest distance found
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny)) {
                visited[nx][ny] = 1;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1; // no path found
}

int main() {
    // Example grid
    n = 5, m = 5;
    grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    visited.assign(n, vector<int>(m, 0));

    pair<int,int> start = {0, 0};
    pair<int,int> goal = {4, 4};

    int result = bfs(start, goal);

    if(result != -1) cout << "Shortest path length: " << result << endl;
    else cout << "No path exists!" << endl;

    return 0;
}
