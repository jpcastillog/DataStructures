#include <iostream>

template<typename T, typename Type_p>
void partition(T begin, T end, size_t p){
    
    return;
};

template<typename T>
void quickSort(T begin, T end){
    return;
};

template<typename T>
void merge(T beginLeft, T endLeft,
           T beginRight, T endRight, 
           T beginAux){
    T L = beginLeft;
    T R = beginRight;
    T A = beginAux;

    size_t sizeL = endLeft - beginLeft;
    size_t sizeR = endRight - beginRight;
    
    size_t i=0;
    size_t j=0;
    size_t k=0;
    while (i < sizeL and j < sizeR) {
        if (L[i] < R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }
    while (i < sizeL)
        A[k++] = L[i++];
    while (j < sizeR)
        A[k++] = R[j++];
};

template<typename T>
void mergeSortHelper(T begin, T end, T beginAux){
    if (end - begin == 1)
        return;
    size_t mid = (end - begin) / 2;
    mergeSortHelper(begin, &begin[mid], beginAux);
    mergeSortHelper(&begin[mid+1], end, beginAux);
    // Copy the elements to the auxiliary array,
    for(size_t i = 0; i < (end - begin); i++) beginAux[i] = begin[i];
    // In the end begin have the sorted elements.
    merge(beginAux, &beginAux[mid],
          &beginAux[mid+1], &beginAux[end],
          begin);
};

template<typename T>
void mergeSort(T begin, T end){
    T beginAux = new T[end - begin];
    mergeSortHelper(begin, end, beginAux);
    delete[] beginAux;
};

template<typename T>
void heapSort(T begin, T end){
    return;
}