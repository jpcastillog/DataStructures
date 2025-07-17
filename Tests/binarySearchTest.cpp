#include "../Algorithms/search.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Example usage of binary search functions
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Searching for an element
    int x = 5;

    cout << "---------- Test Binary Search 2 Branches ----------\n";
    size_t index = binarySearch2Branches(arr.begin(), arr.end(), x);
    
    if (index < arr.size()) {
        std::cout << "Element " << x << " found at index: " << index << std::endl;
    } else {
        std::cout << "Element " << x << " not found." << std::endl;
    }
    cout << "---------- Test Binary Search 3 Branches ----------\n";
    index = binarySearch3Branches(arr.begin(), arr.end(), x);
    
    if (index < arr.size()) {
        std::cout << "Element " << x << " found at index: " << index << std::endl;
    } else {
        std::cout << "Element " << x << " not found." << std::endl;
    }

    cout << "---------- Test Galloping Search ----------\n";
    index = gallopingSearch(arr.begin(), arr.end(), x);
    
    if (index < arr.size()) {
        std::cout << "Element " << x << " found at index: " << index << std::endl;
    } else {
        std::cout << "Element " << x << " not found." << std::endl;
    }
    
    return 0;
}
