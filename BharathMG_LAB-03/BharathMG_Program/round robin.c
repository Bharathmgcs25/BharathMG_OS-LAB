#include <stdio.h>

int main()
{
    int n, i, qt;
    int at[20], bt[20], rem_bt[20];
    int wt[20], tat[20], rt[20], ct[20];
    int visited[20] = {0};

    int queue[100], front = 0, rear = 0;

    int time = 0, completed = 0;
    float awt = 0, atat = 0, art = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter AT and BT for each process:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d (AT BT): ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter quantum time: ");
    scanf("%d", &qt);

    // Add processes that arrive at time 0
    for(i = 0; i < n; i++)
    {
        if(at[i] == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nGantt Chart:\n|");

    while(completed < n)
    {
        if(front == rear)
        {
            time++;
            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && visited[i] == 0)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        // Response Time (first time execution)
        if(rem_bt[idx] == bt[idx])
        {
            rt[idx] = time - at[idx];
            art += rt[idx];
        }

        int exec;
        if(rem_bt[idx] > qt)
            exec = qt;
        else
            exec = rem_bt[idx];

        printf(" P%d |", idx+1);

        time += exec;
        rem_bt[idx] -= exec;

        // Add newly arrived processes
        for(int j = 0; j < n; j++)
        {
            if(at[j] <= time && visited[j] == 0)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rem_bt[idx] > 0)
        {
            queue[rear++] = idx;
        }
        else
        {
            completed++;
            ct[idx] = time;                 // ✅ Completion Time
            tat[idx] = ct[idx] - at[idx];  // ✅ FIXED (IMPORTANT)
        }
    }

    printf("\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i];
        awt += wt[i];
        atat += tat[i];
    }

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    awt /= n;
    atat /= n;
    art /= n;

    printf("\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f", atat);
    printf("\nAverage Response Time = %.2f\n", art);

    return 0;
}
