#include <iostream>
#include <string>
using namespace std;

typedef struct Song {
    string title;
    string artist;
    int ratings[3];
    struct Song *next;
    struct Song *prev;
} Song;

// Append a new song to the END of the list
Song *Append(Song *head, string sng, string sngr, int rate[3]) {
    Song *p = new Song;
    p->title = sng;
    p->artist = sngr;
    for (int i = 0; i < 3; i++)
        p->ratings[i] = rate[i];
    p->next = NULL;
    p->prev = NULL;

    if (head == NULL)
        return p;

    // Traverse to the last node
    Song *tail = head;
    while (tail->next != NULL)
        tail = tail->next;

    tail->next = p;
    p->prev = tail;
    return head;
}

// Display the entire list, highlighting the current song
void Display(Song *head, Song *current) {
    if (head == NULL) {
        cout << "[ Empty playlist ]" << endl;
        return;
    }
    Song *temp = head;
    while (temp != NULL) {
        if (temp == current)
            cout << " --> [CURRENT] ";
        else
            cout << "              ";
        cout << "\"" << temp->title << "\" by " << temp->artist << " | Ratings: ";
        for (int i = 0; i < 3; i++) {
            cout << temp->ratings[i];
            if (i < 2) cout << ", ";
        }
        cout << endl;
        temp = temp->next;
    }
    cout << endl;
}

// Move current pointer to the NEXT song
Song *Next(Song *current) {
    if (current == NULL) {
        cout << "[!] No current song selected." << endl;
        return current;
    }
    if (current->next == NULL) {
        cout << "[!] Already at the last song." << endl;
        return current;
    }
    return current->next;
}

// Move current pointer to the PREVIOUS song
Song *Prev(Song *current) {
    if (current == NULL) {
        cout << "[!] No current song selected." << endl;
        return current;
    }
    if (current->prev == NULL) {
        cout << "[!] Already at the first song." << endl;
        return current;
    }
    return current->prev;
}

// Remove the currently selected song, reconnecting the list
// Returns the new head via reference, and the new current via return value
Song *RemoveCurrent(Song *&head, Song *current) {
    if (current == NULL) {
        cout << "[!] No current song to remove." << endl;
        return NULL;
    }

    Song *newCurrent = NULL;

    // Reconnect neighbours
    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        head = current->next;   // current was the head

    if (current->next != NULL)
        current->next->prev = current->prev;

    // Choose new current: prefer next, else prev
    if (current->next != NULL)
        newCurrent = current->next;
    else
        newCurrent = current->prev;

    cout << "[+] Removed: \"" << current->title << "\"" << endl;
    delete current;
    return newCurrent;
}

int main() {
    Song *head    = NULL;
    Song *current = NULL;
    string song, singer;
    int rating[3];

    cout << "========================================" << endl;
    cout << "    Music Playlist Manager (DLL)        " << endl;
    cout << "========================================" << endl;
    cout << "Commands: EXIT | NEXT | PREV | REMOVE" << endl << endl;

    while (true) {
        cout << "Enter a song title (or command): ";
        cin >> song;

        if (song == "EXIT") break;

        if (song == "NEXT") {
            current = Next(current);
            Display(head, current);
            continue;
        }
        if (song == "PREV") {
            current = Prev(current);
            Display(head, current);
            continue;
        }
        if (song == "REMOVE") {
            current = RemoveCurrent(head, current);
            Display(head, current);
            continue;
        }

        cout << "Enter artist name: ";
        cin >> singer;
        for (int i = 0; i < 3; i++) {
            cout << "Enter rating #" << i + 1 << ": ";
            cin >> rating[i];
        }

        head = Append(head, song, singer, rating);

        // If this is the first song, set it as current
        if (current == NULL)
            current = head;

        Display(head, current);
    }

    // Free all nodes
    Song *temp = head;
    while (temp != NULL) {
        Song *next = temp->next;
        delete temp;
        temp = next;
    }

    cout << "Program finished." << endl;
    return 0;
}