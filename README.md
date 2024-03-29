# OpenCL Sample Programs

## Installation
	
	sudo apt-get install intel-opencl-icd	# for intel gpu
	for intel CPU, read about intel oneAPI

## Programs

### 1. [Vector Addition](Base%20Program)
	This is the base program for all other programs.

<!-- Image Histogram -->
### 2. [Image Histogram](Image%20Histogram)
	Program to calculate histogram of an image.
![Image Histogram](Image%20Histogram/assets/cat.bmp)

## References

1. https://streamhpc.com/blog/2013-04-28/opencl-error-codes/
2. https://stackoverflow.com/questions/18193320/cl-device-not-available-using-intel-core-2-duo-e8500-cpu
3. https://www.intel.com/content/dam/develop/external/us/en/documents/opencl_cpu_runtime-2022-1-release-notes-v1.0.pdf
4. https://www.intel.com/content/www/us/en/develop/documentation/installation-guide-for-intel-oneapi-toolkits-linux/top/installation/install-using-package-managers/apt.html#apt
5. https://www.intel.com/content/www/us/en/developer/tools/opencl-sdk/choose-download.html
6. https://github.com/google-coral/test_data/blob/104342d2d3480b3e66203073dac24f4e2dbb4c41/cat.bmp
	
installation location:

	/opt/intel/
	
To remove intel oneAPI:

	goto opencl folder and run force_remove.sh script
