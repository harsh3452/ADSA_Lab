#include <stdio.h>

#define INF 9999

int n;
int graph[20][20];

void prim()
{
    int key[20], parent[20], used[20];
    int i, j, u, min;

    for (i = 0; i < n; i++)
    {
        key[i] = INF;
        used[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;

    for (i = 0; i < n - 1; i++)
    {
        min = INF; // reset min to start process from start again.
        u = -1;

        for (j = 0; j < n; j++)
        {
            if (!used[j] && key[j] < min) // find the vertex with smallest key to it.
            {
                min = key[j];
                u = j;
            }
        }

        used[u] = 1;

        for (j = 0; j < n; j++) //check all edge of u which can give us the next edge to pick and pick the smallest
        {
            if (graph[u][j] != 0 && //checking if an edge exists if yes j needs not to be visited and we should have a edge which has smaller edge then key we picked
                !used[j] &&
                graph[u][j] < key[j])
            {
                key[j] = graph[u][j]; // assign the weight as we visited it 
                parent[j] = u; //assigning the current as parent as we choose this vertex to go
            }
        }
    }

    printf("Minimum Spanning Tree:\n"); // printing normally

    for (i = 1; i < n; i++)
    {
        printf("%d - %d : %d\n",
               parent[i], i, graph[i][parent[i]]);
    }
}


int main() 
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }

    prim();

    return 0;
}