
#include <stdio.h>

int main() {
    int n, i, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], visited[n];

    printf("Enter Arrival Time and Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("P%d AT BT: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];      // Remaining time (for preemptive)
        visited[i] = 0;     // For non-preemptive
    }

    printf("\nChoose Scheduling Type:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int completed = 0, current_time = 0, shortest;
    float total_tat = 0, total_wt = 0;

    // ---------------- NON PREEMPTIVE ----------------
    if(choice == 1) {

        while(completed < n) {
            shortest = -1;

            for(i = 0; i < n; i++) {
                if(at[i] <= current_time && visited[i] == 0) {
                    if(shortest == -1 || bt[i] < bt[shortest])
                        shortest = i;
                }
            }

            if(shortest == -1) {
                current_time++;
            } else {
                current_time += bt[shortest];
                ct[shortest] = current_time;
                visited[shortest] = 1;
                completed++;
            }
        }
    }

    // ---------------- PREEMPTIVE (SRTF) ----------------
    else if(choice == 2) {

        while(completed < n) {
            shortest = -1;

            for(i = 0; i < n; i++) {
                if(at[i] <= current_time && rt[i] > 0) {
                    if(shortest == -1 || rt[i] < rt[shortest])
                        shortest = i;
                }
            }

            if(shortest == -1) {
                current_time++;
            } else {
                rt[shortest]--;      // Execute for 1 unit
                current_time++;

                if(rt[shortest] == 0) {
                    ct[shortest] = current_time;
                    completed++;
                }
            }
        }
    }

    // ---------------- CALCULATIONS ----------------
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    // ---------------- OUTPUT ----------------
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}
