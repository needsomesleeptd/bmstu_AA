//
// Created by Андрей on 06/12/2023.
//

#ifndef LAB_01_AA_PROG_SRC_SEMAPHORE_H_
#define LAB_01_AA_PROG_SRC_SEMAPHORE_H_


#include <mutex>
#include <condition_variable>

class Semaphore {
 public:
	Semaphore (int count_ = 0)
		: count(count_) {}

	inline void notify()
	{
		std::unique_lock<std::mutex> lock(mtx);
		count++;
		cv.notify_one();
	}

	inline void wait()
	{
		std::unique_lock<std::mutex> lock(mtx);

		while(count == 0){
			cv.wait(lock);
		}
		count--;
	}

 private:
	std::mutex mtx;
	std::condition_variable cv;
	int count;
};
#endif //LAB_01_AA_PROG_SRC_SEMAPHORE_H_
