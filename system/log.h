#ifndef _IF_LOG_H
#define _IF_LOG_H
#include <mutex>
#include "concurent_queue.h"
#include <vector>
#include <cstring>

class Log  //Класс лога
{
public:
	Log();
    std::vector<std::string> getLog (); //Возвращаем лог
    void writeLog (std::string); //Записываем в лог
	void set_max_log(size_t); //Назначаем максимальный размер лога
	~Log();
private:
    ConcurentQueue log;
};

#endif
