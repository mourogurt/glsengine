#include "concurent_queue.h"

ConcurentQueue::ConcurentQueue()
{
    first = nullptr;
    back = nullptr;
	queue_size = 0;
	max_size = 50;
	critical_queue = 0;
}

ConcurentQueue::ConcurentQueue(bool crit)
{
    first = nullptr;
    back = nullptr;
	queue_size = 0;
	max_size = 50;
	critical_queue = crit;
}

void ConcurentQueue::push(Buffer* bufin)
{
	std::unique_lock<std::mutex> mlock(lock_mutex);
	if (queue_size == max_size)
	{
		if ((!critical_queue) && (max_size!=0))
            wait_cond.wait(mlock,[&](){return queue_size < max_size;});
		if ((critical_queue) && (max_size!=0))
		{
			Buffer* retbuf = pop();
			mlock.lock();
            retbuf->data.reset(nullptr);
            delete retbuf;
		}
	}
    if (first == nullptr)
	{
        first = new List;
        back = first;
        back->next = nullptr;
        back->buffer.reset(bufin);
	} else
	{
        back->next = new List;
        back->next->buffer.reset(bufin);
        back->next->next = nullptr;
        back = back->next;
	}
	queue_size++;
	wait_cond.notify_one();
	mlock.unlock();
}

Buffer* ConcurentQueue::pop()
{
	std::unique_lock<std::mutex> mlock(lock_mutex);
    Buffer* retbuf = nullptr;
	if (queue_size == 0)
	{
		if ((!critical_queue) && (max_size!=0))
			wait_cond.wait(mlock,[&](){return queue_size > 0;});
		if ((critical_queue) && (max_size!=0))
		{
			Buffer* retbuf = new Buffer;
            retbuf->data = std::unique_ptr<char[]>(new char[1]);
            retbuf->data.get()[0] = '\0';
            retbuf->datasize = 1;
			mlock.unlock();
			push(retbuf);
			mlock.lock();
		}
	}
    retbuf = first->buffer.release();
    List* nextelem = first->next;
    delete first;
    first = nextelem;
    if (first == nullptr)
        back = nullptr;
	queue_size--;
	wait_cond.notify_one();
	mlock.unlock();
	return retbuf;
}

size_t ConcurentQueue::size()
{
	return queue_size;
}

void ConcurentQueue::set_max_size(size_t maxin)
{
	max_size = maxin;
}

void ConcurentQueue::set_priority(bool prior)
{
	critical_queue = prior;
}

void ConcurentQueue::clean()
{
    while (first != nullptr)
	{
		Buffer* retbuf = pop();
        retbuf->data.reset(nullptr);
        delete retbuf;
		
	}
}

ConcurentQueue::~ConcurentQueue()
{
	clean();
}
