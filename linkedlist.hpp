#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T newData) : data(newData), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(T newData) {
        Node<T>* newNode = new Node<T>(newData);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void remove(T data) {
        if (head == nullptr) {
            std::cout << "Список пуст =(" << "\n";
            return;
        }

        Node<T>* temp = head;
        Node<T>* prev = nullptr;

        while (temp != nullptr && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            std::cout << "Элемент не найден =(" << "\n";
            return;
        }

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        delete temp;
        std::cout << "Элемент удален =(" << "\n";
    }

    bool search(T data) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void display() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            Node<T>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    LinkedList<int> myList;

    myList.insert(5);
    myList.insert(10);
    myList.insert(15);
    myList.insert(20);

    std::cout << "Список: " << "\n";
    myList.display();

    myList.remove(10);
    std::cout << "Список после удаления элемента: " << "\n";
    myList.display();

    std::cout << "Результат поиска элемента 15: " << (myList.search(15) ? "Найден" : "Не найден") << "\n";
}
