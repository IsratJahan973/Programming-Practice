
#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<semaphore.h>
#include<mutex>
#include<unistd.h>
using namespace std;

struct Customer{
    int id;
    string color;
};

int tables=2;
int red_inside=0,blue_inside=0;
sem_t table_sem;
mutex mtx;
mutex print_mtx;
queue<Customer> waiting_queue;

bool canEnter(string color) {
    if(color=="RED")
        return red_inside <= blue_inside;
    else
        return blue_inside <= red_inside;
}

void enterBakery(Customer c) {
    mtx.lock();

    if(!canEnter(c.color)) {
        print_mtx.lock();
        cout<<"Customer "<<c.id<<" ("<<c.color<<") waiting outside"<<endl;
        print_mtx.unlock();

        waiting_queue.push(c);
        mtx.unlock();
        return;
    }

    if(c.color=="RED") 
        red_inside++;
    else 
        blue_inside++;

    print_mtx.lock();
    cout<<"Customer "<<c.id<<" (" << c.color << ") ENTERED | R="<<red_inside<<" B="<<blue_inside<<endl;
    print_mtx.unlock();

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

            print_mtx.lock();
            cout<<"Customer "<<c.id<<" ("<<c.color<<") ENTERED from queue | R="<<red_inside<<" B="<<blue_inside<<endl;
            print_mtx.unlock();

            thread t([c]() {
                sem_wait(&table_sem);

                print_mtx.lock();
                cout<<"Customer "<<c.id<<" got table"<<endl;
                print_mtx.unlock();

                sleep(2);

                mtx.lock();
                if(c.color =="RED") 
                    red_inside--;
                else 
                    blue_inside--;

                print_mtx.lock();
                cout<<"Customer "<<c.id<<" leaving"<<endl;
                print_mtx.unlock();

                mtx.unlock();

                sem_post(&table_sem);
            });
            t.detach();
        } 
        else {
            waiting_queue.push(c);
        }
    }
    mtx.unlock();
}

void customer(Customer c) {
    print_mtx.lock();
    cout<<"Customer "<<c.id<<" (" << c.color << ") arrives"<<endl;
    print_mtx.unlock();

    enterBakery(c);

    mtx.lock();
    bool entered = (c.color == "RED" && red_inside > 0)||(c.color == "BLUE" && blue_inside > 0);
    mtx.unlock();

    if(!entered) return;

    sem_wait(&table_sem);

    print_mtx.lock();
    cout << "Customer " << c.id << " (" << c.color << ") got table" << endl;
    print_mtx.unlock();

    sleep(2);

    mtx.lock();
    if(c.color == "RED") red_inside--;
    else blue_inside--;

    print_mtx.lock();
    cout << "Customer " << c.id << " (" << c.color << ") leaving | R="
         << red_inside << " B=" << blue_inside << endl;
    print_mtx.unlock();

    mtx.unlock();

    sem_post(&table_sem);

    checkWaitingQueue();
}

int main() {
    cout<<"Welcome to Sweet Bakery"<<endl;

    sem_init(&table_sem, 0, tables);

    vector<Customer> customers = { {1,"RED"}, {2,"RED"}, {3,"BLUE"}, {4,"BLUE"}, {5,"RED"}, {6,"BLUE" }};

    vector<thread> threads;

    for(auto &c : customers) {
        threads.push_back(thread(customer, c));
    }

    for(auto &t : threads) {
        t.join();
    }
    return 0;
}