#include "BitonicSorter.h"


using namespace std;


int main()
{
    int arrLen = 18;
    float *arr = new float[arrLen]{ 4, 1, 7, 3, 10, 15, 12, 9, 5, 6, 8, 2, 13, 11, 16, 14, 18, 17 };
    vector<float> vec( arr, arr + arrLen );

    BitonicSorter<float, float*> arraySorter( arr, arrLen );
    arraySorter.print();
    arraySorter.sort( true );
    arraySorter.print();

    BitonicSorter<float, vector<float>> vectorSorter( vec, GreatestPowerOf2LessThan( vec.size() ) );
    vectorSorter.print();
    vectorSorter.sort_NonRecursive( false );
    vectorSorter.print();

    return 0;
}

