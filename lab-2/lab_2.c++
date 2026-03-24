#include <iostream>
#include <string>
using namespace std;

typedef struct Node {
    string data;
    struct Node *next;
} Node;

Node *Insert(Node *hd, string wrd){
    Node *p = new Node;
    p->data = wrd;
    p->next = hd;
    return p;
}
void print(Node *hd){
    while(hd!=NULL){
        cout << hd->data << "->";
        hd = hd->next;
    }
    if(hd==NULL){
        cout << "NULL" << endl;
    }
}

Node *Undo(Node *hd) {
    if (hd == NULL) {
        return NULL;
    }
    
    Node *dlthd = hd;
    hd = hd->next;     
    delete dlthd;    
    return hd;    
}

int main(){

    Node *head =NULL;
    string word;

    while(1){
        cout << "enter a word (EXIT for exit)(Undo for undo the last word): ";
        cin >> word;
        if(word == "EXIT") break;
        if(word == "UNDO"){
            head = Undo(head);
            print(head);
            continue;
        }
        head = Insert(head, word);
        print(head);
    }
    cout << "Program is finished";
}