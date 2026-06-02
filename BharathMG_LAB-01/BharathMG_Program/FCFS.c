#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n], RT[n], RQ[n];

    for (int i = 0; i < n; i++) {
        RQ[i] = i;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &AT[i], &BT[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (AT[RQ[i]] > AT[RQ[j]]) {
                int temp = RQ[i];
                RQ[i] = RQ[j];
                RQ[j] = temp;
            }
        }
    }

    int t = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    for (int i = 0; i < n; i++) {
        if (t < AT[RQ[i]]) {
            t = AT[RQ[i]];
        }

        CT[RQ[i]] = t + BT[RQ[i]];
        TAT[RQ[i]] = CT[RQ[i]] - AT[RQ[i]];
        WT[RQ[i]] = TAT[RQ[i]] - BT[RQ[i]];
        RT[RQ[i]] = t - AT[RQ[i]];

        totalTAT += TAT[RQ[i]];
        totalWT += WT[RQ[i]];
        totalRT += RT[RQ[i]];

        t = CT[RQ[i]];
    }

    printf("\nFCFS process\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, AT[i], BT[i], CT[i], TAT[i], WT[i], RT[i]);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT = %.2f", totalWT / n);
    printf("\nAverage RT = %.2f\n", totalRT / n);

    return 0;
}
