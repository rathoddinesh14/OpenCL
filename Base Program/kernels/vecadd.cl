__kernel void vecadd(__global int *a, __global int *b, __global int *c) {
    // Get work-item id (0, 1, 2, ...)
    int i = get_global_id(0);
    // printf("Hello from work-item %d\n", i);
    c[i] = a[i] + b[i];
}