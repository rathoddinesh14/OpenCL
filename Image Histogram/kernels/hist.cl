#define HIST_BINS 256

__kernel void histogram(__global int *input, int numData, __global int *output) {
    
    int gid = get_global_id(0);
    int lid = get_local_id(0);

    // local histogram
    __local int hist[HIST_BINS];

    // initialize local histogram
    for (int i = lid; i < HIST_BINS; i += get_local_size(0)) {
        hist[i] = 0;
    }

    // wait for all work items within the work group to finish
    barrier(CLK_LOCAL_MEM_FENCE);

    // compute local histogram
    for (int i = gid; i < numData; i += get_global_size(0)) {
        atomic_add(&hist[input[i]], 1);
    }

    // wait for all work items within the work group to finish
    barrier(CLK_LOCAL_MEM_FENCE);

    // write local histogram to global memory
    for (int i = lid; i < HIST_BINS; i += get_local_size(0)) {
        atomic_add(&output[i], hist[i]);
    }
}