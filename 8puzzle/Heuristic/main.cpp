//8 puzzle problem heuristic approach
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 3;

struct Node 
{
    vector<vector<int>> state;
    int x, y; 
    int g, h;    
};

struct Compare 
{
    bool operator()(Node const &a, Node const &b) 
    {
        return (a.g + a.h) > (b.g + b.h);
    }
};

void printPuzzle(vector<vector<int>> &p) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)
        {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

bool isGoal(vector<vector<int>> &p) 
{
    int cnt = 1;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (i == N-1 && j == N-1)
            {
                return p[i][j] == 0;
            }
            if (p[i][j] != cnt++)
            {
                return false;
            }
        }
    }
    return true;
}

// Heuristic 1: Misplaced tiles
int misplacedTiles(vector<vector<int>> &p) 
{
    int cnt = 0, val = 1;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (i == N-1 && j == N-1)
            {
                continue;
            }
            if (p[i][j] != val)
            {
                cnt++;
            }
            val++;
        }
    }
    return cnt;
}

// Heuristic 2: Matched tiles
int matchedTiles(vector<vector<int>> &p) 
{
    int cnt = 0, val = 1;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (i == N-1 && j == N-1)
            {
                continue;
            }
            if (p[i][j] == val) 
            {
                cnt++;
            }
            val++;
        }
    }
    return (N*N - 1) - cnt;
}

// Heuristic 3: Manhattan Distance
int manhattanDistance(vector<vector<int>> &p) 
{
    int dist = 0;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            int val = p[i][j];
            if (val != 0) 
            {
                int goalX = (val - 1) / N;
                int goalY = (val - 1) % N;
                dist += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return dist;
}

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solveAstar(vector<vector<int>> start, int heuristicChoice) 
{
    priority_queue<Node, vector<Node>, Compare> pq;
    Node root{start, 0, 0, 0, 0};

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (start[i][j] == 0) 
            { 
                root.x = i; 
                root.y = j; 
            }
        }
    }
       

    if (heuristicChoice == 1)
    {
        root.h = misplacedTiles(root.state);
    }
    else if (heuristicChoice == 2) 
    {
        root.h = matchedTiles(root.state);
    }
    else 
    {
        root.h = manhattanDistance(root.state);
    }

    pq.push(root);

    while (!pq.empty()) 
    {
        Node cur = pq.top(); pq.pop();

        printPuzzle(cur.state);

        if (isGoal(cur.state)) 
        {
            cout << "Goal state reached in " << cur.g << " moves!" << endl;
            return;
        }

        for (int k = 0; k < 4; k++) 
        {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) 
            {
                Node next = cur;
                swap(next.state[cur.x][cur.y], next.state[nx][ny]);
                next.x = nx; next.y = ny;
                next.g = cur.g + 1;

                if (heuristicChoice == 1)
                {
                    next.h = misplacedTiles(next.state);
                }
                else if (heuristicChoice == 2) 
                {
                    next.h = matchedTiles(next.state);
                }
                else 
                {
                    next.h = manhattanDistance(next.state);
                }

                pq.push(next);
            }
        }
    }
    cout << "Goal not found." << endl;
}

int main() 
{
    vector<vector<int>> start = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    cout << "Solving using Misplaced Tiles Heuristic:" << endl;
    solveAstar(start, 1);

    cout << "\nSolving using Matched Tiles Heuristic:" << endl;
    solveAstar(start, 2);

    cout << "\nSolving using Manhattan Distance Heuristic:" << endl;
    solveAstar(start, 3);

    return 0;
}