#include "BitonicSorter.h"


using namespace std;


template <typename T>
void print( vector<T> vec )
{
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter << ',';
    }
    std::cout << std::endl;
}

int main()
{
    int arrLen = 18;
    float *arr = new float[arrLen]{ 4, 13, 999999, 1, 7, 2, 3, 88888, 7777, 10, 12, 9, 11, 5, 666, 6, 0, 8 };
    vector<float> vec( arr, arr + arrLen );

    for (int i = 1; i <= 8; ++i) {
        vector<float> vec( arr, arr + i );
        print( vec );
        bitonicSort_Ascend( vec, *max_element( vec.begin(), vec.end() ) );
        print( vec );
        cout << endl;
    }

    BitonicSorter<float, float*> arraySorter( arr, arrLen );
    arraySorter.print();
    arraySorter.sort( true );
    arraySorter.print();
    cout << endl;

    BitonicSorter<float, vector<float>> vectorSorter( vec, GreatestPowerOf2LessThan( vec.size() ) );
    vectorSorter.print();
    vectorSorter.sort( false );
    vectorSorter.print();

    return 0;
}

