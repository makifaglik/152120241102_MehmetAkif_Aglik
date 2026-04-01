#include<iostream>
using namespace std;

struct package{
    string packageID;
    string destinationCity;
    int dimensions[3];
    struct package* next;
};

struct courier{
    string courierName;
    string vehicleType;
};

package *Insert(package *hd, int dmns[3]){
    package *p = new package;
    for(int i=0; i<3; i++){
            p->dimensions[i] = dmns[i];
        }
    p->next = hd;
    return p;
}

package *Undo(package *hd) {
    if (hd == NULL) {
        return NULL;
    }

    package *dlthd = hd;
    hd = hd->next;     
    delete dlthd;    
    return hd;    
}

#define MAX 5

int dimens[3];
string cour[3];
string items[MAX];
int front = 0;
int rear = -1;
int current_size = 0;

void enqueue(string info[2]) {
    if (current_size == MAX) {
        cout << "list is full" << endl;
        return;
    }
    rear = (rear + 1) % MAX;
    items[rear] = info[2];
    current_size++;
}

string dequeue() {
    if (current_size == 0) {
        cout << "list is empty" << endl;
        return "";
    }
    string info = items[front];
    front = (front + 1) % MAX;
    current_size--;
    return info;
}

void push(string info) {
    rear = (rear + 1) % MAX;
    items[rear] = info;
    if (current_size < MAX) {
        current_size++;
    } else {
        
        front = (front + 1) % MAX;
    }
}

string pop() {
    if (current_size == 0) return "";
    string info = items[rear];
    rear = (rear - 1 + MAX) % MAX;
    current_size--;
    return info;
}

int main() {
    package *head =NULL;

    for(int i=0; i<3; i++){
            cout << "enter dimension of package: ";
            cin >> dimens[i];
        }
    head = Insert(head, dimens);
    for(int i=0; i<2; i++){
            cout << "enter information of : ";
            cin >> cour[i];
        }
    enqueue(cour);

    dequeue();
    Undo(head);


    return 0;
}