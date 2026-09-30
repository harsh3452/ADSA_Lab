#include <stdio.h>
#include <stdlib.h>

#define N 4
#define MAX 100000

struct Node
{
    int board[N][N];
    int x, y;
    int px, py;
    int level;
    int cost;
};

struct Node heap[MAX];
int heapSize = 0;

unsigned long long visited[MAX];
int visitedCount = 0;

int calculateCost(int board[N][N])
{
    int cost = 0;
    int i, j, value;
    int targetX, targetY;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            value = board[i][j];

            if(value != 0)
            {
                targetX = (value - 1) / N;
                targetY = (value - 1) % N;

                cost += abs(i - targetX);
                cost += abs(j - targetY);
            }
        }
    }

    return cost;
}

int isGoal(int board[N][N])
{
    int i, j, value = 1;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(i == N - 1 && j == N - 1)
                return board[i][j] == 0;

            if(board[i][j] != value)
                return 0;

            value++;
        }
    }

    return 1;
}

unsigned long long encode(int board[N][N])
{
    unsigned long long code = 0;
    int i, j;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            code = code * 16 + board[i][j];
    }

    return code;
}

int isVisited(unsigned long long code)
{
    int i;

    for(i = 0; i < visitedCount; i++)
    {
        if(visited[i] == code)
            return 1;
    }

    return 0;
}

void copyBoard(int source[N][N], int destination[N][N])
{
    int i, j;

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            destination[i][j] = source[i][j];
}

void insertNode(struct Node node)
{
    int i, parent;
    struct Node temp;

    i = heapSize++;
    heap[i] = node;

    while(i > 0)
    {
        parent = (i - 1) / 2;

        if(heap[parent].cost <= heap[i].cost)
            break;

        temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

struct Node removeMin()
{
    struct Node result, temp;
    int i, left, right, smallest;

    result = heap[0];

    heap[0] = heap[--heapSize];

    i = 0;

    while(1)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;

        if(left < heapSize &&
           heap[left].cost < heap[smallest].cost)
            smallest = left;

        if(right < heapSize &&
           heap[right].cost < heap[smallest].cost)
            smallest = right;

        if(smallest == i)
            break;

        temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        i = smallest;
    }

    return result;
}

void addChild(struct Node current, int nx, int ny)
{
    struct Node child;
    unsigned long long code;
    int temp;

    if(nx < 0 || nx >= N || ny < 0 || ny >= N)
        return;

    if(nx == current.px && ny == current.py)
        return;

    copyBoard(current.board, child.board);

    temp = child.board[current.x][current.y];

    child.board[current.x][current.y] =
        child.board[nx][ny];

    child.board[nx][ny] = temp;

    child.x = nx;
    child.y = ny;

    child.px = current.x;
    child.py = current.y;

    child.level = current.level + 1;

    child.cost = child.level +
                 calculateCost(child.board);

    code = encode(child.board);

    if(!isVisited(code))
    {
        visited[visitedCount++] = code;
        insertNode(child);
    }
}

void printBoard(int board[N][N])
{
    int i, j;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            printf("%2d ", board[i][j]);

        printf("\n");
    }
}

void solveBranchAndBound(int board[N][N], int x, int y)
{
    struct Node start, current;
    unsigned long long code;

    start.x = x;
    start.y = y;

    start.px = -1;
    start.py = -1;

    start.level = 0;

    copyBoard(board, start.board);

    start.cost = calculateCost(start.board);

    heapSize = 0;
    visitedCount = 0;

    code = encode(start.board);

    visited[visitedCount++] = code;

    insertNode(start);

    while(heapSize > 0)
    {
        current = removeMin();

        if(isGoal(current.board))
        {
            printf("\nSolution found!\n");
            printf("Minimum number of moves = %d\n\n",
                   current.level);

            printBoard(current.board);

            return;
        }

        addChild(current,
                 current.x - 1,
                 current.y);

        addChild(current,
                 current.x + 1,
                 current.y);

        addChild(current,
                 current.x,
                 current.y - 1);

        addChild(current,
                 current.x,
                 current.y + 1);
    }

    printf("\nNo solution exists.\n");
}

int main()
{
    int board[N][N];
    int i, j;
    int x, y;

    printf("Enter 15-puzzle configuration (0 for blank):\n");

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            scanf("%d", &board[i][j]);

            if(board[i][j] == 0)
            {
                x = i;
                y = j;
            }
        }
    }

    solveBranchAndBound(board, x, y);

    return 0;
}