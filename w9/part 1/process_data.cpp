// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant


#include "process_data.h"

namespace sdds_ws9 {

	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2. 
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
			avg += arr[i];
		avg /= divisor;
	}
	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2. 
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
			var += (arr[i]-avg)*(arr[i]-avg);
		var /= divisor;
	}
	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples. 
	//   
	ProcessData::ProcessData(std::string filename) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.		

		std::ifstream file(filename, std::ios::in|std::ios::binary);
		// First reading initial 4 bytes of file (to get total number of items)
		file.read(reinterpret_cast<char*>(&total_items), 4);
		
		// Initializing dynamic array with size = total_items
		data = new int [total_items];
		size_t i = 0;
		while (file){
			file.read(reinterpret_cast<char*>(&data[i]), 4);
			i++;
		}

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";
	}
	
	ProcessData::~ProcessData() {
		delete[] data;
	}
	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}


	// TODO You create implementation of function operator(). See workshop instructions for details . 
	int ProcessData::operator()(std::string filename, double& avgVal, double& varVal){
		computeAvgFactor(data, total_items, total_items, avgVal);
		computeVarFactor(data, total_items, total_items, avgVal, varVal);
		std::ofstream file(filename, std::ios::out|std::ios::binary);
		file.write(reinterpret_cast<char*>(&total_items), 4);
		for (int i = 0; i < total_items; i++){
			file.write(reinterpret_cast<char*>(&data[i]), 4);
		}
		return 0;
	}





}