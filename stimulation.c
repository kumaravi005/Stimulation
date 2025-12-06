#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define AGENTS 3

int queue[MAX];
int front = 0;
int rear = 0;

int agentBusy[AGENTS];
int agentCall[AGENTS];
int agentTime[AGENTS];

int isEmpty() {
    return front == rear;
}

int isFull() {
    return rear == MAX;
}

void enqueue(int x) {
    if (!isFull()) queue[rear++] = x;
}

int dequeue() {
    if (isEmpty()) return -1;
    return queue[front++];
}

int main() {
    int time = 0, choice, callId, duration, i;

    for (i = 0; i < AGENTS; i++) agentBusy[i] = 0;

    while (1) {
        printf("\n1. Add Call\n2. Simulate 1 Time Unit\n3. Exit\nEnter: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Call ID: ");
            scanf("%d", &callId);
            printf("Duration: ");
            scanf("%d", &duration);
            enqueue(callId);
            enqueue(duration);
        } 
        
        else if (choice == 2) {
            time++;

            for (i = 0; i < AGENTS; i++) {
                if (agentBusy[i]) {
                    agentTime[i]--;
                    if (agentTime[i] <= 0) {
                        agentBusy[i] = 0;
                        printf("Time %d: Agent %d finished call %d\n", time, i + 1, agentCall[i]);
                    }
                }
            }

            for (i = 0; i < AGENTS; i++) {
                if (!agentBusy[i] && !isEmpty()) {
                    int id = dequeue();
                    int t = dequeue();
                    agentBusy[i] = 1;
                    agentCall[i] = id;
                    agentTime[i] = t;
                    printf("Time %d: Agent %d started call %d for %d units\n", time, i + 1, id, t);
                }
            }
        }

        else if (choice == 3) {
            break;
        }
    }

    return 0;
}