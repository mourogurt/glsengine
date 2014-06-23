#ifndef _IF_CONCURENT_QUEUE
#define _IF_CONCURENT_QUEUE
#include <thread>
#include <mutex>
#include <condition_variable>

struct Buffer
{
   char* buff;
   unsigned int buffsize;
};

struct Spisok
{
	Buffer* buf;
	Spisok* next;
};

class ConcurentQueue
{
public:
	ConcurentQueue();
	ConcurentQueue(bool);
	void push (Buffer*);
	Buffer* pop();
	size_t size();
	void set_max_size(size_t);
	void set_priority(bool);
	void clean();
	~ConcurentQueue();
private:
	size_t queue_size;
	size_t max_size;
	bool critical_queue;
	Spisok* first;
	Spisok* back;
    std::mutex lock_mutex;
	std::condition_variable wait_cond;
};

#endif
