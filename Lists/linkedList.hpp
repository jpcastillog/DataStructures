#ifndef LINKEDLIST_H
#define LINKKEDLIST_H

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
        uint32_t length;
        uint32_t currPos;

    public:
        LinkedList(){
            curr = tail = head = new Node<TypeElem>;
            length = 0;
            currPos = 0;
        }

        void clear(){
            currPos = 0;
            curr = head->next;
            Node<TypeElem> *tmp;
            for (uint32_t i = 0; i < length; ++i) {
                tmp = curr->next;
                delete curr;
                curr = tmp;
            }
            length = 0;
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
            return item
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

        inline int length() {
            return LinkedList::length; 
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
