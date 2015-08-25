#include <string>
#include <vector>


extern const std::vector<std::string> ErrorMsg;


void generateInstance( float* data, int* segID, int* segStart, int len, int segNum );
int check( float* data, int* segID, float* oldData, int* oldSegID, int len );
