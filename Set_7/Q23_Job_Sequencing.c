#include <stdio.h>

struct Job
{
    char id;
    int deadline;
    int profit;
};

void sortJobs(struct Job jobs[], int n)
{
    int i, j;
    struct Job temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(jobs[j].profit < jobs[j + 1].profit)
            {
                temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

void jobSequencing(struct Job jobs[], int n)
{
    int slot[20];
    int i, j, maxDeadline = 0;
    int totalProfit = 0;

    for(i = 0; i < n; i++)
    {
        if(jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    for(i = 0; i <= maxDeadline; i++)
        slot[i] = -1;

    for(i = 0; i < n; i++)
    {
        for(j = jobs[i].deadline; j > 0; j--)
        {
            if(slot[j] == -1)
            {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("Job sequence:\n");

    for(i = 1; i <= maxDeadline; i++)
    {
        if(slot[i] != -1)
            printf("%c ", jobs[slot[i]].id);
    }

    printf("\nMaximum profit = %d\n", totalProfit);
}

int main()
{
    struct Job jobs[20];
    int n, i;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    printf("Enter job ID, deadline and profit:\n");

    for(i = 0; i < n; i++)
        scanf(" %c %d %d",
              &jobs[i].id,
              &jobs[i].deadline,
              &jobs[i].profit);

    sortJobs(jobs, n);
    jobSequencing(jobs, n);

    return 0;
}