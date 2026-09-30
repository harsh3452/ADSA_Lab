#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define INF 999999

int n;
int graph[MAX][MAX];
int visited[MAX];
int minCost;

void tsp(int city, int count, int cost)
{
    int i;

    if(count == n)
    {
        if(graph[city][0] != 0)
        {
            cost += graph[city][0];

            if(cost < minCost)
                minCost = cost;
        }

        return;
    }

    for(i = 0; i < n; i++)
    {
        if(!visited[i] && graph[city][i] != 0)
        {
            visited[i] = 1;

            tsp(i, count + 1,
                cost + graph[city][i]);

            visited[i] = 0;
        }
    }
}

int solveTSP()
{
    int i;

    minCost = INF;

    for(i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1;

    tsp(0, 1, 0);

    return minCost;
}

void generateGraph(int size)
{
    int i, j;

    n = size;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = rand() % 100 + 1;
        }
    }
}

void measureTime(int sizes[], int count)
{
    int i, result;
    clock_t start, end;
    double timeTaken;

    printf("\nProblem Size\tExecution Time\n");

    for(i = 0; i < count; i++)
    {
        generateGraph(sizes[i]);

        start = clock();

        result = solveTSP();

        end = clock();

        timeTaken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t\t%.6f seconds\n",
               sizes[i], timeTaken);
    }
}

int main()
{
    int sizes[] = {10, 20, 40, 60, 100};
    int count = 5;

    srand(time(NULL));

    measureTime(sizes, count);

    return 0;
}