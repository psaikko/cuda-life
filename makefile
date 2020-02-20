life: life.cpp
	$(CXX) --std=c++14 -O3 -pedantic -Wall life.cpp -o life

cuda-life: cuda-life.cu
	nvcc --std=c++14 -O3 --compiler-options -Wall cuda-life.cu -o cuda-life