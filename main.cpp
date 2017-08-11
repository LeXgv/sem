//Задача: Сделать группу из 16 семафоров сис5 и 
//значение каждого семафора 
//это его порядковый номер
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>
union semun
{
int val;
struct semid_ds *buf;
unsigned short *array;
} arg;

int main()
{
	//получение ключа объекта sys5
	key_t SemKey = ftok("sem", 2);
	if(-1 == SemKey)
	{
		std::cout << "Ошибка создания объекта sys5\n";
		return -1;
	}
	//создание семафора
	int semid = semget(SemKey, 16, IPC_CREAT | IPC_EXCL | 0777);
	if(-1 == semid)
	{
		if(EEXIST != errno)
		{
			std::cout << "Ошибка создания семафора\n";
			return -2;
		}
		else
		{
			std::cout << "такой семафор существует. Удалите его...\n";
			return -3;
		}
	}
	std::cout << "semid = " << semid << std::endl;
	union semun arg;
	//ИНИЦИАЛИЗАЦИЯ СЕМАФОРА ПО ЗАДАНИЮ
	for(int i = 0; i < 16; i++)
	{
		arg.val = i;
		int r = semctl(semid, i, SETVAL, arg);
		std::cout << i << " : " << r << std::endl;
		if(-1 == r)
		{
			std::cout << "На итерации " << i << " ошибка записи значения в семафор\n";
			return -4;
		}
	}
	
	return 0;
	
}
