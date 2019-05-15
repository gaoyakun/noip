#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <iterator>
#include <cstddef>

template <class T>
class DoubleList {
    struct Node {
        T data;
        Node *prev;
        Node *next;
    };
    Node *head;
    size_t count;
public:
    struct iterator {
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        Node *node;
        explicit iterator (Node *p): node(p) {
        }
        reference operator * () const {
            return node->data;
        }
        pointer operator -> () const {
            return &node->data;
        }
        iterator &operator ++ () {
            node = node->next;
            return *this;
        }
        iterator operator ++ (int) {
            iterator ret(node);
            node = node->next;
            return ret;
        }
        iterator &operator -- () {
            node = node->prev;
            return *this;
        }
        iterator operator -- (int) {
            iterator ret(node);
            node = node->prev;
            return ret;
        }
        bool operator == (iterator other) const {
            return node == other.node;
        }
    };
    DoubleList () {
        head = new Node ();
        head->prev = head;
        head->next = head;
        count = 0;
    }
    virtual ~DoubleList () {
        while (head->next != head) {
            Node *p = head->next;
            head->next = p->next;
            delete p;
        }
        delete head;
    }
    iterator insert (iterator pos, const T &data) {
        Node *node = new Node;
        node->data = data;
        node->next = pos.node;
        node->prev = pos.node->prev;
        node->next->prev = node;
        node->prev->next = node;
        count++;
        return iterator(node);
    }
    iterator erase (iterator pos) {
        iterator ret(pos.node->next);
        pos.node->prev->next = pos.node->next;
        pos.node->next->prev = pos.node->prev;
        delete pos.node;
        count--;
        return ret;
    }
    void push_front (const T &data) {
        insert (begin(), data);
    }
    void push_back (const T &data) {
        insert (end(), data);
    }
    iterator begin () const {
        return iterator(head->next);
    }
    iterator end () const {
        return iterator(head);
    }
    size_t size () const {
        return count;
    }
};

#endif // __DOUBLE_LIST_H__
