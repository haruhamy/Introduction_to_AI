#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n;    // Ma tran co n x n cot
int u, v; // Dinh ket thuc
int s, t; // Dinh bat dau
char h[1001][1001];

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
char duy[4] = {'x', 'o', 'o', 'o'};
char bando[1001][1001];

int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}
int manhattan_distance(int x1, int x2, int y1, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
bool cmp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{ // sort f(x) tu tot nhat den xau nhat
    return a.second.second < b.second.second;
}
void inp()
{
    n = random(20, 70);
    cout << "Ma tran co: " << n << " x " << n << " \n";
    srand((int)time(0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int r = random(0, 3);
            h[i][j] = duy[r];
        }
    }
    int ax = random(1, n);
    int ay = random(1, n);
    int bx = random(1, n);
    int by = random(1, n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            h[ax][ay] = 'A';
            h[bx][by] = 'B';
            if (h[i][j] == 'A')
            {
                s = i;
                t = j; // Đỉnh bắt đầu
            }
            else if (h[i][j] == 'B')
            {
                u = i;
                v = j; // Đỉnh kết thúc
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << h[i][j] << " ";
        }
        cout << endl;
    }
}
void branch_and_bound(int s, int t, int u, int v)
{
    int p = random(50, 189);
    clock_t start, end; // khai bao bien thoi gian
    double time_use;    // thoi gian se in ra
    start = clock();    // thoi gian bat dau
    bool visited[n + 1][n + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            visited[i][j] = false;
        }
    }
    int cost = 1e6;                                    // Khoi tao cost vo cung lon
    int z = 0;                                         // bien check
    vector<pair<pair<int, int>, pair<int, int>>> open; // danh sach open luu dinh, ham g(x), f(x) cua dinh
    map<pair<int, int>, pair<int, int>> father;        // key: dinh, dinh truoc do, ham f(con)
    vector<pair<pair<int, int>, pair<int, int>>> cl;
    open.push_back({{s, t}, {0, manhattan_distance(s, u, t, v)}}); // s, t, g(A), f(A)
    cl.push_back({{s, t}, {0, manhattan_distance(s, u, t, v)}});
    visited[s][t] = true; // danh dau da tham
    int cnt = p;
    while (!open.empty())
    {
        cnt++;
        pair<pair<int, int>, pair<int, int>> o = open[0]; // Lay phan tu dau hang doi
        pair<pair<int, int>, pair<int, int>> x = cl[0];
        visited[x.first.first][x.first.second] = true; // danh dau la da tham
        open.erase(open.begin());                      // Xoa phan tu do di
        cl.erase(cl.begin());
        cout << "Nut xet thu " << cnt << ": " << endl;
        cout << o.first.first << " " << o.first.second << " ";
        cout << "Ham g(x): " << o.second.first << " Ham f(x): " << o.second.second << endl;
        if (x.first.first == u && x.first.second == v && x.second.first <= cost)
        {          // neu bang dinh ket thuc
            z = 1; // Tim kiem thanh cong
            cost = x.second.first;
            break;
        }
        else
        {
            if (x.second.second > cost)
                continue;                                     // f(x) > cost
            vector<pair<pair<int, int>, pair<int, int>>> tmp; // danh sach tmp
            for (int k = 0; k < 4; k++)
            {
                int i1 = x.first.first + dx[k];
                int j1 = x.first.second + dy[k];
                if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= n && h[i1][j1] != 'x' && !visited[i1][j1])
                {
                    pair<pair<int, int>, pair<int, int>> y;
                    y.first.first = i1;
                    y.first.second = j1;
                    y.second.first = x.second.first + 1;                                                        // g(y) = g(x) + k(x, y)
                    y.second.second = y.second.first + manhattan_distance(y.first.first, u, y.first.second, v); // f(y) = g(y) + h(y);
                    visited[i1][j1] = true;
                    cl.push_back(y);
                    tmp.push_back(y);
                    father[{y.first.first, y.first.second}] = {x.first.first, x.first.second};
                }
            }
            sort(tmp.begin(), tmp.end(), cmp);
            for (int i = 0; i < tmp.size(); i++)
            {
                open.insert(open.begin() + i, tmp[i]);
            }
            sort(cl.begin(), cl.end(), cmp);
        }
    }
    cout << endl;
    if (z == 0)
    {
        cout << "Khong ton tai duong di tu A den B \n";
    }
    else
    {
        vector<pair<int, int>> path;
        path.push_back({u, v});
        pair<int, int> current = {u, v};
        while (current != pair<int, int>(s, t))
        {
            current = father[current];
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        cout << "Do dai duong di ngan nhat la: ";
        cout << path.size() << "\n";
        for (auto p : path)
        {
            cout << "hang thu: " << p.first << " "
                 << "cot thu: " << p.second << " " << endl;
        }
        cout << "Ma tran ban dau la: \n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << h[i][j];
                bando[i][j] = h[i][j];
            }
            cout << endl;
        }
        for (auto p : path)
        {
            if (p.first == s && p.second == t)
                continue;
            if (p.first == u && p.second == v)
                continue;
            bando[p.first][p.second] = '-';
        }
        cout << "Ma tran duong di ngan nhat la: \n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << bando[i][j] << " ";
            }
            cout << endl;
        }
    }
    end = clock(); // thoi gian ket thuc
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Thoi gian chay la: " << time_use << endl;
}
void A_star_search(int s, int t, int u, int v)
{
    clock_t start, end; // khai bao bien thoi gian
    double time_use;    // thoi gian se in ra
    start = clock();    // thoi gian bat dau
    int z = 0;          // Bien check
    bool visited[n + 1][n + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            visited[i][j] = false;
        }
    }
    vector<pair<pair<int, int>, pair<int, int>>> open; // danh sach open luu dinh, ham g(x), f(x) cua dinh
    map<pair<int, int>, pair<int, int>> father;
    open.push_back({{s, t}, {0, manhattan_distance(s, u, t, v)}});
    visited[s][t] = true;
    int cnt = 0;
    while (!open.empty())
    {
        cnt++;
        pair<pair<int, int>, pair<int, int>> x = open[0]; // Lay phan tu dau hang doi
        visited[x.first.first][x.first.second] = true;    // danh dau la da tham
        cout << "Nut xet thu " << cnt << ": " << endl;
        cout << x.first.first << " " << x.first.second << " ";
        cout << "Ham g(x): " << x.second.first << " Ham f(x): " << x.second.second << endl;
        open.erase(open.begin()); // Xoa phan tu do di
        if (x.first.first == u && x.first.second == v)
        {          // neu bang dinh ket thuc
            z = 1; // Tim kiem thanh cong
            break;
        }
        else
        {
            for (int k = 0; k < 4; k++)
            {
                int i1 = x.first.first + dx[k];
                int j1 = x.first.second + dy[k];
                if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= n && h[i1][j1] != 'x' && !visited[i1][j1])
                {
                    pair<pair<int, int>, pair<int, int>> y;
                    y.first.first = i1;
                    y.first.second = j1;
                    y.second.first = x.second.first + 1;                                                        // g(y) = g(x) + k(x, y)
                    y.second.second = y.second.first + manhattan_distance(y.first.first, u, y.first.second, v); // f(y) = g(y) + h(y);
                    open.push_back(y);
                    father[{y.first.first, y.first.second}] = {x.first.first, x.first.second};
                    visited[i1][j1] = true;
                }
            }
            sort(open.begin(), open.end(), cmp);
        }
    }
    cout << endl;
    if (z == 0)
    {
        cout << "Khong ton tai duong di tu A den B \n";
    }
    else
    {
        vector<pair<int, int>> path;
        path.push_back({u, v});
        pair<int, int> current = {u, v};
        while (current != pair<int, int>(s, t))
        {
            current = father[current];
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        cout << "Do dai duong di ngan nhat la: ";
        cout << path.size() << "\n";
        for (auto p : path)
        {
            cout << "hang thu: " << p.first << " "
                 << "cot thu: " << p.second << " " << endl;
        }
        cout << "Ma tran ban dau la: \n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << h[i][j];
                bando[i][j] = h[i][j];
            }
            cout << endl;
        }
        for (auto p : path)
        {
            if (p.first == s && p.second == t)
                continue;
            if (p.first == u && p.second == v)
                continue;
            bando[p.first][p.second] = '-';
        }
        cout << "Ma tran duong di ngan nhat la: \n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << bando[i][j] << " ";
            }
            cout << endl;
        }
    }
    end = clock(); // thoi gian ket thuc
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Thoi gian chay la: " << time_use << endl;
}

int main()
{
    while (1)
    {
        cout << "---------------MENU--------------" << endl;
        cout << "0. Bat dau tao ma tran \n";
        cout << "1. Bat dau nhanh can \n";
        cout << "2. Bat dau A* \n";
        cout << "3. Ket thuc \n";
        cout << "Moi nhap lua chon: ";
        int lc;
        cin >> lc;
        if (lc == 0)
        {
            inp();
        }
        else if (lc == 1)
        {
            branch_and_bound(s, t, u, v);
        }
        else if (lc == 2)
        {
            A_star_search(s, t, u, v);
        }
        else
        {
            break;
        }
    }
    return 0;
}
