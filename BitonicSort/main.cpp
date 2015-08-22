#include "BitonicSorter.h"


using namespace std;


int main()
{
    int arrLen = 18;
    float *arr = new float[arrLen]{ 4, 18, 1, 7, 3, 10, 15, 12, 9, 5, 6, 17, 8, 2, 13, 11, 16, 14 };
    vector<float> vec( arr, arr + arrLen );

    BitonicSorter<float, float*> arraySorter( arr, arrLen );
    arraySorter.sort( true );
    arraySorter.print();

    BitonicSorter<float, vector<float>> vectorSorter( vec, vec.size() );
    vectorSorter.sort( true );
    vectorSorter.print();

    return 0;
}

