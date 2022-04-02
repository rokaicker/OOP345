// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant

#include "process_data.h"


namespace sdds_ws9 {

	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}
	ProcessData::operator bool() const {
		return total_items > 0 && data && num_threads>0 && averages && variances && p_indices;
	}

	ProcessData::ProcessData(std::string filename, int n_threads) {  
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

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.
	int ProcessData::operator()(std::string filename, double& avgVal, double& varVal){
		
		std::vector<std::thread> compAvgFacThreads;
		auto bindCompAvgFac = std::bind(computeAvgFactor,std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3);
		for (int i = 0; i < num_threads; i++){
			int index = p_indices[i];
			int sz = p_indices[i+1] - index;
			compAvgFacThreads.push_back(std::thread(bindCompAvgFac, data[index], sz, std::ref(averages[i])));
		}
		for (auto& thread : compAvgFacThreads){
			thread.join();
		}
		double totalAvg;
		for (int i = 0; i < num_threads; i++){
			totalAvg += averages[i];
		}
		avgVal = totalAvg;

		std::vector<std::thread> compVarFacThreads;
		auto bindCompVarFac = std::bind(computeVarFactor, std::placeholders::_1, std::placeholders::_2, total_items, avgVal, std::placeholders::_3 );
		for (int i = 0; i < num_threads; i++){
			int index = p_indices[i];
			int sz = p_indices[i+1] - index;
			compVarFacThreads.push_back(std::thread(bindCompVarFac, data[index], sz, std::ref(variances[i])));
		}
		for (auto& thread : compVarFacThreads){
			thread.join();
		}
		double totalVar;
		for (int i = 0; i < num_threads; i++){
			totalVar += variances[i];
		}
		varVal = totalVar;

		std::ofstream file(filename, std::ios::out|std::ios::binary);
		file.write(reinterpret_cast<char*>(&total_items), 4);
		for (int i = 0; i < total_items; i++){
			file.write(reinterpret_cast<char*>(&data[i]), 4);
		}
		return 0;
	}
}