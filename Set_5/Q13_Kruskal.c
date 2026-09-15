#include <stdio.h>

struct Edge
{
    int u, v, weight;
};

int parent[20];

int find(int x)
{
    if (parent[x] == x)
        return x;

    return find(parent[x]);
}

void sortEdges(struct Edge edges[], int e)
{
    struct Edge temp;
    int i, j;

    for (i = 0; i < e - 1; i++)
    {
        for (j = 0; j < e - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskal(struct Edge edges[], int e, int n)
{
    int i, count = 0;
    int u, v;

    for (i = 0; i < n; i++)
        parent[i] = i;

    sortEdges(edges, e);

    printf("Minimum Spanning Tree:\n");

    for (i = 0; i < e && count < n - 1; i++)
    {
        u = find(edges[i].u);
        v = find(edges[i].v);

        if (u != v)
        {
            printf("%d - %d : %d\n",
                   edges[i].u,
                   edges[i].v,
                   edges[i].weight);

            parent[u] = v;
            count++;
        }
    }
}

int main()
{
    struct Edge edges[20];
    int n, e, i;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v weight):\n");

    for (i = 0; i < e; i++)
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].weight);

    kruskal(edges, e, n);

    return 0;
}