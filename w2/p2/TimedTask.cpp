/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: January 30, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "TimedTask.h"

namespace sdds {
	TimedTask::TimedTask() {
		m_recordCount = 0;
	}

	void TimedTask::startClock() {
		m_startTime = std::chrono::steady_clock::now();
	}

	void TimedTask::stopClock() {
		m_endTime = std::chrono::steady_clock::now();
	}

	void TimedTask::addTask(const char* name) {
		m_recordedTasks[m_recordCount].m_Name.assign(name);
		m_recordedTasks[m_recordCount].m_TimeUnits.assign("nanoseconds");
		m_recordedTasks[m_recordCount].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime-m_startTime);
		++m_recordCount;
	}
	
	int TimedTask::getRecordCount()const {
		return m_recordCount;
	}

	std::string TimedTask::getTaskName(int index)const {
		return m_recordedTasks[index].m_Name;
	}

	std::string TimedTask::getTimeUnits(int index)const {
		return m_recordedTasks[index].m_TimeUnits;
	}

	long long TimedTask::getDuration(int index)const {
		return m_recordedTasks[index].m_duration.count();
	}
	
	std::ostream& operator<<(std::ostream& os,  const TimedTask& task) {

		int taskRecCount = task.getRecordCount();
		os << "--------------------------" << std::endl << "Execution Times:" << std::endl << "--------------------------" << std::endl;
		for (int i = 0; i < taskRecCount; i++) {
			//os << "  ";
			os.width(21);
			os.setf(std::ios::left);
			os << task.getTaskName(i);
			os.width(13);
			os.unsetf(std::ios::left);
			os << task.getDuration(i) << " " << task.getTimeUnits(i) << std::endl;
		}
		os << "--------------------------" << std::endl;
		return os;
	}

}
