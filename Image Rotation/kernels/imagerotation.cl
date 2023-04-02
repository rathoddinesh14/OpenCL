__constant sampler_t sampler =  CLK_NORMALIZED_COORDS_FALSE |
                                CLK_ADDRESS_CLAMP |
                                CLK_FILTER_LINEAR;

__kernel void rotation( __read_only image2d_t inputImg, 
                        __write_only image2d_t outputImg,
                        int imgWidth, int imgHeight, float angle) {

    int x = get_global_id(0);
    int y = get_global_id(1);

    // // printf("x: %d, y: %d\n", x, y);

    // // image center
    // float cx = width / 2.0f;
    // float cy = height / 2.0f;

    // // relative coordinates of work item
    // int rx = x - cx;
    // int ry = y - cy;

    // // compute trigonometric functions
    // float cos_theta = cos(angle);
    // float sin_theta = sin(angle);

    // // input coordinates
    // float ix = cx + cos_theta * rx - sin_theta * ry;
    // float iy = cy + sin_theta * rx + cos_theta * ry;

    //  read input pixel from image with cl_unsigned_int32
    float pixel = read_imagef(inputImg, sampler, (int2)(x, y)).x;

    // print pixel content
    // printf("pixel: %f\n", pixel);

    // write output pixel
    write_imagef(outputImg, (int2)(x, y), (float4)(pixel, 0.0f, 0.0f, 0.0f));
}