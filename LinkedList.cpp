#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

template <typename T> class Node {
public:
  T data;
  Node<T> *next;
};

template <typename T> class LinkedList {
private:
  Node<T> *head;
  int size;

public:
  LinkedList() {
    head = nullptr;
    size = 0;
  }
  LinkedList(const LinkedList &other) : head(other.head), size(other.size){};
  LinkedList(LinkedList &&other) noexcept : head(other.head), size(other.size) {
    other.head = nullptr;
    other.size = 0;
  };
  LinkedList &operator=(const LinkedList &other) = default;

  // ~LinkedList() { clear(); }

  void log() {
    auto c = head;
    while (c != nullptr) {
      std::cout << c->data << " ";
      c = c->next;
    }
  }
  void push_back(const T &value) {
    Node<T> *newNode = new Node<T>();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
      head = newNode;
    } else {
      Node<T> *current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }
    size++;
  }

  void insert(int index, T value) {
    if (index < 0 || index > size) {
      return;
    }

    Node<T> *newNode = new Node<T>();
    newNode->data = value;

    if (index == 0) {
      newNode->next = head;
      head = newNode;
    } else {
      Node<T> *current = head;
      for (int i = 0; i < index - 1; i++) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }
    size++;
  }
  void erase(int index) {
    if (index < 0 || index >= size) {
      return;
    }

    if (index == 0) {
      Node<T> *current = head;
      head = head->next;
      delete current;
    } else {
      Node<T> *current = head;
      for (int i = 0; i < index - 1; i++) {
        current = current->next;
      }
      Node<T> *next = current->next;
      current->next = next->next;
      delete next;
    }
    size--;
  }

  void clear() {
    while (head != nullptr) {
      Node<T> *current = head;
      head = head->next;
      delete current;
    }
    size = 0;
  }

  T operator[](int index) {
    if (index < 0 || index >= size) {
      return T();
    }

    Node<T> *current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  int getSize() { return size; }
  T getHead() { return head->data; }
  bool find(const T &value, bool t) {
    if (t == true) {
      Node<T> *current = head;
      while (current != nullptr) {
        if (current->data == value) {
          return true;
        }
        current = current->next;
      }
      return false;
    }
    return false;
  }
  // range-based for loop
public:
  class Iterator {
  public:
    Iterator(Node<T> *node) : current(node) {}

    T &operator*() { return current->data; }
    Iterator &operator++() {
      current = current->next;
      return *this;
    }
    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }
    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

  private:
    Node<T> *current;
  };

  Iterator begin() { return Iterator(head); }
  Iterator end() { return Iterator(nullptr); }
  Iterator find(const std::string &value) {
    Iterator it = begin();
    Iterator end_it = end();
    while (it != end_it) {
      if ((*it).word == value) {
        return it;
      }
      ++it;
    }
    return end_it;
  }
};
