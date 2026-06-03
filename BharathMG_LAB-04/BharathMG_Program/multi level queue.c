#include <stdio.h>
#define MAX 100

typedef struct {
    int id, at, bt, rt, ct, wt, tat, type;
} Process;

Process p[MAX];
int n;
int sysQ[MAX], userQ[MAX];
int frontS = 0, rearS = 0;
int frontU = 0, rearU = 0;

void enqueue(int q[], int *rear, int val) {
    q[(*rear)++] = val;
}

int dequeue(int q[], int *front, int *rear) {
    if (*front == *rear) return -1;
    return q[(*front)++];
}

int isEmpty(int front, int rear) {
    return front == rear;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);
        p[i].id = i;
        p[i].rt = p[i].bt;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }}}

    int time = 0, completed = 0, i = 0;
    int current = -1;
    int gantt[MAX], gtime[MAX], gindex = 0;

    while (completed < n) {
        while (i < n && p[i].at <= time) {
            if (p[i].type == 0)
                enqueue(sysQ, &rearS, i);
            else
                enqueue(userQ, &rearU, i);
            i++;
        }

        if (current != -1 && p[current].type == 1 && !isEmpty(frontS, rearS)) {
            enqueue(userQ, &rearU, current);
            current = -1;
        }

        if (current == -1) {
            if (!isEmpty(frontS, rearS))
                current = dequeue(sysQ, &frontS, &rearS);
            else if (!isEmpty(frontU, rearU))
                current = dequeue(userQ, &frontU, &rearU);
            else {
                time++;
                continue;
            }
        }

        gantt[gindex] = p[current].id;
        gtime[gindex] = time;
        gindex++;
        p[current].rt--;
        time++;

        if (p[current].rt == 0) {
            p[current].ct = time;
            p[current].tat = p[current].ct - p[current].at;
            p[current].wt = p[current].tat - p[current].bt;
            completed++;
            current = -1;
        }}

    gtime[gindex] = time;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gindex; i++) {
        printf(" P%d |", gantt[i]);
    }

    printf("\n0");
    for (int i = 0; i < gindex; i++) {
        printf("   %d", gtime[i+1]);
    }

    float totalWT = 0, totalTAT = 0;

    printf("\n\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               (p[i].type == 0) ? "System" : "User",
               p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tat);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
