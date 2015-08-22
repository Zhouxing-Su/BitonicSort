#include <iostream>
#include <vector>
#include <string>


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

    // if (ascend == true), the list will be sorted in ascending order
    void sort( bool ascend = true )
    {
        bitonicSort( ascend, 0, listLen );
    }

    void sort_NonRecursive( bool ascend = true )
    {
        int i, j, k;
        for (k = 2; k <= listLen; k <<= 1) {
            for (j = k >> 1; j > 0; j >>= 1) {
                for (i = 0; i < listLen; ++i) {
                    int ixj = i ^ j;
                    if (ixj > i) {
                        if ((i & k) == 0) {
                            if (list[i] > list[ixj]) {
                                std::swap( list[i], list[ixj] );
                            }
                        } else {    // ((i & k) != 0)
                            if (list[i] < list[ixj]) {
                                std::swap( list[i], list[ixj] );
                            }
                        }
                    }
                }
            }
        }

        if (!ascend) {
            for (int l = listLen / 2 - 1, r = listLen / 2; l >= 0; --l, ++r) {
                std::swap( list[l], list[r] );
            }
        }
    }

    void print() const
    {
        for (int i = 0; i < listLen; ++i) {
            std::cout << list[i] << ',';
        }
        std::cout << std::endl;
    }

private:
    void bitonicSort( bool ascend, int offset, int len )
    {
        if (len <= 1) { return; }

        printOperation( "sort", ascend, offset, len );

        int halfLen = len / 2;
        bitonicSort( !ascend, offset, halfLen );
        bitonicSort( ascend, offset + halfLen, len - halfLen );

        bitonicMerge( ascend, offset, len );
    }

    void bitonicMerge( bool ascend, int offset, int len )
    {
        if (len <= 1) { return; }

        printOperation( "merge", ascend, offset, len );

        int halfLen = GreatestPowerOf2LessThan( len );
        int left = offset;
        int right = offset + halfLen;
        for (int i = halfLen; i < len; ++i, ++left, ++right) {
            if ((list[left] > list[right]) == ascend) { std::swap( list[left], list[right] ); }
        }
        bitonicMerge( ascend, offset, halfLen );
        bitonicMerge( ascend, offset + halfLen, len - halfLen );
    }

    static void printOperation( std::string operation, bool ascend, int offset, int len )
    {
        std::cout << operation << " " << (ascend ? "up" : "down") << "[" << offset << ", " << offset + len << ")" << std::endl;
    }

    List &list;
    int listLen;
};