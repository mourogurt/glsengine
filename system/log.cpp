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
		std::string str (buf->buff,buf->buff+buf->buffsize);
		outlog.push_back(str);
		delete [] buf->buff;
		delete buf;
	}
	return outlog;
}

void Log::writeLog(std::string str)
{
	Buffer* buf = new Buffer;
	buf->buff = new char[str.size()];
	memcpy (buf->buff,str.c_str(),str.size());
	buf->buffsize = str.size();
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
