#include <string>
#include <vector>


extern const std::vector<std::string> ErrorMsg;


// see [ http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 ]
// example [
//  cout << LeastPowerOf2NotLessThan( 3 ) << LeastPowerOf2NotLessThan( 4 ) << LeastPowerOf2NotLessThan( 5 ) << endl;
// ] output [ 448 ]
int LeastPowerOf2NotLessThan( int n );
int GreatestPowerOf2LessThan( int n );

void segmentedBitonicSort( float* data, int* seg_id, int* seg_start, int len, int seg_num );

void generateInstance( float* data, int* segID, int* segStart, int len, int segNum );
int check( float* data, int* segID, float* oldData, int* oldSegID, int len );


class BitonicSorter
{
public:
    BitonicSorter( float *data, int* segID, int len )
        : data( data ), segID( segID ), listLen( len )
    {
    }

    // if (ascend == true), the data will be sorted in ascending order
    void sort( bool ascend = true )
    {
        bitonicSort( ascend, 0, listLen );
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
            if (compare( left, right ) == ascend) { exchange( left, right ); }
        }
        bitonicMerge( ascend, offset, halfLen );
        bitonicMerge( ascend, offset + halfLen, len - halfLen );
    }

    // if left > right, return true.
    bool compare( int left, int right ) const
    {
        if (segID[left] != segID[right]) {
            return (segID[left] > segID[right]);
        } else {
            return (data[left] > data[right]);
        }
    }

    void exchange( int left, int right ) const
    {
        std::swap( data[left], data[right] );
        std::swap( segID[left], segID[right] );
    }

    float *data;
    int *segID;
    int listLen;
};