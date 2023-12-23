//
// Created by Андрей on 23/12/2023.
//

#ifndef LAB_01_AA_PROG_SRC_ATOMIC_QUEUE_H_
#define LAB_01_AA_PROG_SRC_ATOMIC_QUEUE_H_

#include <mutex>
#include <queue>

class atomic_queue
{
 public:
	void push( const int& value )
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queque.push(value);
	}

	void pop()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queque.pop();
	}
	//int operator[]( int i ){ return m_queque[i] };
 public:
	std::queue<int> m_queque;
	mutable std::mutex m_mutex;
};

#endif //LAB_01_AA_PROG_SRC_ATOMIC_QUEUE_H_
