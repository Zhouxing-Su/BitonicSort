#include <stdlib.h>
#include <float.h>
#include <string.h>


//#define NON_RECURSIVE
//#define NON_RECURSIVE_IN_PLACE_SORT


#ifdef __cplusplus
extern "C" {
#endif
    void segmentedBitonicSort( float* data, int* seg_id, int* seg_start, int len, int seg_num );
#ifdef __cplusplus
}
#endif
