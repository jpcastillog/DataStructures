#include <iostream>
/**
    * @param begin: pointer or iterator to the first element of the array
    * @param end: pointer or iterator to the last element of the array
    * @param x: value to search in the array
    * @return: index of the value in the array, or size if not found
    **Time complexity Theta(lg(n)) 
*/
template<typename Type_it, typename Type_target>
size_t binarySearch2Branches(const Type_it begin, const Type_it end, Type_target x){
    size_t size = end - begin + 1;
    size_t left = 0;
    size_t right = size - 1;
    while(left < right){
        /*
        mid + left  = (left + right)/2 +left
        mid = left + left/2 + right/2 - left
        mid = left + (right - left)/2
        */
        size_t mid = left + (right - left) / 2;
        if (x <= begin[mid])
            right = mid;
        else
            left = mid + 1;
    }
    if (begin[left] == x)
        return left;
    return size; // Not found, return size as an invalid index
};

/** 
 * @param begin: pointer or iterator to the first element of the array
 * @param end: pointer or iterator to the last element of the array
 * @param x: value to search in the array
 * * Time complexity O(lg(n))
 */
template<typename Type_it, typename Type_target>
size_t binarySearch3Branches(const Type_it begin, const Type_it end, Type_target x){
    size_t size = end - begin + 1;
    size_t left = 0;
    size_t right = size - 1;
    while(left <= right){
        size_t mid = left + (right - left) / 2;
        if (begin[mid] == x)
            return mid;
        else if (x < begin[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return size;
};

/**
 * @param begin: pointer or iterator to the first element of the array
 * @param end: pointer or iterator to the last element of the array
 * @param x: value to search in the array
 * * Time complexity Theta(lg(i)), where i is the position of x in the array
 */
template<typename Type_it, typename Type_target>
size_t gallopingSearch(const Type_it begin, const Type_it end, Type_target x) {
    size_t size = end - begin + 1;
    if (size == 0) return size; // Empty array

    size_t index = 0;
    size_t step = 1;

    // Find the range where x might be present
    while (index < size && begin[index] <= x) {
        index += step;
        step *= 2; // Double the step size
    }

    // Perform binary search in the found range
    return index/2 + 
           binarySearch2Branches(begin + (index / 2),
                                 begin + std::min(index, size - 1), 
                                 x);
};