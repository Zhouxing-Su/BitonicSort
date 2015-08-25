#include <iostream>
#include <chrono>

#include "BitonicSort.h"


using namespace std;


void print( float* data, int* segID, int len )
{
    for (int i = 0; i < len; i++) {
        cout << data[i] << ' ';
    }
    cout << endl;
}

void printInstance( float* data, int* segID, int* segStart, int len, int segNum )
{
}

int main()
{
    const int n = 8192;
    const int m = 8192;

    const int repeat = 128;

    float oldData[n];
    int oldSegID[n];

    float data[n];
    int segID[n];
    int segStart[m + 1];

    chrono::high_resolution_clock::time_point start, end;

    // correctness test
    for (int len = 1; len <= 40; ++len) {
        for (int segNum = 1; segNum <= len; ++segNum) {
            for (int k = 0; k < 16; ++k) {
                generateInstance( data, segID, segStart, len, segNum );

                copy( data, data + len, oldData );
                copy( segID, segID + len, oldSegID );

                segmentedBitonicSort( data, segID, segStart, len, segNum );

                int errorCode = check( data, segID, oldData, oldSegID, len );
                if (errorCode != 0) {
                    cout << ErrorMsg[errorCode] << endl;
                    print( oldData, oldSegID, len );
                    print( data, segID, len );
                }
            }
        }
    }

    // performance test
    cout << "len,segNum,time(ms),(repeat " << repeat << " times)" << endl;
    for (int i = 1; i <= 43; ++i) {
        int len = i * 187;
        for (int j = 1; j <= 19; ++j) {
            int segNum = len * j / 19;
            if (segNum <= 0) { segNum = 1; }
            chrono::high_resolution_clock::duration time;
            for (int k = 0; k < repeat; ++k) {
                generateInstance( data, segID, segStart, len, segNum );

                start = chrono::high_resolution_clock::now();
                segmentedBitonicSort( data, segID, segStart, len, segNum );
                end = chrono::high_resolution_clock::now();
                time += (end - start);
            }

            cout << len << "," << segNum << ","
                << chrono::duration_cast<chrono::milliseconds>(time).count() << endl;
        }
    }

    return 0;
}

