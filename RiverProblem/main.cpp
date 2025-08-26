#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> grid, visited;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m
           && grid[x][y] == 0 && !visited[x][y];
}

int bfs(pair<int,int> start, pair<int,int> goal) {
    queue<pair<int,int>> q;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    visited.assign(n, vector<int>(m, 0));

    q.push(start);
    visited[start.first][start.second] = 1;
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        pair<int,int> cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;

        if (x == goal.first && y == goal.second)
            return dist[x][y];

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny)) {
                visited[nx][ny] = 1;
                dist[nx][ny] = dist[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    return -1;
}

int main() {
    n = 5; m = 5;
    grid = {
        {0,1,0,0,0},
        {0,1,0,1,0},
        {0,0,0,1,0},
        {1,1,0,1,0},
        {0,0,0,0,0}
    };

    int result = bfs({0,0}, {4,4});
    if (result != -1) cout << "Shortest path length: " << result << "\n";
    else cout << "No path exists!\n";
    return 0;
}
