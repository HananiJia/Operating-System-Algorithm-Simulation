#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<queue>

class pcb
{
public:
	std::string _name;	//������
	size_t _time_come;	//����ʱ��
	size_t _time_nowneed;	//��ǰ����Ҫ�ķ���ʱ��
	size_t _time_need;	//�ܵ���Ҫ����ʱ��
	size_t _time_begin;	//����ʼʱ��
	size_t _time_finish;	//���ʱ��
	size_t _weight;	//���ȼ�
	size_t _time_T;	//��תʱ��
	double _time_T_Weight;	//��Ȩ��תʱ��

	pcb(std::string name, size_t time_come, size_t time_need,size_t weight = 0)
	{
		_name = name;
		_time_come = time_come;
		_time_nowneed = time_need;
		_time_begin = INT_MAX;
		_time_need = time_need;
		_time_finish = INT_MAX;
		_weight = weight;
	}

	void setweight(size_t weight)	//set���ȼ�
	{
		_weight = weight;
	}

	void print(int flag = 0)
	{
		std::cout << "���̣�" << _name << " ���" << _time_come << " �������" << _time_need;
		if (flag == 1)
			std::cout << " ����Ȩ��" << _weight;
	}

	void SetTTimeAndTTimeWithW()	//������תʱ��ʹ�Ȩ��תʱ��
	{
		_time_T = _time_finish - _time_come;
		_time_T_Weight = (double)_time_T / (double)_time_need;
	}

	friend bool CmpByFcfs(pcb& a, pcb& b);	//����FCFS����
	friend bool CmpBySjf(pcb& a, pcb& b);	//����SJF����
	friend bool CmpByPsa(pcb& a, pcb& b);	//����PSA����
};

void PintfPcbs(std::vector<pcb>& pcbs,int flag = 0)
{
	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		pcbs[i].print(flag);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool CmpByFcfs(pcb& a, pcb& b)
{
	return a._time_come < b._time_come;
}

bool CmpBySjf(pcb& a, pcb& b)
{
	return a._time_need < b._time_need;
}

bool CmpByPsa(pcb& a, pcb& b)
{
	return a._weight > b._weight;
}

void GetPcbs(std::vector<pcb>& pcbs,int flag = 0)
{
	system("cls");
	size_t num;
	std::string name;
	size_t time_come;
	size_t time_need;
	size_t weight;
	
	std::cout << "������ģ���㷨�н���������";
	std::cin >> num;
	for (size_t i = 0; i < num; ++i)
	{
		system("cls");
		std::cout << "�������������";
		std::cin >> name;
		std::cout << "�����뵽��ʱ�䣺";
		std::cin >> time_come;
		std::cout << "�������������ʱ�䣺";
		std::cin >> time_need;
		pcbs.push_back(pcb(name, time_come, time_need));
		if (flag == 1)
		{
			std::cout << "������������ȼ���";
			std::cin >> weight;
			pcbs.back().setweight(weight);
		}
	}
	system("cls");
}

void GetRoundTime(size_t& times)
{
	system("cls");
	std::cout << "������ʱ��Ƭ��С��";
	std::cin >> times;
}

void SortPcbsByFCFS(std::vector<pcb>& pcbs)
{
	sort(pcbs.begin(), pcbs.end(), CmpByFcfs);
}

void FCFS(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs);
	size_t nowtime = 0;

	//���յ���ʱ������
	SortPcbsByFCFS(pcbs);

	//��finishʱ�����
	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		if (nowtime < pcbs[i]._time_come)
		{
			nowtime = pcbs[i]._time_come;
		}
		pcbs[i]._time_finish = pcbs[i]._time_need + nowtime;
		pcbs[i]._time_begin = nowtime;
		nowtime += pcbs[i]._time_need;
	}

	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		pcbs[i].print();
		std::cout << " ���ʱ�䣺"<<pcbs[i]._time_finish << std::endl;
	}
	system("pause");
}

void SortPcbsBySJF(std::vector<pcb>& pcbs)
{
	if (pcbs.size() == 0)
		return;
	sort(pcbs.begin(), pcbs.end(), CmpBySjf);
}

