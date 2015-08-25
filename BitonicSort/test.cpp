#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <set>


using namespace std;


extern const vector<string> ErrorMsg = {
    "CheckPass",
    "SegmentMismatch",
    "MissingItem",
    "WrongOrder"
};


void generateInstance( float* data, int* segID, int* segStart, int len, int segNum )
{
    random_device rd;
    mt19937 randEngine( 0 );

    uniform_real_distribution<float> valueDist( 0, 1 );
    for (int i = 0; i < len; ++i) {
        data[i] = valueDist( randEngine );
    }

    set<int> start;
    if (len > 1) {
        uniform_int_distribution<int> segStartDist( 1, len - 1 );
        while (start.size() < (segNum - 1)) {
            start.insert( segStartDist( randEngine ) );
        }
    }
    segStart[0] = 0;
    int i = 1;
    for (auto iter = start.begin(); iter != start.end(); ++iter, ++i) {
        segStart[i] = *iter;
    }
    segStart[segNum] = len;

    //sort( segStart, segStart + segNum );

    for (int i = 0, seg = 1; i < len; ++i) {
        if (i < segStart[seg]) {
            segID[i] = seg - 1;
        } else {
            segID[i] = seg;
            ++seg;
        }
    }
}

int check( float* data, int* segID, float* oldData, int* oldSegID, int len )
{
    // make sure segments distribution is the same
    for (int i = 0; i < len; ++i) {
        if (segID[i] != oldSegID[i]) {
            return 1;
        }
    }

    vector<float> v;
    int currentSeg = 0;
    for (int i = 0, j; i < len; i = j, ++currentSeg) {
        for (j = i; (j < len) && (oldSegID[j] == currentSeg); ++j) {
            v.push_back( oldData[j] );
        }
        for (j = i; (j < len) && (segID[j] == currentSeg); ++j) {
            // make sure all items in each segments are there
            auto iter = find( v.begin(), v.end(), data[j] );
            if (iter == v.end()) { return 2; }
            v.erase( iter );
            // make sure data has been sorted
            if ((j > 0) && (segID[j - 1] == segID[j])) {
                if (data[j - 1] > data[j]) { return 3; }
            }
        }
    }

    return 0;
}