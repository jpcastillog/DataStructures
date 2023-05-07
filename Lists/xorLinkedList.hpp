#ifndef XORLINKEDLIST_H
#define XORLINKEDLIST_H

template<typename TypeElem>
struct Node {
    Node *xordir;
    TypeElem data;
};

template<typename TypeElem>
class xorLinkedList{
    private:
        Node<TypeElem> *curr;
        Node<TypeElem> *prev;
        Node<TypeElem> *next;
        Node<TypeElem> *head;
        Node<TypeElem> *tail;
        uitn32_t legth;
        uint32_t currPos;
    public:
        
};


#endif