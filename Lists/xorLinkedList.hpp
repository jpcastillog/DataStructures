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
        xorLinkedList(){
            head = tail = curr = prev = next = NULL;
            length = 0;
            currPos = 0;
        };

        void clear(){
            currPos = 0;
            curr = head;
            Node<TypeElem> *tmp;
            while (curr != tail){
                tmp = (curr->xordir)^prev;
                prev = curr;
                curr = tmp;
                next = (curr->xordir)^prev;
                delete curr;
            }
            length = 0;
            head = tail = curr = prev = next = NULL;
        };

        // Insert item in curr position.
        int insert(TypeElem item){
            Node<TypeElem> *tmp;
            Node<TypeElem> *newNode = new Node<TypeElem>;
            newNode->data=item;
            newNode->xordir = (curr^next);
            // Update directions for current node
            curr->xordir = (prev^newNode);
            if (curr == tail)
                tail == newNode;
            else {
                // Update directions of next node
                tmp = (next->xordir)^curr;
                next->xordir = (curr^tmp);
                // Update next pointer of Class
                next = newNode;
            }
            length++;
            return currPos;
        };

        int append(TypeElem item){
            Node<TypeElem> *newNode = new Node<TypeElem>;
            newNode->data = item;
            newNode->xordir = (curr^nullptr);
            // Update directions of ex tail
            tail->xordir = (tail->data^nullptr)^newNode;
            // Update the tail
            tail = newNode;
            length++;
            return length;
        };

        TypeElem erase(){
            TypeElem item;
            item = curr->data;
            Node<TypeElem>* tmp = curr;
            if (curr == tail){
                //update tail with previous element
                tail = (curr->xordir)^next;
                //previous element, its the previous of previous
                prev = ((curr->xordir)^next)^curr;
                tail->xordir = prev^nullptr;
                //curr now its the previous element
                curr = (curr->xordir)^next;
                curr->xordir = prev^nullptr;
                next = nullptr;
                pos--;
            }
            else if (curr == head){
                // head and curr is the next element
                curr = head = next;
                prev=nullptr;
                // next element is the next of next
                next = (next->xordir)^tmp;
                // update xor dir of current position,
                // because in the previous position is nothing.
                curr->xordir = nullptr^next;
            }
            else{
                // Curr is the next element
                curr = (curr->xordir)^prev;
                // The next element is next of current next
                next = (next->xordir)^tmp;
                next->xordir = ((next->xordir)^tmp)^curr;
                // update new curr xordir
                curr->xordir = prev^next;
                // Prev is the same (prev of curr)
                prev->xordir = ((prev->xordir)^tmp)^curr;
                
            }
            delete tmp;
            length--;
            return item;
        };

        inline void moveToStart(){
            curr = head;
            currPos = 0;
        };

        inline void moveToEnd(){
            curr = tail;
            currPos = length-1;
        };

        inline void next(){
            if(curr==tail) return;
            Node<TypeElem>* tmp = curr;
            curr = next;
            next = (next->xordir)^tmp;
            prev = tmp;
            currPos++;
        };

        inline void prev(){
            if (curr == head)   return;
            Node<TypeElem>* tmp = curr;
            curr = prev;
            prev = (prev->xordir)^tmp;
            next = tmp;
            currPos--;
        };

        inline uint32_t length(){
            return length;
        };

        void moveToPos(int pos){
            if (pos>=lenght) return;
            if (pos < 0) return;
            if (pos == currPos) return;
            else if (pos > currPos){
                while (currPos != pos) next();
            }
            else{
                while (currPos != pos) prev();
            }
        };

        inline TypeElem getValue(){
            return curr->data;
        };
};
#endif