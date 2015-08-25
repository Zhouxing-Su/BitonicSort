#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "BitonicSort.h"


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

// if left < right, return true.
bool compare( float *data, int* segID, int left, int right )
{
    if (segID[left] != segID[right]) {
        return (segID[left] < segID[right]);
    } else {
        return (data[left] < data[right]);
    }
}

void exchange( float *data, int* segID, int left, int right )
{
    std::swap( data[left], data[right] );
    std::swap( segID[left], segID[right] );
}

void bitonicSort_Ascend_LengthIsPowerOfTwoOnly( float *data, int* segID, int len )
{
    int i, j, k;
    // k selects the bit position that determines whether the pairs of 
    // elements are to be exchanged into ascending or descending order.
    // length of sort interval get doubled every iteration
    // (because sort recursion is post-ordered).
    for (k = 2; k <= len; k <<= 1) {
        // j corresponds to the distance apart the elements are that 
        // are to be compared and conditionally exchanged.
        // length of merge interval get halved every iteration
        // (because merge recursion is pre-ordered).
        for (j = k >> 1; j > 0; j >>= 1) {
            for (i = 0; i < len; ++i) {
                int ixj = i ^ j;
                if (i < ixj) {
                    if ((i & k) != 0) {
                        if (compare( data, segID, i, ixj )) {
                            exchange( data, segID, i, ixj );
                        }
                    } else {    // ((i & k) == 0)
                        if (!compare( data, segID, i, ixj )) {
                            exchange( data, segID, i, ixj );
                        }
                    }
                }
            }
        }
    }
}

void segmentedBitonicSort( float* data, int* seg_id, int* seg_start, int len, int seg_num )
{
    //BitonicSorter sorter( data, seg_id, len );
    //sorter.sort();

    for (int i = 0; i < seg_num; ++i) {
        BitonicSorter( data + seg_start[i], seg_id + seg_start[i], seg_start[i + 1] - seg_start[i] ).sort();
    }

    //int partLen = GreatestPowerOf2LessThan( len );
    //bitonicSort_Ascend_LengthIsPowerOfTwoOnly( data, seg_id, partLen );

    //int offset = len - partLen;
    //bitonicSort_Ascend_LengthIsPowerOfTwoOnly( data + offset, seg_id + offset, partLen );

    //int midSegStart, midSegEnd;
    //for (int i = 0; i < seg_num; ++i) {
    //    if (seg_start[i] < partLen) {
    //        midSegStart = seg_start[i - 1];
    //        midSegEnd = seg_start[i];
    //        break;
    //    }
    //}

    //if ((midSegStart < partLen) || (midSegEnd >( len - partLen ))) {
    //    return;
    //}

}