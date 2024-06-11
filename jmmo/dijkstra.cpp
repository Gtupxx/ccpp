/*
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-07-03 17:16:58
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-07-03 17:26:04
 * @FilePath: \ccpp\jmmo\dijkstra.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define MAXN 9      // 最大顶点数
#define INF 999999// 无穷大

float G[MAXN][MAXN] = {
    {0, 2, 2, 2, 2, 2, 2, 2, 1},
    {2, 0, 0.5, 2, 2, 2, 1, 2, 2},
    {2, 0, 0, INF, 2, 2, 0, 2, 1},
    {2, INF, INF, 0, 0, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 2, 1, 2, 0},
    {INF, INF, INF, INF, 1, 0, 2, 2, 2},
    {INF, 1, 1, INF, 1, 2, 0, 2, 1},
    {INF, 2, 2, 2, 2, 2, 2, 0, 2},
    {0, 0, 0, 0, 0, 2, 1, 2, 0}}; // 邻接矩阵表示的图

float dist[MAXN];     // 最短路径长度
bool visited[MAXN]; // 是否已访问

void dijkstra(int s)
{ // s为起点
    fill(dist, dist + MAXN, INF);
    fill(visited, visited + MAXN, false);
    dist[s] = 0;

    for (int i = 0; i < MAXN; i++)
    {
        int u = -1;
        for (int j = 0; j < MAXN; j++)
        {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }
        if (dist[u] == INF)
            break;
        visited[u] = true;

        for (int v = 0; v < MAXN; v++)
        {
            if (G[u][v] != INF && !visited[v] && dist[v] > dist[u] + G[u][v])
            {
                dist[v] = dist[u] + G[u][v];
            }
        }
    }
}

int main()
{
    for (int s = 0; s < 9; s++)
    {

        dijkstra(s);
        // 输出最短路径长度
        for (int i = 0; i < MAXN; i++)
        {
            if (dist[i] == INF)
            {
                cout << "INF" << '\t';
            }
            else
            {
                cout << dist[i] << '\t';
            }
        }
        cout << std::endl;
    }

    return 0;
}