#pragma once
#include <cstdint>
#include <iterator>
#include <initializer_list>

template<typename T>
class List {
    struct Node {
        Node* next = 0;
        Node* prev = 0;
        T* value = 0;
        ~Node() { delete value; }
    };
    Node head;
    unsigned long long size_;
public:
    struct iterator : std::iterator<std::bidirectional_iterator_tag, T> {
        Node* node;
        iterator() = delete;
        iterator(const iterator&) = default;
        iterator(Node* node_) : node(node_) {}
        iterator& operator++() { node = node->next; return *this; }
        iterator operator++(int) { iterator copy(*this); ++(*this); return copy; }
        iterator& operator--() { node = node->prev; return *this; }
        iterator operator--(int) { iterator copy(*this); --(*this); return copy; }
        bool operator==(iterator other) { return node == other.node; }
        bool operator!=(iterator other) { return !(*this == other); }
        T& operator*() { return *(node->value); }
    };
    List() : size_(0) {
        head.next = &head;
        head.prev = &head;
    }
    template<typename Iter>
    List(Iter first, const Iter last) : List() {
        Node* current_node = &head;
        while (first != last) {
            Node* new_node = new Node;
            new_node->prev = current_node;
            new_node->value = new T(*first);
            current_node->next = new_node;
            ++first;
            current_node = new_node;
            ++size_;
        }
        current_node->next = &head;
        head.prev = current_node;
    }
    List(std::initializer_list<T> init_list) : List(init_list.begin(), init_list.end()) { }
    ~List() { clear(); }
    iterator begin() { return iterator(head.next); }
    iterator end() { return iterator(&head); }
    void push_back(const T& val) {
        Node* new_node = new Node;
        new_node->value = new T(val);
        new_node->next = &head;
        new_node->prev = head.prev;
        new_node->prev->next = new_node;
        head.prev = new_node;
        ++size_;
    }
    iterator erase(iterator pos) {
        pos.node->next->prev = pos.node->prev;
        pos.node->prev->next = pos.node->next;
        auto ret = pos.node->next;
        delete pos.node;
        --size_;
        return ret;
    }
    T& at(size_t index) {
        return *std::next(begin(), index);
    }
    void clear() {
        Node* last, * curr = head.next;
        while (curr != &head) {
            last = curr;
            curr = curr->next;
            delete last;
        }
        head.next = &head;
        head.prev = &head;
        size_ = 0;
    }
    size_t size() const { return size_; }
    bool empty() const { return !size(); }
};