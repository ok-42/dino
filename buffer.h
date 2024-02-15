#include <stdlib.h>

/// @brief Stores values received via IR
class Buffer {
public:
    Buffer() {
        buffer = (int*)calloc(5, sizeof(int));
        volatile int bufferIndex = 0;
    };

    void add(int);
    int resolve(void);


private:
    int* buffer;
    int index;
};
