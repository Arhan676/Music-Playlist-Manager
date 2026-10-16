#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Every node stores one song and links to the songs on either side.
class Node {
public:
    string title;
    string artist;
    Node* prev;
    Node* next;

    Node(string songTitle, string artistName) {
        title = songTitle;
        artist = artistName;
        prev = nullptr;
        next = nullptr;
    }
};

class MusicPlaylist {
private:
    Node* head;       // first song in the playlist
    Node* current;    // song selected for playback

    // Print song details in one place so all menu options look consistent.
    void printSong(Node* song) {
        cout << song->title << " - " << song->artist;
    }

public:
    MusicPlaylist() {
        head = nullptr;
        current = nullptr;
    }

    // Clear dynamically allocated nodes before the program closes.
    ~MusicPlaylist() {
        Node* q = head;
        while (q != nullptr) {
            Node* p = q;           // p is the node to delete
            q = q->next;           // q moves ahead before p is deleted
            delete p;
        }
        head = nullptr;
        current = nullptr;
    }

    void addSong(string title, string artist) {
        Node* p = new Node(title, artist);  // p points to the new node

        if (head == nullptr) {
            head = p;
            current = p;  // the first song becomes the current song
        } else {
            Node* q = head; // q traverses the playlist
            while (q->next != nullptr) {
                q = q->next;
            }
            q->next = p;
            p->prev = q;
        }
        cout << "Song added successfully.\n";
    }

    void deleteSong(string title) {
        if (head == nullptr) {
            cout << "Playlist is empty. Nothing to delete.\n";
            return;
        }

        Node* q = head;  // find the song by its title
        while (q != nullptr && q->title != title) {
            q = q->next;
        }

        if (q == nullptr) {
            cout << "Song not found in the playlist.\n";
            return;
        }

        Node* p = q;  // p points to the song being deleted

        // If current is deleted, choose the next song; otherwise the previous.
        if (current == p) {
            if (p->next != nullptr)
                current = p->next;
            else
                current = p->prev;
        }

        if (p == head)
            head = p->next;

        if (p->prev != nullptr)
            p->prev->next = p->next;

        if (p->next != nullptr)
            p->next->prev = p->prev;

        cout << "Deleted: ";
        printSong(p);
        cout << "\n";
        delete p;
    }

    void displayPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* q = head;  // travel forward using next
        int number = 1;
        cout << "\nPlaylist (forward):\n";
        while (q != nullptr) {
            cout << number++ << ". ";
            printSong(q);
            if (q == current)
                cout << "  <-- Current";
            cout << "\n";
            q = q->next;
        }
    }

    void displayReverse() {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* q = head;
        while (q->next != nullptr)  // first reach the last song
            q = q->next;

        cout << "\nPlaylist (reverse):\n";
        int number = 1;
        while (q != nullptr) {
            cout << number++ << ". ";
            printSong(q);
            if (q == current)
                cout << "  <-- Current";
            cout << "\n";
            q = q->prev;         // now move backward using prev
        }
    }
