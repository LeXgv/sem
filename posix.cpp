#include <iostream>
#include <semaphore.h>
#include <fcntl.h>

int main()
{
	//создание посикс семафора
	sem_unlink("/test.sem");
	sem_t *semp = sem_open("/test.sem", O_CREAT | O_EXCL, 0777, 66);
	if(SEM_FAILED == semp)
	{
		if(errno == EEXIST)
		{
			std::cout << "семафор существует...\n";
			return -1;
		}
		else
		{
			std::cout << "Ошибка создания семафора\n";
			return -2;
		}
	}
	std::cout << "Семафор успешно создан\n";



return 0;
}
