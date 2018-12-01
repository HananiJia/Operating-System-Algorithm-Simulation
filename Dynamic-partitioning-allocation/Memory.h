#pragma once
#include<iostream>
#include<stdlib.h>
#include<list>
#include<vector>

#include<queue>

class MemoryBlock
{
public:
	size_t _length;
	size_t _start;
	size_t _end;
	
	MemoryBlock(size_t length, size_t start = 0)
	{
		_length = length;
		_start = start;
		_end = _start + _length - 1;
	}

	MemoryBlock(const MemoryBlock& m)
	{
		_length = m._length;
		_start = m._start;
		_end = m._end;
	}

	void Print()
	{
		std::cout << "  ��ʼ��ַ��" <<_start;
		std::cout << "  ������ַ��" <<_end;
		std::cout << "  �ڴ���С��" << _length << std::endl;
	}

	friend bool CmpByFF(MemoryBlock& a, MemoryBlock& b);
};

void InitMB(std::list<MemoryBlock> &MB)
{
	system("cls");
	size_t size = 0;
	std::cout << "�������ʼ�ڴ��ܴ�С��";
	std::cin >> size;
	MemoryBlock NewMB(size);
	MB.push_back(NewMB);
	std::cout << "�ڴ��ʼ���ɹ�!!" << std::endl;
	system("pause");
}

void MBPrintf(std::list<MemoryBlock> &MB)
{
	if (MB.empty())
		std::cout << "��" << std::endl;
	//std::list<MemoryBlock>::iterator i = MB.begin();
	size_t i = 0;
	for (auto m : MB)
	{
		std::cout << "�ڴ���ţ�" << i++;
		m.Print();
	}
	std::cout << std::endl;
}

bool CmpByFF(MemoryBlock& a, MemoryBlock& b)
{
	return a._start < b._start;
}

void SortMBByFF(std::list<MemoryBlock> &MB)
{
	MB.sort(CmpByFF);
}

void MallocMBByFF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock>& UsedMB)
{
	size_t size;
	std::cout << "��������Ҫ���������ڴ���С��";
	std::cin >> size;

	std::list<MemoryBlock>::iterator it = FreeMB.begin();
	for (;it!=FreeMB.end();++it)
	{
		if ((*it)._length >= size)
		{
			std::cout << "�ڴ����ɹ�,������ڴ�����£�" << std::endl;
			if ((*it)._length > size)
			{
				MemoryBlock NewMB(size, (*it)._start);
				(*it)._start += size;
				(*it)._length -= size;
				UsedMB.push_back(NewMB);
				NewMB.Print();
			}
			else
			{
				(*it).Print();
				UsedMB.push_back((*it));
				FreeMB.erase(it);
			}
			SortMBByFF(UsedMB);
			SortMBByFF(FreeMB);
			system("pause");
			return;
		}
	}
	std::cout << "�ڴ����ʧ�ܣ�δ�ҵ����ʿɷ���Ŀ����ڴ��" << std::endl;
	system("pause");
	return;
}

void FreeMBByFF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock> &UsedMB)
{
	size_t ID;
	std::cout << "��������Ҫ���յ��ڴ��ţ�";
	std::cin >> ID;
	if (ID >= UsedMB.size())
	{
		std::cout << "��ų�����Χ�������ڴ�ʧ�ܣ���" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = UsedMB.begin();
	if (ID != 0)
	{
		while (ID--)
			it++;
	}
	FreeMB.push_back(*it);
	UsedMB.erase(it);
	SortMBByFF(FreeMB);

	for(int i = 0; i< 2 && FreeMB.size() > 1; ++i)
	{
		std::list<MemoryBlock>::iterator it = FreeMB.begin();
		std::list<MemoryBlock>::iterator its = it;
		its++;
		for (; its != FreeMB.end(); ++it,++its)
		{
			if ((*it)._end + 1 == (*its)._start)
			{
				(*its)._start = (*it)._start;
				(*its)._length += (*it)._length;
				FreeMB.erase(it);
				break;
			}
		}
	}

	std::cout << "�ڴ���ճɹ�����" << std::endl;
	system("pause");

}

void FistFit()
{
	std::list<MemoryBlock> FreeMB;
	std::list<MemoryBlock> UsedMB;
	InitMB(FreeMB);

	char c = 0;
	size_t MBLenth = 0;
	while (1)
	{
		system("cls");
		std::cout << "�����ڴ�飺" << std::endl;
		MBPrintf(FreeMB);
		std::cout << "��ʹ���ڴ�飺" << std::endl;
		MBPrintf(UsedMB);
		
		std::cout << "����ָ�ϣ�1���ڴ����  2�������ڴ�   ��q�˳�����" << std::endl;
		std::cout << "�����������Ҫ���еĲ�����";
		std::cin >> c;
		switch (c)
		{
		case '1':
			MallocMBByFF(FreeMB, UsedMB);
			break;
		case '2':
			FreeMBByFF(FreeMB, UsedMB);
			break;
		case 'q':
			goto end;
		}

	}
end:
	return;
}


