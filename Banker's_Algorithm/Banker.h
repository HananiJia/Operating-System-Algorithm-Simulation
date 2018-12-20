#pragma
#include<iostream>
#include<stdlib.h>
#include<vector>

class Resources
{
public:
	std::vector<int> _Available;
	std::vector<std::vector<int>> _Allocation;
	std::vector< std::vector<int>> _Need;
	std::vector< std::vector<int>> _MaxNeed;
	std::vector<int> _Work;
	std::vector<bool> _Finish;
	std::vector<int> _Request;
	size_t _PcbNum;
	size_t _ResourcesNum;
};

void Init(Resources& R)
{
	system("cls");

	std::cout << "��������Դ����������";
	std::cin >> R._ResourcesNum;
	std::cout << "�����������������";
	std::cin >> R._PcbNum;

	R._Available.resize(R._ResourcesNum);	
	R._Allocation.resize(R._PcbNum);
	R._Need.resize(R._PcbNum);
	R._MaxNeed.resize(R._PcbNum);
	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		R._Allocation[i].resize(R._ResourcesNum);
		R._Need[i].resize(R._ResourcesNum);
		R._MaxNeed[i].resize(R._ResourcesNum);
	}
	R._Work.resize(R._ResourcesNum);
	R._Finish.resize(R._ResourcesNum);
	R._Request.resize(R._ResourcesNum);

	system("cls");
	for (size_t i = 0; i < R._ResourcesNum; ++i)
	{
		std::cout << "�������" << i + 1 << "����Դ��ϵͳʣ��������";
		std::cin >> R._Available[i];
	}

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		system("cls");
		std::cout << "�������" << i + 1 << "�������ѷ������Դ������" << std::endl;
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			std::cout << "�������ѷ���ĵ�" << j + 1 << "����Դ������";
			std::cin >> R._Allocation[i][j];
		}
	}

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		system("cls");
		std::cout << "�������" << i + 1 << "�����̶���Դ���������������" << std::endl;
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			std::cout << "������Ե�" << j + 1 << "����Դ�������������";
			std::cin >> R._MaxNeed[i][j];
			R._Need[i][j] = R._MaxNeed[i][j] - R._Allocation[i][j];
		}
	}
	std::cout << "����������������������������������������������������������������" << std::endl;
	std::cout << "��ʼ���ɹ�����" << std::endl;

	system("pause");
}
