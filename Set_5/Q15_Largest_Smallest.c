#include <stdio.h>

#define INF 9999

int graph[20][20];
int n;

int path[20];
int inPath[20];

int minCycle = INF;
int maxCycle = 0;

void findCycles(int start, int u, int depth)
{
    int v;

    path[depth] = u;
    inPath[u] = 1;

    for(v = 0; v < n; v++)
    {
        if(graph[u][v] == 0)
            continue;

        if(v == start && depth >= 2)
        {
            int length = depth + 1;

            if(length < minCycle)
                minCycle = length;

            if(length > maxCycle)
                maxCycle = length;
        }
        else if(!inPath[v])
        {
            findCycles(start, v, depth + 1);
        }
    }

    inPath[u] = 0;
}

void largestSmallestCycle()
{
    int i;

    minCycle = INF;
    maxCycle = 0;

    for(i = 0; i < n; i++)
        inPath[i] = 0;

    for(i = 0; i < n; i++)
        findCycles(i, i, 0);

    if(maxCycle == 0)
        printf("No cycle exists\n");
    else
    {
        printf("Smallest cycle = %d\n", minCycle);
        printf("Largest cycle = %d\n", maxCycle);
    }
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    largestSmallestCycle();

    return 0;
}