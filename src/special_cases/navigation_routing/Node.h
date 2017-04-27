//
// Created by Andreas Zinkl on 23.04.17.
//

#ifndef ROUTING_NODE_H
#define ROUTING_NODE_H

#include <vector>

using namespace std;

class Node {

private:
    int _x;
    int _y;
    int _costs;

    Node *_predessesor;

public:
    Node();
    Node(int x, int y);
    ~Node();

    friend bool operator<(const Node& lmp, const Node& hmp);

    int getX();
    int getY();

    void setCosts(int costs);
    int getCosts();
    bool equals(Node* comp);

    void setPredessesor(Node* node);
    Node* getPredessesor();
};


#endif //ROUTING_NODE_H
