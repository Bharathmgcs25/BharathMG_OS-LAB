#include <stdio.h>
#include <math.h>

#define MAX 20

struct Task {
    int id;
    int bt;
    int deadline;
    int period;
    int ct;
    int wt;
    int tat;
};

double utilization_edf(struct Task tasks[], int n) {
    double u = 0;
    for(int i=0;i<n;i++)
        u += (double)tasks[i].bt / tasks[i].deadline;
    return u;
}

double utilization_rms(struct Task tasks[], int n) {
    double u = 0;
    for(int i=0;i<n;i++)
        u += (double)tasks[i].bt / tasks[i].period;
    return u;
}

double rm_bound(int n) {
    return n * (pow(2.0,1.0/n) - 1.0);
}

void edf(struct Task tasks[], int n) {

    // Sort by deadline
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            if(tasks[i].deadline > tasks[j].deadline) {
                struct Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    printf("\n===== EARLIEST DEADLINE FIRST (EDF) =====\n");
    printf("--------------------------------------------------\n");
    printf("PID\tBT\tDeadline\tCT\tWT\tTAT\n");
    printf("--------------------------------------------------\n");

    int time = 0;

    for(int i=0;i<n;i++) {
        time += tasks[i].bt;
        tasks[i].ct = time;
        tasks[i].tat = tasks[i].ct;
        tasks[i].wt = tasks[i].tat - tasks[i].bt;

        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
            tasks[i].id,
            tasks[i].bt,
            tasks[i].deadline,
            tasks[i].ct,
            tasks[i].wt,
            tasks[i].tat
        );
    }

    double u = utilization_edf(tasks,n);

    printf("--------------------------------------------------\n");
    printf("Utilization (EDF) = %.2f\n", u);

    if(u <= 1.0)
        printf("Result: Schedulable\n");
    else
        printf("Result: Not Schedulable\n");
}

void rms(struct Task tasks[], int n) {

    // Sort by period
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            if(tasks[i].period > tasks[j].period) {
                struct Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    printf("\n===== RATE MONOTONIC SCHEDULING (RMS) =====\n");
    printf("--------------------------------------------------\n");
    printf("PID\tBT\tPeriod\t\tCT\tWT\tTAT\n");
    printf("--------------------------------------------------\n");

    int time = 0;

    for(int i=0;i<n;i++) {
        time += tasks[i].bt;
        tasks[i].ct = time;
        tasks[i].tat = tasks[i].ct;
        tasks[i].wt = tasks[i].tat - tasks[i].bt;

        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
            tasks[i].id,
            tasks[i].bt,
            tasks[i].period,
            tasks[i].ct,
            tasks[i].wt,
            tasks[i].tat
        );
    }

    double u = utilization_rms(tasks,n);
    double bound = rm_bound(n);

    printf("--------------------------------------------------\n");
    printf("Utilization (RMS) = %.2f\n", u);
    printf("RM Bound = %.2f\n", bound);

    if(u <= bound)
        printf("Result: Schedulable\n");
    else
        printf("Result: Not Schedulable\n");
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Task tasks[n];

    printf("\nEnter process details:\n");

    for(int i=0;i<n;i++) {
        tasks[i].id = i+1;

        printf("\nProcess %d:\n", i+1);
        printf("Burst Time: ");
        scanf("%d",&tasks[i].bt);

        printf("Deadline: ");
        scanf("%d",&tasks[i].deadline);

        printf("Period: ");
        scanf("%d",&tasks[i].period);
    }

    edf(tasks,n);
    rms(tasks,n);

    return 0;
}

