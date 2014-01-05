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
			wait_cond.wait(mlock,[&](){return queue_size <= max_size;});
		if ((critical_queue) && (max_size!=0))
		{
			mlock.unlock();
			Buffer* retbuf = pop();
			mlock.lock();
			if (retbuf != NULL)
			{
				if (retbuf->buff != NULL)
					delete [] retbuf->buff;
				delete retbuf;
			}
		}
	}
	if (first==NULL)
	{
		first = new Spisok;
		first->buf = bufin;
		back = first;
	} else if (first == back)
	{
		Spisok* sp = new Spisok;
		sp->buf = bufin;
		back = sp;
		first -> next = back;
	} else
	{
		Spisok* sp = new Spisok;
		sp->buf = bufin;
		back->next = sp;
		back = sp;
	}
	queue_size++;
	wait_cond.notify_one();
	mlock.unlock();
}

Buffer* ConcurentQueue::pop()
{
	std::unique_lock<std::mutex> mlock(lock_mutex);
	Buffer* retbuf;
	if (queue_size == 0)
	{
		if ((!critical_queue) && (max_size!=0))
			wait_cond.wait(mlock,[&](){return queue_size > 0;});
		if ((critical_queue) && (max_size!=0))
		{
			Buffer* retbuf = new Buffer;
			retbuf->buff = new char;
			retbuf->buff[0] = '\0';
			retbuf->buffsize = 1;
			mlock.unlock();
			push(retbuf);
			mlock.lock();
		}
	}
	if (first==back)
	{
		retbuf = first->buf;
		delete first;
		first = nullptr;
	} else
	{
		Spisok* dlspsk;
		retbuf = first->buf;
		dlspsk = first;
		first = first -> next;
		delete dlspsk;
	}
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
		if (retbuf != NULL)
		{
			if (retbuf->buff != NULL)
				delete [] retbuf->buff;
			delete retbuf;
		}
		
	}
}

ConcurentQueue::~ConcurentQueue()
{
	clean();
}