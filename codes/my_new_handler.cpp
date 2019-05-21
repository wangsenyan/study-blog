#include <iostream>
//#inlucde <new>
/// buffer to be allocated after custom new handler has been installed
char* g_pSafetyBuffer = NULL;

/// exceptional one time release of a global reserve
void my_new_handler()
{
    if (g_pSafetyBuffer) {
        delete [] g_pSafetyBuffer;
        g_pSafetyBuffer = NULL;
        std::cout << "[Free some pre-allocated memory]";
        return;
    }
    std::cout << "[No memory to free, throw bad_alloc]";
    throw std::bad_alloc();
}

/// illustrates how a custom new handler may work
int main()
{
    enum { MEM_CHUNK_SIZE = 1000*1000 }; // adjust according to your system
    std::set_new_handler(my_new_handler);
    g_pSafetyBuffer = new char[801*MEM_CHUNK_SIZE];
    try {
        while (true) {
            std::cout << "Trying another new... ";
            new char[200*MEM_CHUNK_SIZE];
            std::cout << " ...succeeded.\n";
        }
    } catch (const std::bad_alloc& e) {
        std::cout << " ...failed.\n";
    }
    return 0;
}
