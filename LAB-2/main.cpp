#include <iostream>
#include <string>
#include <limits>

struct Node {
    std::string title;
    Node* next;
    Node(const std::string& t) : title(t), next(nullptr) {}
};
Node* addSong(Node* head, const std::string& title) {
    Node* n = new Node(title);
    n->next = head;
    return n;
}
int searchSong(Node* head, const std::string& title) {
    Node* cur = head;
    int pos = 1;
    while (cur) {
        if (cur->title == title) return pos;
        cur = cur->next;
        ++pos;
    }
    return 0;
}
void listSongs(Node* head) {

    if (!head) {
        std::cout << "Playlist is empty." << std::endl;
        return;
    }
    Node* cur = head;
    int position = 1;
    while (cur) {
        std::cout << position << ". " << cur->title << std::endl;
        cur = cur->next;
        ++position;
    }
}


void freeList(Node* head) {
    while (head) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

int main() {
    Node* head = nullptr;
    
    head = addSong(head, "Shut Up And Drive");
    head = addSong(head, "Love Story");
    head = addSong(head, "Numb");
    while (true) {
        std::cout << "\n--- Playlist Menu ---\n";
        std::cout << "1. Add Song (to top)\n";
        std::cout << "2. Search Song\n";
        std::cout << "3. List Songs\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 1) {
            std::cout << "Enter song title: ";
            std::string title;
            std::getline(std::cin, title);
            if (title.empty()) {
                std::cout << "Empty title ignored." << std::endl;
            } else {
                head = addSong(head, title);
                std::cout << "Added '" << title << "' to top of playlist." << std::endl;
            }
        } else if (choice == 2) {
            if (!head) { std::cout << "Playlist is empty." << std::endl; continue; }
            std::cout << "Enter title to search: ";
            std::string title;
            std::getline(std::cin, title);
            int pos = searchSong(head, title);
            if (pos) std::cout << "Found '" << title << "' at position " << pos << "." << std::endl;
            else std::cout << "'" << title << "' not found in playlist." << std::endl;
        } else if (choice == 3) {
            std::cout << "\nCurrent playlist:\n";
            listSongs(head);
        } else if (choice == 4) {
            std::cout << "Exiting..." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please enter 1-4." << std::endl;
        }
    }
    freeList(head);
    return 0;
}

