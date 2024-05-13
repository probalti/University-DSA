#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* head = NULL;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void insert(int data) {
    Node* newNode = createNode(data);
    if (head == NULL || data < head->data) {
        newNode->next = head;
        if (head != NULL)
            head->prev = newNode;
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }
    newNode->next = current->next;
    if (current->next != NULL)
        current->next->prev = newNode;
    current->next = newNode;
    newNode->prev = current;
}

void remove(int data) {
    if (head == NULL) {
        return;
    }
    Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                head = current->next;
            if (current->next != NULL)
                current->next->prev = current->prev;
            free(current);
            return;
        }
        current = current->next;
    }
}

void print() {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//void moveMinToFront() {
//    if (head == NULL || head->next == NULL) {
//        return;
//    }
//    Node* current = head;
//    Node* minNode = current;
//    while (current != NULL) {
//        if (current->data < minNode->data) {
//            minNode = current;
//        }
//        current = current->next;
//    }
//    if (minNode != head) {
//        minNode->prev->next = minNode->next;
//        if (minNode->next != NULL) {
//            minNode->next->prev = minNode->prev;
//        }
//        minNode->next = head;
//        head->prev = minNode;
//        minNode->prev = NULL;
//        head = minNode;
//    }
//}
//
//void moveMaxToLast() {
//    if (head == NULL || head->next == NULL) {
//        return;
//    }
//    Node* current = head;
//    Node* maxNode = current;
//    while (current != NULL) {
//        if (current->data > maxNode->data) {
//            maxNode = current;
//        }
//        current = current->next;
//    }
//    if (maxNode->next != NULL) {
//        maxNode->prev->next = maxNode->next;
//        maxNode->next->prev = maxNode->prev;
//        current = head;
//        while (current->next != NULL) {
//            current = current->next;
//        }
//        current->next = maxNode;
//        maxNode->prev = current;
//        maxNode->next = NULL;
//    }
//}

int countNodes() {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int findMiddleValue() {
    int count = countNodes();
    Node* current = head;
    for (int i = 0; i < count / 2; ++i) {
        current = current->next;
    }
    return current->data;
}

int main() {
    insert(5);
    insert(10);
    insert(3);
    insert(8);
    insert(15);
    insert(1);

    cout << "Nodes: ";
    print();

    remove(8);
    cout << "After deleting node with data 8: ";
    print();

//    moveMinToFront();
    cout << "After moving minimum value node to the first position: ";
    print();
//
//    moveMaxToLast();
//    cout << "After moving maximum value node to the last position: ";
//    print();

    cout << "Total number of nodes: " << countNodes() << endl;

    cout << "Middle value of the linked list: " << findMiddleValue() << endl;

    return 0;
}

