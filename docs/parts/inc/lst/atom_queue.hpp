template<class T>
class AtomicQueue
{
 public:
	void push(const T& value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queque.push(value);
	}

	void pop()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queque.pop();
	}
	T front()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queque.front();
	}
	size_t size()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queque.size();
	}
 public:
	std::queue<T> m_queque;
	mutable std::mutex m_mutex;
};