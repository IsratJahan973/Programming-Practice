
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAX_TABLES 3
#define TOTAL_CUSTOMERS 20
#define MAX_QUEUE 100

// ================= STRUCT =================

typedef struct {
    int id;
    char type; // 'R' or 'B'
} Customer;

// ================= QUEUE =================

Customer queue[MAX_QUEUE];
int front = 0, rear = 0;

int isEmpty() {
    return front == rear;
}

void enqueue(Customer c) {
    queue[rear] = c;
    rear = (rear + 1) % MAX_QUEUE;
}

Customer dequeue() {
    Customer c = queue[front];
    front = (front + 1) % MAX_QUEUE;
    return c;
}

Customer peek() {
    return queue[front];
}

// ================= SYNC =================

pthread_mutex_t lock;
pthread_cond_t cond;

sem_t table_sem;

// ================= STATE =================

int red_inside = 0;
int blue_inside = 0;

int waiting_red = 0;
int waiting_blue = 0;

// ================= HELPER =================

void print_status() {
    printf("Inside[R:%d B:%d] Waiting[R:%d B:%d]\n",
           red_inside, blue_inside, waiting_red, waiting_blue);
}

int can_enter(char type) {
    if (type == 'R')
        return red_inside <= blue_inside;
    else
        return blue_inside <= red_inside;
}

// ================= ENTRY =================

void enter(Customer c) {
    pthread_mutex_lock(&lock);

    enqueue(c);

    if (c.type == 'R') waiting_red++;
    else waiting_blue++;

    printf("Customer %d (%c) ARRIVED & QUEUED\n", c.id, c.type);
    print_status();

    while (1) {
        Customer first = peek();

        // FIFO + balance rule
        if (first.id == c.id && can_enter(c.type)) {

            if (sem_trywait(&table_sem) == 0) {

                dequeue();

                if (c.type == 'R') {
                    red_inside++;
                    waiting_red--;
                } else {
                    blue_inside++;
                    waiting_blue--;
                }

                printf(" Customer %d (%c) ENTERED\n", c.id, c.type);
                print_status();

                pthread_mutex_unlock(&lock);
                return;
            }
        }

        pthread_cond_wait(&cond, &lock);
    }
}

// ================= EXIT =================

void leave(Customer c) {
    pthread_mutex_lock(&lock);

    if (c.type == 'R') red_inside--;
    else blue_inside--;

    printf(" Customer %d (%c) LEFT\n", c.id, c.type);
    print_status();

    pthread_mutex_unlock(&lock);

    sem_post(&table_sem);

    // Wake next possible thread
    pthread_cond_signal(&cond);
}

// ================= THREAD =================

void* customer_thread(void* arg) {
    Customer c = *((Customer*)arg);

    enter(c);

    sleep(rand() % 3 + 1);

    leave(c);

    return NULL;
}

// ================= MAIN =================

int main() {
    srand(time(NULL));

    pthread_t threads[TOTAL_CUSTOMERS];
    Customer customers[TOTAL_CUSTOMERS];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    sem_init(&table_sem, 0, MAX_TABLES);

    for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
        customers[i].id = i + 1;
        customers[i].type = (rand() % 2 == 0) ? 'R' : 'B';

        pthread_create(&threads[i], NULL, customer_thread, &customers[i]);

        usleep(80000);
    }

    for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    sem_destroy(&table_sem);

    printf("\n TOPPER LEVEL SIMULATION COMPLETE!\n");

    return 0;
}
