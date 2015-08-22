#include <iostream>
#include <vector>


// see [ http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 ]
// example [
//  cout << GreatestPowerOf2LessThan( 3 ) << GreatestPowerOf2LessThan( 4 ) << GreatestPowerOf2LessThan( 5 ) << endl;
// ] output [ 448 ]
int GreatestPowerOf2LessThan( int n )
{
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return (n + 1) >> 1;
}


// type of items in List must be Item.
// there must be operator[] in List.
template <typename Item, typename List>
class BitonicSorter
{
public:
    BitonicSorter( List &list, int len ) : list( list ), listLen( len ) {}

    void print() const
    {
        for (int i = 0; i < listLen; ++i) {
            std::cout << list[i] << ',';
        }
        std::cout << std::endl;
    }

    // if (ascend == true), the list will be sorted in ascending order
    void sort( bool ascend = true )
    {
        bitonicSort( ascend, 0, listLen );
    }

    void sort_NonRecursive( bool ascend = true )
    {
        int i, j, k;
        for (k = 2; k <= listLen; k = 2 * k) {
            for (j = k >> 1; j > 0; j = j >> 1) {
                for (i = 0; i < listLen; ++i) {
                    int ixj = i^j;
                    if ((ixj) > i) {
                        if ((((i&k) == 0) == ascend) && (list[i] > list[ixj])) {
                            std::swap( list[i], list[ixj] );
                        }
                        if ((((i&k) != 0) == ascend) && (list[i] < list[ixj])) {
                            std::swap( list[i], list[ixj] );
                        }
                    }
                }
            }
        }
    }

private:
    void bitonicSort( bool ascend, int offset, int len )
    {
        if (len <= 1) { return; }

        int halfLen = len / 2;
        bitonicSort( !ascend, offset, halfLen );
        bitonicSort( ascend, offset + halfLen, len - halfLen );

        bitonicMerge( ascend, offset, len );
    }

    void bitonicMerge( bool ascend, int offset, int len )
    {
        if (len <= 1) { return; }

        int halfLen = GreatestPowerOf2LessThan( len );
        int left = offset;
        int right = offset + halfLen;
        for (int i = halfLen; i < len; ++i, ++left, ++right) {
            if ((list[left] > list[right]) == ascend) { std::swap( list[left], list[right] ); }
        }
        bitonicMerge( ascend, offset, halfLen );
        bitonicMerge( ascend, offset + halfLen, len - halfLen );
    }

    List &list;
    int listLen;
};