void SJF(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs);
	size_t nowtime = 0;
	std::vector<pcb> pcbQ;
	SortPcbsByFCFS(pcbs);

	size_t index = 0;
	while (1)
	{
		if (pcbQ.empty() && index >= pcbs.size())
			break;
		if (pcbQ.empty())
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}

		if (pcbQ[0]._time_come > nowtime)
			nowtime = pcbQ[0]._time_come;

		while (index < pcbs.size() && pcbs[index]._time_come <= nowtime)
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}
		SortPcbsBySJF(pcbQ);

		//ȡ��ͷpcb������
		pcb nowpcb(pcbQ[0]);
		pcbQ[0] = pcbQ[pcbQ.size() - 1];
		pcbQ.pop_back();

		//����ղ�ȡ����pcb��finishʱ��
		nowpcb._time_begin = nowtime;
		nowpcb._time_finish = nowpcb._time_need + nowtime;
		nowtime += nowpcb._time_need;
		nowpcb.SetTTimeAndTTimeWithW();
		nowpcb.print();
		std::cout << " ��ʼ��" << nowpcb._time_begin << " ��ɣ�" << nowpcb._time_finish <<
			" ��ת��"<<nowpcb._time_T<<" ��Ȩ��ת��"<<nowpcb._time_T_Weight<< std::endl;
		SortPcbsBySJF(pcbQ);
	}
	system("pause");
}

void RR(std::vector<pcb>& pcbs, std::size_t times)
{
	PintfPcbs(pcbs);
	SortPcbsByFCFS(pcbs);
	size_t  nowtime = 0;
	std::queue<pcb> pcbQ;

	size_t index = 0;
	while (1)
	{
		if (pcbQ.empty() && index >= pcbs.size())
			break;
		if (pcbQ.empty())
		{
			pcbQ.push(pcbs[index]);
			index++;
		}
		if (pcbQ.front()._time_come > nowtime)
			nowtime = pcbQ.front()._time_come;

		while (index < pcbs.size() && pcbs[index]._time_come <= nowtime + 1)
		{
			pcbQ.push(pcbs[index]);
			index++;
		}

		//ȡ��ͷpcb������
		pcb nowpcb(pcbQ.front());
		pcbQ.pop();

		if (nowpcb._time_begin == INT_MAX)
			nowpcb._time_begin = nowtime;

		if (nowpcb._time_nowneed <= times)
		{
			nowpcb._time_finish = nowpcb._time_nowneed + nowtime;
			nowtime += nowpcb._time_nowneed;
			nowpcb.SetTTimeAndTTimeWithW();
			nowpcb.print();
			std::cout << " ��ʼ��" << nowpcb._time_begin << " ��ɣ�" << nowpcb._time_finish <<
				" ��ת��" << nowpcb._time_T << " ��Ȩ��ת��" << nowpcb._time_T_Weight << std::endl;
		}
		else
		{
			nowpcb._time_nowneed -= times;
			nowtime += times;
			pcbQ.push(nowpcb);
		}
	}
	system("pause");
}

void SortPcbsByPSA(std::vector<pcb>& pcbs)
{
	if (pcbs.size() == 0)
		return;
	sort(pcbs.begin(), pcbs.end(), CmpByPsa);
}

void PSA(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs, 1);
	size_t nowtime = 0;
	size_t index = 0;
	std::vector<pcb> pcbQ;
	SortPcbsByFCFS(pcbs);

	while (1)
	{
		if (pcbQ.empty() && index >= pcbs.size())
			break;
		if (pcbQ.empty())
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}

		while (index < pcbs.size() && pcbs[index]._time_come <= nowtime)
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}
		SortPcbsByPSA(pcbQ);

		if (pcbQ.front()._time_come > nowtime)
			nowtime = pcbQ.front()._time_come;

		if (pcbQ.front()._time_begin == INT_MAX)
			pcbQ.front()._time_begin = nowtime;

		if (pcbQ.front()._time_nowneed == 1)
		{
			pcbQ.front()._time_nowneed = 0;
			pcbQ.front()._time_finish = nowtime + 1;
			nowtime++;
			pcbQ.front().SetTTimeAndTTimeWithW();
			pcbQ.front().print(1);
			std::cout << " ��ʼ��" << pcbQ.front()._time_begin << " ��ɣ�" << pcbQ.front()._time_finish <<
				" ��ת��" << pcbQ.front()._time_T << " ��Ȩ��ת��" << pcbQ.front()._time_T_Weight << std::endl;
			pcbQ.front() = pcbQ.back();
			pcbQ.pop_back();
		}
		else
		{
			pcbQ.front()._time_nowneed --;
			nowtime++;
		}
	}
	system("pause");
}


