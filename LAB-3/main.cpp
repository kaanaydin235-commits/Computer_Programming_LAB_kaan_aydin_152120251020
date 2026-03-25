#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>

struct Page {
    std::string url;
    std::string title;
    int accessTime[3]; 
    Page* next;
    Page* prev;

    Page(const std::string& u, const std::string& t, int h, int m, int s)
        : url(u), title(t), next(nullptr), prev(nullptr) {
        accessTime[0] = h; accessTime[1] = m; accessTime[2] = s;
    }
};

class History {
private:
    Page* head;
    Page* tail;
    Page* current;
public:
    History() : head(nullptr), tail(nullptr), current(nullptr) {}

    ~History() { clear(); }

    void visit(const std::string& url, const std::string& title, int h, int m, int s) {
        Page* p = new Page(url, title, h, m, s);
        if (!head) {
            head = tail = current = p;
        } else {
            // append to tail
            tail->next = p;
            p->prev = tail;
            tail = p;
            current = p; // current moves to new page
        }
        std::cout << "Visited: " << url << " (" << title << ") at ";
        printTime(h,m,s);
        std::cout << '\n';
    }

    void back() {
        if (!current) { std::cout << "History is empty.\n"; return; }
        if (current->prev) {
            current = current->prev;
            std::cout << "Moved back to: " << current->url << "\n";
        } else {
            std::cout << "Already at the oldest entry.\n";
        }
    }

    void forward() {
        if (!current) { std::cout << "History is empty.\n"; return; }
        if (current->next) {
            current = current->next;
            std::cout << "Moved forward to: " << current->url << "\n";
        } else {
            std::cout << "Already at the newest entry.\n";
        }
    }

    void deleteCurrent() {
        if (!current) { std::cout << "History is empty.\n"; return; }
        Page* toDelete = current;
        std::cout << "Deleting: " << toDelete->url << "\n";
    
        if (toDelete->prev) toDelete->prev->next = toDelete->next; else head = toDelete->next;
        if (toDelete->next) toDelete->next->prev = toDelete->prev; else tail = toDelete->prev;
    
        if (toDelete->next) current = toDelete->next;
        else if (toDelete->prev) current = toDelete->prev;
        else current = nullptr;
        delete toDelete;
    }

    void display() const {
        if (!head) {
            std::cout << "History is empty.\n";
            return;
        }
        std::cout << "\n--- Browser History ---\n";
        int idx = 1;
        for (Page* p = head; p; p = p->next, ++idx) {
        
            std::cout << idx << ". " << p->url << " | " << p->title << " | ";
            printTime(p->accessTime[0], p->accessTime[1], p->accessTime[2]);
            if (p == current) std::cout << "  <-- current";
            std::cout << "\n";
        }
    }

    void clear() {
        Page* p = head;
        while (p) {
            Page* nxt = p->next;
            delete p;
            p = nxt;
        }
        head = tail = current = nullptr;
    }

    static void printTime(int h, int m, int s) {
        char buf[16];
        std::snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);
        std::cout << buf;
    }
};


void getCurrentTime(int &h, int &m, int &s) {
    std::time_t t = std::time(nullptr);
    std::tm *lt = std::localtime(&t);
    h = lt->tm_hour; m = lt->tm_min; s = lt->tm_sec;
}

int main() {
    History hist;
    while (true) {
        std::cout << "\n--- History Menu ---\n";
        std::cout << "1. Visit (append)\n";
        std::cout << "2. Back\n";
        std::cout << "3. Forward\n";
        std::cout << "4. Delete current entry\n";
        std::cout << "5. Display history\n";
        std::cout << "6. Exit\n";
        std::cout << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::string url, title;
            int h,m,s;
            std::cout << "Enter URL: "; std::getline(std::cin, url);
            std::cout << "Enter title: "; std::getline(std::cin, title);
            std::cout << "Use current time? (y/n): ";
            char c; std::cin >> c; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (c == 'y' || c == 'Y') getCurrentTime(h,m,s);
            else {
                std::cout << "Enter hour minute second: ";
                std::cin >> h >> m >> s; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            hist.visit(url,title,h,m,s);
        } else if (choice == 2) {
            hist.back();
        } else if (choice == 3) {
            hist.forward();
        } else if (choice == 4) {
            hist.deleteCurrent();
        } else if (choice == 5) {
            hist.display();
        } else if (choice == 6) {
            std::cout << "Exiting and freeing history...\n";
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}
