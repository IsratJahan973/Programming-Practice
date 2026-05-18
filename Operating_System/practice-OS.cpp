#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<semaphore.h>
#include<mutex>
#include<unistd.h>
using namespace std;

int tables=2;
int red_inside=0, blue_inside=0;
sem_t table_sem;
mutex mtx;
queue<Customer>waiting_queue;

struct Customer{
    int id;
    string color;
};

bool canEnter(string color) {
    if(color=="RED")
        return red_inside <= blue_inside;
    else
        return blue_inside <= red_inside;
}

void enterBakery(Customer c) {
    mtx.lock();

    if(!canEnter(c.color)) {
        cout<<"Customer "<<c.id<<" ("<<c.color<<") waiting outside"<<endl;
        waiting_queue.push(c);
        mtx.unlock();
        return;
    }

    if(c.color=="RED") 
    red_inside++;
    else 
    blue_inside++;

    cout<<"Customer "<<c.id<<" (" << c.color << ") ENTERED | R="<<red_inside<<" B="<<blue_inside<<endl;
    mtx.unlock();
}

void checkWaitingQueue() {
    mtx.lock();
    int size=waiting_queue.size();

    while(size--) {
        Customer c= waiting_queue.front();
        waiting_queue.pop();

        if(canEnter(c.color)) {
            if(c.color=="RED") 
              red_inside++;
            else 
              blue_inside++;

            cout<<"Customer "<<c.id<<" ("<<c.color<<") ENTERED from queue | R="<<red_inside<<" B="<<blue_inside<<endl;

            thread t([c]() {
                sem_wait(&table_sem);
                cout<<"Customer "<<c.id<<" got table"<<endl;
                sleep(2);

                mtx.lock();
                if(c.color =="RED") 
                  red_inside--;
                else 
                  blue_inside--;
                cout<<"Customer "<<c.id<<" leaving"<<endl;
                mtx.unlock();

                sem_post(&table_sem);
            });
            t.detach();
        } 
        else 
            waiting_queue.push(c);    
    }
    mtx.unlock();
}

void customer(Customer c) {
    cout<<"Customer "<<c.id<<" (" << c.color << ") arrives"<<endl;
    enterBakery(c);
    mtx.lock();
    bool entered = (c.color == "RED" && red_inside > 0)||(c.color == "BLUE" && blue_inside > 0);
    mtx.unlock();

    if(!entered) return;

    // Table handling
    sem_wait(&table_sem);

    cout << "Customer " << c.id << " (" << c.color << ") got table\n";

    sleep(2);

    // Leaving
    mtx.lock();
    if(c.color == "RED") red_inside--;
    else blue_inside--;

    cout << "Customer " << c.id << " (" << c.color << ") leaving | R="
         << red_inside << " B=" << blue_inside << endl;
    mtx.unlock();

    sem_post(&table_sem);

    checkWaitingQueue();
}

// ---------- MAIN ----------
int main() {

    sem_init(&table_sem, 0, tables);

    vector<Customer> customers = {
        {1,"RED"}, {2,"RED"}, {3,"BLUE"},
        {4,"BLUE"}, {5,"RED"}, {6,"BLUE"}
    };

    vector<thread> threads;

    for(auto &c : customers) {
        threads.push_back(thread(customer, c));
    }

    for(auto &t : threads) {
        t.join();
    }

    return 0;
}
