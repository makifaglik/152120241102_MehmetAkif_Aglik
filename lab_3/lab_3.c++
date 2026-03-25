#include <iostream>
#include <string>
using namespace std;

typedef struct Song{
    string title;
    string artist;
    int ratings[3];
    struct Song *next;
    struct Song *prev;
    struct Song *current;
}Song;

Song *Insert(Song *hd, string sng, string sngr, int rate[3]){
    Song *p = new Song;
    p->title = sng;
    p->artist = sngr;
    for(int i=0; i<3; i++){
            p->ratings[i] = rate[i];
        }
    p->next = hd;
    return p;
}
void print(Song *hd){
    while(hd!=NULL){
        cout << hd->title <<","<<hd->artist<<",";
        for(int i=0; i<3; i++){
            cout << hd->ratings[i];
            cout << ",";
        }
        cout << "->";
        hd = hd->next;
    }
    if(hd==NULL){
        cout << "NULL" << endl;
    }
}

Song *Undo(Song *hd) {
    if (hd == NULL) {
        return NULL;
    }
    
    Song *dlthd = hd;
    hd = hd->next;     
    delete dlthd;    
    return hd;    
}

int main(){

    Song *head =NULL;
    string song;
    string singer;
    int rating[3];

    Song s1;
    Song *ps =&s1;

    while(1){
        cout << "enter a song (EXIT for exit)(Undo for undo the last word): ";
        cin >> song;
        if(song == "UNDO"){
            head = Undo(head);
            print(head);
            continue;
        }
        if(song == "EXIT") break;
        cout << "enter a singer (EXIT for exit)(Undo for undo the last word): ";
        cin >> singer;
        for(int i=0; i<3; i++){
            cout << "enter a ratings (EXIT for exit)(Undo for undo the last word): ";
            cin >> rating[i];
        }
        head = Insert(head, song, singer, rating);
        print(head);
    }
    cout << "Program is finished";
}