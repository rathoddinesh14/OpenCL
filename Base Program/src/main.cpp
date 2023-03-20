#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include "machine.h"
#include <iostream>
#include <vector>

using namespace std;



int main() {

    const int num_elements = 1024;

    // datasize
    size_t datasize = sizeof(int) * num_elements;

    cout << "datasize: " << datasize << endl;

    // host data
    int *h_a = new int[num_elements];
    int *h_b = new int[num_elements];
    int *h_c = new int[num_elements];

    // init host data
    for (int i = 0; i < num_elements; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    Machine machine;
    machine.print_platform_and_device_info();
    machine.print_context_info();
    machine.create_single_context();
    machine.print_context_info();



    return 0;
}