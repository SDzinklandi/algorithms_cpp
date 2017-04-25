#include <iostream>
#include "src/priorityqueue/priorityqueue.h"

int main() {

    //Test the Priority Queue
    PriorityQueue* pq = new PriorityQueue();

    //Nodes for the PQ
    pq->insert(new Node(), 5);
    pq->insert(new Node(), 10);
    pq->insert(new Node(), 2);
    pq->insert(new Node(), 8);
    pq->insert(new Node(), 3);

    while(!pq->isEmpty()) {
        Element* e = pq->extractMin();
        printf("PRIO(%d)\n", e->getPriority());
    }

    return 0;
}