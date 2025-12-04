#include <stdio.h>

void fcfs() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], start[n], finish[n], wait[n], seq[n];

    for(int i=0;i<n;i++){
        seq[i] = i+1;
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);
    }

    int t = 0;
    for(int i=0;i<n;i++){
        if(t < arrival[i]) t = arrival[i];
        start[i] = t;
        t += burst[i];
        finish[i] = t;
        wait[i] = start[i] - arrival[i];
    }

    float avg = 0;
    for(int i=0;i<n;i++) avg += wait[i];
    avg /= n;

    printf("\nFCFS Result:\n");
    for(int i=0;i<n;i++){
        printf("P%d Arrival=%d Burst=%d Wait=%d\n", seq[i], arrival[i], burst[i], wait[i]);
    }

    printf("Sequence: ");
    for(int i=0;i<n;i++) printf("P%d ", seq[i]);
    printf("\nAverage Waiting Time=%.2f\n\n", avg);
}

void sjf() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], done[n], wait[n], seq[n];

    for(int i=0;i<n;i++){
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);
        done[i] = 0;
    }

    int t = 0, completed = 0, s = 0;

    while(completed < n){
        int idx = -1, best = 999999;
        for(int i=0;i<n;i++){
            if(!done[i] && arrival[i] <= t){
                if(burst[i] < best){
                    best = burst[i];
                    idx = i;
                }
            }
        }
        if(idx == -1){ t++; continue; }

        seq[s++] = idx+1;
        wait[idx] = t - arrival[idx];
        t += burst[idx];
        done[idx] = 1;
        completed++;
    }

    float avg = 0;
    for(int i=0;i<n;i++) avg += wait[i];
    avg /= n;

    printf("\nSJF Result:\n");
    for(int i=0;i<n;i++){
        printf("P%d Arrival=%d Burst=%d Wait=%d\n", i+1, arrival[i], burst[i], wait[i]);
    }

    printf("Sequence: ");
    for(int i=0;i<s;i++) printf("P%d ", seq[i]);
    printf("\nAverage Waiting Time=%.2f\n\n", avg);
}

void rr() {
    int n, q;
    printf("Number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], rem[n], finish[n], wait[n];

    for(int i=0;i<n;i++){
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);
        rem[i] = burst[i];
    }

    printf("Enter Quantum: ");
    scanf("%d", &q);

    int t = 0, done = 0;
    int seq[999], s = 0;

    while(done < n){
        int used = 0;

        for(int i=0;i<n;i++){
            if(arrival[i] <= t && rem[i] > 0){
                int run = rem[i] < q ? rem[i] : q;
                rem[i] -= run;

                for(int k=0;k<run;k++) seq[s++] = i+1;

                t += run;
                if(rem[i] == 0){
                    finish[i] = t;
                    done++;
                }
                used = 1;
            }
        }
        if(!used) t++;
    }

    for(int i=0;i<n;i++){
        wait[i] = finish[i] - arrival[i] - burst[i];
    }

    float avg = 0;
    for(int i=0;i<n;i++) avg += wait[i];
    avg /= n;

    printf("\nRound Robin Result:\n");
    for(int i=0;i<n;i++){
        printf("P%d Arrival=%d Burst=%d Wait=%d\n", i+1, arrival[i], burst[i], wait[i]);
    }

    printf("Sequence: ");
    for(int i=0;i<s;i++) printf("P%d ", seq[i]);
    printf("\nAverage Waiting Time=%.2f\n\n", avg);
}

void priority_sch() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], priority[n], done[n], wait[n], seq[n];

    for(int i=0;i<n;i++){
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);
        printf("Enter priority for P%d: ", i+1);
        scanf("%d", &priority[i]);
        done[i] = 0;
    }

    int t = 0, s = 0, completed = 0;

    while(completed < n){
        int idx = -1, best = 999999;

        for(int i=0;i<n;i++){
            if(!done[i] && arrival[i] <= t){
                if(priority[i] < best){
                    best = priority[i];
                    idx = i;
                }
            }
        }

        if(idx == -1){ t++; continue; }

        seq[s++] = idx+1;
        wait[idx] = t - arrival[idx];
        t += burst[idx];
        done[idx] = 1;
        completed++;
    }

    float avg = 0;
    for(int i=0;i<n;i++) avg += wait[i];
    avg /= n;

    printf("\nPriority Scheduling Result:\n");
    for(int i=0;i<n;i++){
        printf("P%d Arrival=%d Burst=%d Priority=%d Wait=%d\n", i+1, arrival[i], burst[i], priority[i], wait[i]);
    }

    printf("Sequence: ");
    for(int i=0;i<s;i++) printf("P%d ", seq[i]);
    printf("\nAverage Waiting Time=%.2f\n\n", avg);
}

int main() {
    int c;

    while(1){
        printf("==========================================\n");
        printf("        WELCOME TO GROUP-3's \n");
        printf("       PROCESS SCHEDULER SIMULATOR\n");
        printf("==========================================\n\n");
        printf("Select an option...\n");
        printf("1. First Come First Serve (FCFS)\n");
        printf("2. Shortest Job First (SJF)\n");
        printf("3. Round Robin (RR)\n");
        printf("4. Priority Scheduling\n");
        printf("0. Exit\n");
        printf("==========================================\n\n");
        printf("Choice: ");
        scanf("%d", &c);

        if(c==0){
            printf("\n==========================================\n");
            printf("   THANK YOU FOR USING GROUP 3's  \n");
            printf("   PROCESS SCHEDULER SIMULATOR\n");
            printf("==========================================\n");
            break;
        }
        else if(c==1){
            printf("\nYou are choosing: First Come First Serve (FCFS)\n\n");
            fcfs();
        }
        else if(c==2){
            printf("\nYou are choosing: Shortest Job First (SJF)\n\n");
            sjf();
        }
        else if(c==3){
            printf("\nYou are choosing: Round Robin (RR)\n\n");
            rr();
        }
        else if(c==4){
            printf("\nYou are choosing: Priority Scheduling\n\n");
            priority_sch();
        }
        else printf("\nInvalid choice! Please select 0-4.\n\n");
    }
    return 0;
}
