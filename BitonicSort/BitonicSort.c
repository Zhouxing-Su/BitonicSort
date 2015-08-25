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


#ifdef NON_RECURSIVE
#ifdef NON_RECURSIVE_IN_PLACE_SORT
void bitonicSort_Ascend_LengthIsPowerOfTwoOnly( float *data, int len, float *padBuf, int padLen )
{
    int i, j, k;
    float tmp;
    float *left;
    float *right;

    // k selects the bit position that determines whether the pairs of 
    // elements are to be exchanged into ascending or descending order.
    // length of sort interval get doubled every iteration
    // (because sort recursion is post-ordered).
    for (k = 2; k <= padLen; k <<= 1) {
        // j corresponds to the distance apart the elements are that 
        // are to be compared and conditionally exchanged.
        // length of merge interval get halved every iteration
        // (because merge recursion is pre-ordered).
        for (j = k >> 1; j > 0; j >>= 1) {
            for (i = 0; i < padLen; ++i) {
                int ixj = i ^ j;
                if (i < ixj) {
                    left = ((i < len) ? (data + i) : (padBuf + i - len));
                    right = ((ixj < len) ? (data + ixj) : (padBuf + ixj - len));
                    if ((i & k) != 0) {
                        if (*left < *right) {
                            tmp = *left;
                            *left = *right;
                            *right = tmp;
                        }
                    } else {    // ((i & k) == 0)
                        if (*left > *right) {
                            tmp = *left;
                            *left = *right;
                            *right = tmp;
                        }
                    }
                }
            }
        }
    }
}

// if (ascend == true), the data will be sorted in ascending order
void bitonicSort( float *data, int len, int ascend )
{
    static float *padBuf = NULL;
    static int padBufLen = 0;
    int padLen = LeastPowerOf2NotLessThan( len );

    int requiredPadLen = padLen - len;
    if (padBufLen < requiredPadLen) {
        padBuf = (float*)realloc( padBuf, requiredPadLen * sizeof( float ) );
        for (padBufLen = 0; padBufLen < requiredPadLen; ++padBufLen) {
            padBuf[padBufLen] = FLT_MAX;
        }
    }

    bitonicSort_Ascend_LengthIsPowerOfTwoOnly( data, len, padBuf, padLen );
}
#else
void bitonicSort_Ascend_LengthIsPowerOfTwoOnly( float *data, int len )
{
    int i, j, k;
    float tmp;

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
                        if (data[i] < data[ixj]) {
                            tmp = data[i];
                            data[i] = data[ixj];
                            data[ixj] = tmp;
                        }
                    } else {    // ((i & k) == 0)
                        if (data[i] > data[ixj]) {
                            tmp = data[i];
                            data[i] = data[ixj];
                            data[ixj] = tmp;
                        }
                    }
                }
            }
        }
    }
}

// if (ascend == true), the data will be sorted in ascending order
void bitonicSort( float *data, int len, int ascend )
{
    int padLen = LeastPowerOf2NotLessThan( len );
    int i;
    float *padBuf;

    if (padLen == len) {
        bitonicSort_Ascend_LengthIsPowerOfTwoOnly( data, len );
    } else {
        padBuf = (float*)malloc( padLen * sizeof( float ) );
        memcpy( padBuf, data, len * sizeof( float ) );
        for (i = len; i < padLen; ++i) {
            padBuf[i] = FLT_MAX;
        }
        bitonicSort_Ascend_LengthIsPowerOfTwoOnly( padBuf, padLen );
        memcpy( data, padBuf, len * sizeof( float ) );
        free( padBuf );
    }
}
#endif // IN_PLACE_SORT
#else
void bitonicMerge( float *data, int len, int ascend )
{
    int halfLen = GreatestPowerOf2LessThan( len );
    int left = 0;
    int right = halfLen;
    int i;
    float tmp;

    if (len <= 1) { return; }

    for (i = halfLen; i < len; ++i, ++left, ++right) {
        if ((data[left] > data[right]) == ascend) {
            tmp = data[left];
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
    int halfLen = len / 2;

    if (len <= 1) { return; }

    bitonicSort( data, halfLen, !ascend );
    bitonicSort( data + halfLen, len - halfLen, ascend );

    bitonicMerge( data, len, ascend );
}
#endif // !NON_RECURSIVE


void segmentedBitonicSort( float* data, int* seg_id, int* seg_start, int len, int seg_num )
{
    int i;
    for (i = 0; i < seg_num; ++i) {
        bitonicSort( data + seg_start[i], seg_start[i + 1] - seg_start[i], !0 );
    }
}