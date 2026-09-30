#include <stdio.h>

int graph[20][20];
int n;

int visited[20];
int disc[20], low[20];
int parent[20];
int timer;

void connectedComponents()
{
    int i, j, count = 0;

    for(i = 0; i < n; i++)
        visited[i] = 0;

    for(i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            count++;

            printf("Component %d: ", count);

            for(j = 0; j < n; j++)
            {
                if(graph[i][j] && !visited[j])
                {
                    visited[j] = 1;
                    printf("%d ", j);
                }
            }

            printf("\n");
        }
    }
}

void DFS(int u)
{
    int v;

    visited[u] = 1;
    disc[u] = low[u] = ++timer;

    for(v = 0; v < n; v++)
    {
        if(!graph[u][v])
            continue;

        if(!visited[v])
        {
            parent[v] = u;

            DFS(v);

            if(low[v] < low[u])
                low[u] = low[v];

            if(parent[u] == -1 && disc[v] > 1)
                printf("Articulation Point: %d\n", u);

            if(parent[u] != -1 && low[v] >= disc[u])
                printf("Articulation Point: %d\n", u);

            if(low[v] > disc[u])
                printf("Bridge: %d - %d\n", u, v);
        }
        else if(v != parent[u])
        {
            if(disc[v] < low[u])
                low[u] = disc[v];
        }
    }
}

void findBiconnected()
{
    int i;

    for(i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        disc[i] = 0;
        low[i] = 0;
    }

    timer = 0;

    for(i = 0; i < n; i++)
    {
        if(!visited[i])
            DFS(i);
    }
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }

    printf("\nConnected Components:\n");
    connectedComponents();

    printf("\nArticulation Points and Bridges:\n");
    findBiconnected();

    return 0;
}