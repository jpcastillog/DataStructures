#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <sstream>
#include <initializer_list>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;
template<typename TypeElem>
struct Node {
    Node *next;
    TypeElem data;
};

template<typename TypeElem> 
class LinkedList{
    private:
        Node<TypeElem> *head;
        Node<TypeElem> *curr;
        Node<TypeElem> *tail;
        size_t length;
        size_t currPos;

    public:
        LinkedList(){
            curr = tail = head = new Node<TypeElem>;
            length = 0;
            currPos = 0;
        };

        LinkedList(initializer_list<TypeElem> values) : LinkedList() {
            for (const auto& item : values)
                this->append(item);
        };

        LinkedList(TypeElem * begin, TypeElem * end): LinkedList() {
            size_t size = end - begin;
            TypeElem* it = begin;
            for (size_t i=0; i < size; ++i, it++)
                this->append(*it);
        };

        template<class Iterator>
        LinkedList(Iterator begin, Iterator end): 
            LinkedList(&(*begin), &(*end)) {};
        
        ~LinkedList(){
            this->clear();
            delete head;
        };

        
        friend ostream& operator<<(ostream &os, const LinkedList<TypeElem> &list) {
            Node<TypeElem> *aux;
            os << "[";
            if (list.getLength() > 0) {
                aux = list.head->next;
            
                for (size_t i = 0; i < list.getLength() - 1; ++i) {
                    os << aux->data << ", ";
                    aux = aux->next;
                }
                os  << aux->data;
            }
            os << "]";
            return os;
        };

        friend istream& operator>>(istream &is, LinkedList<TypeElem> &list) {
            TypeElem item;
            while (is >> item) {
                list.append(item);
            }
            return is;
        };

        size_t operator++() {
            if (currPos == length - 1)
                return length;
            else {
                curr = curr -> next;
                currPos++;
            }
        };

        size_t operator--() {
            if (currPos == 0)
                return 0;
            else {
                Node<TypeElem> *aux = head;
                for (size_t i=0; i < currPos - 1; ++i)
                    this->next();
            }
            return --currPos;
        };

        LinkedList<TypeElem>& operator + (const LinkedList<TypeElem> &list) {
            LinkedList<TypeElem> newList = LinkedList<TypeElem>();
            size_t i = 0;
            for(i = 0; i < this->length; ++i) {
                newList.append(this->getValue());
                this->next();
            };
            for(i = 0; i < list.length; ++i) {
                newList.append(list.getValue());
                list.next();
            };
            return newList;
        };

        TypeElem& operator[](size_t pos) {
            if (pos < 0 or pos >= this->getLength()) {
                stringstream ss;
                ss << "Index " << pos << " out of range";
                throw std::out_of_range(ss.str());
            }
            else {
                Node <TypeElem> *aux = head;
                for (size_t i=0; i < pos; ++i)
                    aux = aux->next;
                return aux->next->data;
            }
        };

        inline size_t getLength() const {
            return this->length; 
        };

        inline size_t getCurrPos() const {
            return currPos;
        };

        size_t concatenate(const LinkedList<TypeElem> &list){
           while (list.getCurrPos() < list.getLength()) {
                this->append(list.getValue());
                list.next();
           }
           return this->length; 
        };

        void clear(){
            curr = head->next;
            Node<TypeElem> *tmp;
            for (size_t i = 0; i < this->getLength(); ++i) {
                tmp = curr->next;
                delete curr;
                curr = tmp;
            }
            cout << "ok deleting list \n";
            currPos = 0;
            curr=nullptr;
            this->length = 0;
            tail=curr=head;
        };

        int insert(TypeElem item) {
            Node<TypeElem> *tmp = curr->next;
            curr->next = new Node<TypeElem>;
            curr->next->data = item;
            curr->next->next = tmp;
            length++;
            if (curr == tail) 
                tail = curr->next;
            return currPos;
        };

        int append(TypeElem item){
            tail->next = new Node<TypeElem>;
            tail = tail->next;
            tail->data = item;
            tail->next = NULL;
            length++;
            return length;
        };
        
        TypeElem erase(){
            TypeElem item;
            item = curr->next->data;
            Node<TypeElem> *tmp = curr->next->next;
            if (curr->next == tail) 
                tail = curr;
            delete curr->next;
            curr->next = tmp;
            length--;
            return item;
        };
        
        inline void moveToStart(){
            curr = head;
            currPos = 0;
        };

        inline void moveToEnd(){
            curr = tail;
            currPos = length - 1;
        };
        
        inline void next(){
            if (curr == tail)
                return;
            curr = curr->next;
            currPos++;
        };

        void prev() {
            if (curr == head) return;
            Node<TypeElem> *tmp = head;
            while(tmp->next != curr){
                tmp = tmp->next;
            }
            curr = tmp;
            currPos--;
        };
        
        void moveToPos(int pos) {
            if (pos < 0 || pos > length-1) return;
            Node<TypeElem> *tmp;
            tmp = head;
            for (uint32_t i=0; i<pos; ++i) {
                tmp = tmp->next;
            }
            curr = tmp;
            currPos = pos;
        };
        
        inline TypeElem getValue() {
            return curr->next->data;
        };
};

#endif