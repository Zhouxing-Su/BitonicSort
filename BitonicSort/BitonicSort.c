#include "BitonicSort.h"


// see [ http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 ]
// example [
//  cout << LeastPowerOf2NotLessThan( 3 ) << LeastPowerOf2NotLessThan( 4 ) << LeastPowerOf2NotLessThan( 5 ) << endl;
// ] output [ 448 ]
int LeastPowerOf2NotLessThan( int n )
{
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return (n + 1);
}

int GreatestPowerOf2LessThan( int n )
{
    return LeastPowerOf2NotLessThan( n ) >> 1;
}

void bitonicMerge( float *data, int len, int ascend )
{
    if (len <= 1) { return; }

    int halfLen = GreatestPowerOf2LessThan( len );
    int left = 0;
    int right = halfLen;
    for (int i = halfLen; i < len; ++i, ++left, ++right) {
        if ((data[left] > data[right]) == ascend) {
            float tmp = data[left];
            data[left] = data[right];
            data[right] = tmp;
        }
    }
    bitonicMerge( data, halfLen, ascend );
    bitonicMerge( data + halfLen, len - halfLen, ascend );
}

// if (ascend == true), the data will be sorted in ascending order
void bitonicSort( float *data, int len, int ascend )
{
    if (len <= 1) { return; }

    int halfLen = len / 2;
    bitonicSort( data, halfLen, !ascend );
    bitonicSort( data + halfLen, len - halfLen, ascend );

    bitonicMerge( data, len, ascend );
}

void segmentedBitonicSort( float* data, int* seg_id, int* seg_start, int len, int seg_num )
{
    for (int i = 0; i < seg_num; ++i) {
        bitonicSort( data + seg_start[i], seg_start[i + 1] - seg_start[i], !0 );
    }
}