#include <iostream>
#include "../Lists/LinkedList.hpp"

using namespace std;

int main(int argc, char* argv[]){
    LinkedList<int> list;
    
    cout << "-------------Testing append, moveToPos and insert operators -------------" << endl;
    list.append(1);
    list.append(2);
    list.append(3);
    list.moveToPos(1);
    list.insert(5);
    cout << "-------------Testing getLength() operator-------------" << endl;
    cout << list.getLength() << endl; // Should print 4
    cout << "-------------Testing print operator-------------" << endl;
    cout << list << endl; // Should print 1 5 2 3
    cout << "-------------Testing {} constructor-------------" << endl;
    LinkedList<int> list2 = {1, 2, 3, 4, 5, 7, 8, -1, -2};
    cout << list2 << endl;
    cout << "-------------Testing clear method-------------" << endl;
    list2.clear();
    cout << list2 << endl;
    cout << "-------------Testing iterator constructor-------------" << endl;
    vector<int> v = {1, 2, 4, 5, 67, 78};
    LinkedList<int> list3((v.begin()+2), (v.end())-1);
    cout << list3 << endl;
    cout << "-------------Testing [] operator-------------" << endl;
    list[2] = 100000;
    cout << list << endl;
    list[10] = 5;// Should throw an out_of_range exception
    return 0;
}
