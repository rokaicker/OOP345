/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: January 30, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef TIMEDTASK_H
#define TIMEDTASK_H
#include <chrono>
#include <string>
#include <iostream>

namespace sdds {
	constexpr int MAXRECORDS = 10;

	// struct "Task" to hold basic information about a Task
	struct Task {										
		std::string m_Name{};								// Name of the Task
		std::string m_TimeUnits{};							// Units of time used with the Task
		std::chrono::duration<long long, std::nano> m_duration;			// Duration of the Task
	};

	class TimedTask {
		int m_recordCount{};									// Keeps track of number of records stored in Task array
		std::chrono::steady_clock::time_point m_startTime;	// Start time of current task (set when the clock starts)
		std::chrono::steady_clock::time_point m_endTime;	// End time of the current task (set when the clock stops)
		Task m_recordedTasks[MAXRECORDS]{};							// Array to hold incoming Tasks

	public:
		TimedTask();										// Default Constructor
		void startClock();									// Starts timer for event
		void stopClock();									// Stops timer for event
		void addTask(const char* name);						// Adds tasks to m_recordedTasks array
		//~TimedTask();										// Destructor

		int getRecordCount()const;							// Returns value of m_recordCount

		std::string getTaskName(int index)const;			// Returns task name

		std::string getTimeUnits(int index)const;			// Returns units of time

		long long getDuration(int index)const;	// Returns duration of index. 
		

		friend std::ostream& operator<<(std::ostream& os, const TimedTask& task);
	};

	std::ostream& operator<<(std::ostream& os, const TimedTask& task);		// Friend insertion operator to insert TimedTask objects into the ostream in a specific format.

}

#endif
