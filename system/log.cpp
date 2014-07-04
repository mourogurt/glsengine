#include "log.h"

Log::Log()
{
	log.set_priority(true);
	log.set_max_size(20);
}

std::vector<std::string> Log::getLog()
{
	std::vector<std::string> outlog;
	while (log.size() > 0)
	{
		Buffer* buf = log.pop();
        std::string str (buf->data.get(),buf->data.get()+buf->datasize);
		outlog.push_back(str);
        buf->data.reset(nullptr);
		delete buf;
	}
	return outlog;
}

void Log::writeLog(std::string str)
{
	Buffer* buf = new Buffer;
    buf->data = std::unique_ptr<char[]>(new char[str.size()+1]);
    memcpy (buf->data.get(),str.c_str(),str.size());
    buf->data.get()[str.size()] = '\0';
    buf->datasize = str.size();
	log.push(buf);
}

void Log::set_max_log(size_t maxsize)
{
	log.set_max_size(maxsize);
}

Log::~Log()
{
	log.clean();
}
