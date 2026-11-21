/*
 * ==============================================================================
 *  Smart Music Playlist — Circular & Doubly Linked List Engine
 *  Air University — Department of Creative Technology
 *  Course: CS210 (Data Structures & Algorithms)
 *  Author: Muhammad Ahad Ali (2503605) | BSDS-3A
 *  Instructor: Ma'am Umme Sadima
 * ==============================================================================
 *  Core Data Structures Principles:
 *    • Dynamic Node Allocation & Pointer Stitching
 *    • O(1) Constant Time Next/Previous Pointer Traversal
 *    • Circular Wrap-Around Without Boundary Checks
 *    • Asymptotic Complexity: O(1) Insertion & Deletion after Current Node
 * ==============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

namespace Color {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string EMERALD = "\033[32m";
    const string CYAN    = "\033[36m";
    const string YELLOW  = "\033[33m";
    const string PURPLE  = "\033[35m";
    const string RED     = "\033[31m";
}

struct Node {
    string song;
    Node* next;
    Node* prev;

    Node(string title) : song(title), next(nullptr), prev(nullptr) {}
};

class SmartPlaylist {
private:
    Node* head;
    Node* current;
    int size;

public:
    SmartPlaylist() : head(nullptr), current(nullptr), size(0) {}

    ~SmartPlaylist() {
        if (!head) return;
        Node* temp = head;
        do {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        head = nullptr;
        current = nullptr;
    }

    void addSong(const string& title) {
        Node* newNode = new Node(title);
        if (!head) {
            head = newNode;
            current = newNode;
            newNode->next = head;
            newNode->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        size++;
    }

    void insertAfterCurrent(const string& title) {
        if (!head) {
            addSong(title);
            return;
        }
        Node* newNode = new Node(title);
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        size++;
        cout << Color::EMERALD << "  [SUCCESS] Inserted '" << title << "' immediately after '" << current->song << "'.\n" << Color::RESET;
    }

    void deleteCurrent() {
        if (!head) {
            cout << Color::RED << "  [ERROR] Playlist is empty. Nothing to delete.\n" << Color::RESET;
            return;
        }

        string removedTitle = current->song;
        if (size == 1) {
            delete head;
            head = nullptr;
            current = nullptr;
            size = 0;
        } else {
            Node* toDelete = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;

            if (current == head) {
                head = current->next;
            }
            current = current->next;
            delete toDelete;
            size--;
        }

        cout << Color::YELLOW << "  [DELETED] '" << removedTitle << "' removed. Now playing: " 
             << (current ? current->song : "None") << "\n" << Color::RESET;
    }

    void playNext() {
        if (!current) {
            cout << Color::RED << "  [EMPTY] Playlist contains no tracks.\n" << Color::RESET;
            return;
        }
        current = current->next;
        cout << Color::CYAN << Color::BOLD << "  ⏭️ Now Playing (Next): " << current->song << Color::RESET;
        if (current == head) cout << Color::YELLOW << " [🔁 Wrapped around to Head!]" << Color::RESET;
        cout << "\n";
    }

    void playPrev() {
        if (!current) {
            cout << Color::RED << "  [EMPTY] Playlist contains no tracks.\n" << Color::RESET;
            return;
        }
        current = current->prev;
        cout << Color::PURPLE << Color::BOLD << "  ⏮️ Now Playing (Previous): " << current->song << Color::RESET << "\n";
    }

    void display() const {
        if (!head) {
            cout << Color::RED << "  Playlist is empty.\n" << Color::RESET;
            return;
        }

        cout << Color::BOLD << "\n  === 🎵 CURRENT SMART PLAYLIST TOPOLOGY (" << size << " Tracks) ===\n" << Color::RESET;
        Node* temp = head;
        int idx = 1;
        do {
            if (temp == current) {
                cout << Color::EMERALD << Color::BOLD << "  ▶ [" << idx << "] " << temp->song << " (CURRENT)" << Color::RESET;
            } else if (temp == head) {
                cout << Color::CYAN << "    [" << idx << "] " << temp->song << " (HEAD)" << Color::RESET;
            } else {
                cout << "    [" << idx << "] " << temp->song;
            }
            cout << "  ⇄  ";
            temp = temp->next;
            idx++;
        } while (temp != head);
        cout << Color::YELLOW << "(Back to Head)\n\n" << Color::RESET;
    }

    bool search(const string& query) const {
        if (!head) return false;
        Node* temp = head;
        do {
            if (temp->song == query) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    void playOneCompleteRound() const {
        if (!current) {
            cout << Color::RED << "  Playlist is empty.\n" << Color::RESET;
            return;
        }
        cout << Color::BOLD << Color::YELLOW << "\n  [CIRCULAR ROUND-ROBIN] Playing 1 complete cycle from current:\n" << Color::RESET;
        Node* temp = current;
        int step = 1;
        do {
            cout << "    " << step << ". 🎶 " << temp->song << "\n";
            temp = temp->next;
            step++;
        } while (temp != current);
        cout << Color::EMERALD << "  [COMPLETE] Safely returned to starting track: " << current->song << "\n\n" << Color::RESET;
    }
};

int main() {
    cout << Color::BOLD << Color::EMERALD << R"(
========================================================================
   ____                      _     __  __           _      
  / ___|_ __ ___   __ _ _ __| |_  |  \/  |_   _ ___(_) ___ 
  \___ \ '_ ` _ \ / _` | '__| __| | |\/| | | | / __| |/ __|
   ___) | | | | | (_| | |  | |_  | |  | | |_| \__ \ | (__ 
  |____/|_| |_| |_|\__,_|_|   \__| |_|  |_|\__,_|___/_|\___|
========================================================================
)" << Color::RESET;
    cout << Color::CYAN << "  Circular & Doubly Linked List Engine • Asymptotic O(1) Traversal\n" << Color::RESET;

    SmartPlaylist playlist;
    // Load assignment defaults
    playlist.addSong("National Treasure");
    playlist.addSong("Loosing Myself");
    playlist.addSong("Dark Knight");

    playlist.display();
    playlist.playOneCompleteRound();

    cout << "\n  [Testing Dynamic Operations]\n";
    playlist.insertAfterCurrent("Peaky Blinders Theme Song");
    playlist.display();

    playlist.playNext();
    playlist.playNext();

    cout << "\n  [Testing Circular Wrap-Around]\n";
    playlist.playNext();

    cout << "\n  [Testing Search]\n";
    cout << "  Search 'Opera' : " << (playlist.search("Opera") ? "Found!" : "Not Found!") << "\n";
    cout << "  Search 'Dark Knight' : " << (playlist.search("Dark Knight") ? "Found!" : "Not Found!") << "\n";

    cout << "\n  For live animated pointer canvas, open 'web/index.html' in your browser!\n\n";
    return 0;
}
