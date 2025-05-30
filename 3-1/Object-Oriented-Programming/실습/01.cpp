#include <bits/stdc++.h>
using namespace std;

struct Node { int z, y, x; };          // 한 칸의 좌표

const int MAX = 100;
int box_[MAX][MAX][MAX];               // 0: 안 익음, 1: 익음, -1: 빈 칸
int dz[6] = { 1, -1, 0, 0, 0, 0 };
int dy[6] = { 0, 0, 1, -1, 0, 0 };
int dx[6] = { 0, 0, 0, 0, 1, -1 };

int m, n, h;                           // m: 가로, n: 세로, h: 높이

int bfs() {
    queue<Node> q;
    for (int z = 0; z < h; ++z)
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                if (box_[z][y][x] == 1)
                    q.push({z, y, x}); // 다중 시작점

    int days = 0;
    while (!q.empty()) {
        int qs = q.size();
        while (qs--) {
            auto [z, y, x] = q.front();
            q.pop();
            for (int dir = 0; dir < 6; ++dir) {
                int nz = z + dz[dir], ny = y + dy[dir], nx = x + dx[dir];
                if (nz < 0 || nz >= h || ny < 0 || ny >= n || nx < 0 || nx >= m)
                    continue;
                if (box_[nz][ny][nx] == 0) {
                    box_[nz][ny][nx] = 1;
                    q.push({nz, ny, nx});
                }
            }
        }
        if (!q.empty())
             ++days;        // 다음 레벨(하루) 존재 시 날짜++ 
    }

    return days;
}

void solve() {
    if (!(cin >> m >> n >> h)) 
        return;

    for (int z = 0; z < h; ++z)
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                cin >> box_[z][y][x];

    int ans = bfs();

    // 아직 0(안 익은 토마토) 남아 있으면 실패
    for (int z = 0; z < h; ++z)
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                if (box_[z][y][x] == 0) {
                    cout << -1 << '\n';
                    return;
                }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
