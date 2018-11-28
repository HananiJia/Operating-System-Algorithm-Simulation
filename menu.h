#pragma once
#include"OS.h"

int menu_select()
{
	int i;
	do {
		system("cls");
		std::cout << "\t\t �q�����������������������������������������������r\n";
		std::cout << "\t\t��     Operating-System-Algorithm-Simulation     ��\n";
		std::cout << "\t\t�t�����������������������������������������������s\n";
		std::cout << "\t\t   ��������������������������������������������\n";
		std::cout << "\t\t   ��         1. First Come First Served     ��\n";
		std::cout << "\t\t   ��                                        ��\n";
		std::cout << "\t\t   ��         2. Short Job First             ��\n";
		std::cout << "\t\t   ��                                        ��\n";
		std::cout << "\t\t   ��         3. Round Robin                 ��\n";
		std::cout << "\t\t   ��                                        ��\n";
		std::cout << "\t\t   ��         0. Exit                        ��\n";
		std::cout << "\t\t   ��������������������������������������������\n";
		std::cout << "\t\tPlease choose(0-3):";
		std::cin >> i;
	} while (i < 0 || i>3);

	return i;
}

void OSAlgorithmSimulation()
{
	std::vector<pcb> pcbs;
	size_t roundtime;

	while (1)
	{
		pcbs.clear();
		switch (menu_select())
		{
		case 1:
			GetPcbs(pcbs);
			FCFS(pcbs);
			break;
		case 2:
			GetPcbs(pcbs);
			SJF(pcbs);
			break;
		case 3:
			GetPcbs(pcbs);
			GetRoundTime(roundtime);
			RR(pcbs, roundtime);
			break;
		case 0:
			std::cout << "\t\tsystem exit" << std::endl;
			system("pause");
			exit(0);
		}
	}
}

