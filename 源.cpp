#include<string>
#include<iostream>
#include<deque>
#include<algorithm>
#include <stdlib.h>
#define movingtime 5
using namespace std;
class Tank
{
public:
	string name;//̹������
	string starlevel;//�Ǽ�
	int ID;//���
	int price;//����ķѵĽ��
	int producingtime;//����ķѵ�ʱ��
	int repairtime;//ά�޵�ʱ��
	int special_attack;//���⹥��������
	int normal_attack;//��ͨ����������
	int defense;//��������ֵ
	int maxHp;//��Ѫ��
	double Hp;//Ѫ��
	bool survivalstate;//�ж��Ƿ���,'1'������,'0'�����ѱ���
	bool transformation;//�ж��Ƿ����,'1'�����Ӱ̹��δ���ڱ���״̬���ܱ�������״̬��'0'�����ڱ���״̬
	bool basestate;//�ж��Ƿ��ս,'1'�����ڻ���,'0'�����ڻ���
	virtual void battle(int, int) {}//�����۳�Ѫ��
	virtual void starlevel_up() {}//���������Ǽ���
	Tank(string Name, int Price, int Producingtime, int Repairtime, int Normal_attack, int Defense, int MaxHp, string Starlevel, double _Hp, bool Survivalstate, bool Basestate) :
		name(Name), price(Price), producingtime(Producingtime), repairtime(Repairtime), normal_attack(Normal_attack), defense(Defense), maxHp(MaxHp), starlevel("\0"), Hp(_Hp), survivalstate(Survivalstate), basestate(Basestate) {}
};
class Bear :public Tank
{
public:
	string name = "Bear";
	string starlevel = "\0";
	int ID;
	int price = 600;
	int producingtime = 1;
	int normal_attack = 30;
	int defense = 15;
	int maxHp = 100;
	double Hp = 100;
	bool survivalstate = 1;
	bool basestate = 1;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= attack_strength - defense_strength;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::normal_attack += 5;
		Tank::defense += 5;
	}
	Bear() :Tank("Bear", 600, 1, 0, 30, 15, 100, "\0", 100, 1, 1) {}
};
class Phantom :public Tank
{
public:
	string name = "Phantom";
	string starlevel = "\0";
	int ID;
	int price = 1000;
	int productingtime = 2;
	int normal_attack = 40;
	int defense = 15;
	int maxHp = 100;
	double Hp = 100;
	bool survivalstate = 1;
	bool transformation = 1;
	bool basestate = 1;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= attack_strength - defense_strength;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::normal_attack += 5;
		Tank::defense += 5;
	}
	Phantom() :Tank("Phantom", 1000, 2, 0, 40, 15, 100, "\0", 100, 1, 1) { Tank::transformation = 1; }
};
class Prism :public Tank
{
public:
	string name = "Prism";
	string starlevel = "\0";
	int ID;
	int price = 1200;
	int productingtime = 4;
	int special_attack = 50;
	int defense = 10;
	int maxHp = 100;
	double Hp = 100;
	bool survivalstate = 1;
	bool basestate = 1;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= attack_strength - defense_strength;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::defense += 5;
	}
	Prism() :Tank("Prism", 1200, 4, 0, 0, 10, 100, "\0", 100, 1, 1) { Tank::special_attack = 50; }
};
class Apocalypse :public Tank
{
public:
	string name = "Apocalypse";
	string starlevel = "\0";
	int ID;
	int price = 1750;
	int productingtime = 6;
	int normal_attack = 60;
	int defense = 20;
	int maxHp = 120;
	double Hp = 120;
	bool survivalstate = 1;
	bool basestate = 1;
	double damage_reduction = 0.8;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= (attack_strength - defense_strength) * 0.8;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::normal_attack += 5;
		Tank::defense += 5;
	}
	Apocalypse() :Tank("Apocalypse", 1750, 6, 0, 60, 20, 120, "\0", 120, 1, 1) {}
};
class Spy
{
public:
	int starlevel = 0;//�Ǽ�
	int invasion_time;//���ֵ��Է���������ʱ��
	Spy(int _starlevel) {
		starlevel = _starlevel;
		switch (starlevel) {
		case 1:invasion_time = 40; break;
		case 2:invasion_time = 20; break;
		case 3:invasion_time = 5; break;
		}
	}
};
typedef deque<Tank*>::iterator Iterator;//����������������
void producing(int& _totalmoney, int& _time, int _invadedtime, deque<Tank*>& tmp) {
	//'0'Ϊ����,'1'Ϊ��Ӱ,'2'Ϊ����,'3'Ϊ����
	int i = 0;
	switch (i)
	{
	case 0:if (_totalmoney >= 600)
	{
		if (_time + 1 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Bear());
		_totalmoney -= 600;
		_time += 1;
	}
	case 1:if (_totalmoney >= 1000)
	{
		if (_time + 2 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Phantom());
		_totalmoney -= 1000;
		_time += 2;
	}
	case 2:if (_totalmoney > 1200)
	{
		if (_time + 4 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Prism());
		_totalmoney -= 1200;
		_time += 4;
	}
	case 3:if (_totalmoney >= 1750)
	{
		if (_time + 6 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Apocalypse());
		_totalmoney -= 1750;
		_time += 6;
	}
		  break;
	}
}//����̹��
void fighting(Tank* tank1, Tank* tank2) {
	tank1->basestate = 0;//��Ϊ��ս״̬
	tank2->basestate = 0;
	if (tank1->name == "Bear" && tank2->name == "Bear")
	{
		tank1->battle(tank2->normal_attack, tank1->defense);
		tank2->battle(tank1->normal_attack, tank2->defense);
	}//Bear Vs Bear

	if ((tank1->name == "Bear" && tank2->name == "Phantom") || (tank2->name == "Bear" && tank1->name == "Phantom"))
	{
		if (tank1->transformation == 1 && tank1->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
		}
		else if (tank2->transformation == 1 && tank2->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank2->transformation = 0;
		}
		else if (tank2->transformation == 0 && tank1->name == "Bear")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->transformation = 1;
		}
		else if (tank1->transformation == 0 && tank2->name == "Bear")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 1;
		}
	}//Bera Vs Phantom

	if ((tank1->name == "Bear" && tank2->name == "Prism") || (tank2->name == "Bear" && tank1->name == "Prism"))
	{
		if (tank1->name == "Bear")
		{
			tank1->battle(tank2->special_attack, 0);
			tank2->battle(tank1->normal_attack, tank2->defense);
		}
		if (tank2->name == "Bear")
		{
			tank2->battle(tank1->special_attack, 0);
			tank1->battle(tank2->normal_attack, tank1->defense);
		}
	}//Bear Vs Prism

	if ((tank1->name == "Bear" && tank2->name == "Apocalypse") || (tank1->name == "Apocalypse" && tank2->name == "Bear"))
	{
		if (tank1->name == "Bear")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
		}
		if (tank2->name == "Bear")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->battle(tank2->normal_attack, tank1->defense);
		}
	}//Bear Vs Apocalypse

	if (tank1->name == "Phantom" && tank2->name == "Phantom")
	{
		if (tank1->transformation == 1 && tank2->transformation == 1)
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
			tank2->transformation = 0;
		}
		else if (tank1->transformation == 0 && tank2->transformation == 0)
		{
			tank1->transformation = 1;
			tank2->transformation = 1;
		}
	}//Phantom Vs Phantom

	if ((tank1->name == "Phantom" && tank2->name == "Prism") || (tank2->name == "Phantom" && tank1->name == "Prism"))
	{
		if (tank1->transformation == 1 && tank2->name == "Prism")
		{
			tank1->battle(tank2->special_attack, 0);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
		}

		else if (tank2->transformation == 1 && tank1->name == "Prism")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->special_attack, 0);
			tank2->transformation = 0;
		}
		else if (tank1->transformation == 0 && tank2->name == "Prism")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 1;
		}
		else if (tank2->transformation == 0 && tank1->name == "Prism")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->transformation = 1;
		}
	}//Phantom Vs Prism

	if ((tank1->name == "Apocalypse" && tank2->name == "Phantom") || (tank2->name == "Apocalypse" && tank1->name == "Phantom"))
	{
		if (tank1->transformation == 1 && tank1->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
		}
		else if (tank2->transformation && tank2->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank2->transformation = 0;
		}
		else if (tank2->transformation == 0 && tank1->name == "Apocalypse")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->transformation = 1;
		}
		else if (tank1->transformation == 0 && tank2->name == "Apocalypse")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 1;
		}
	}//Phantom Vs Apocalypse

	if (tank1->name == "Prism" && tank2->name == "Prism")
	{
		tank1->battle(tank2->special_attack, 0);
		tank2->battle(tank1->special_attack, 0);
	}//Prism Vs Prism

	if ((tank1->name == "Prism" && tank2->name == "Apocalypse") || (tank1->name == "Apocalypse" && tank2->name == "Prism"))
	{
		if (tank1->name == "Prism")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->special_attack, 0);
		}
		if (tank2->name == "Prism")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->battle(tank2->special_attack, 0);
		}
	}//Prism Vs Apocalypse

	if ((tank1->name == "Apocalypse" && tank2->name == "Apocalypse"))
	{
		tank1->battle(tank2->normal_attack, tank1->defense);
		tank2->battle(tank1->normal_attack, tank2->defense);
	}//Apocalypse Vs Apocalypse
}//��ս����
void repair(Tank* tank, int& timecount) {
	tank->basestate = 1;
	if (timecount > 0 && tank->Hp < tank->maxHp)
		tank->Hp += (timecount - 5) * 4;//Ҫ��ȥ�Լ����ػ�������������λʱ��
	if (tank->Hp > tank->maxHp)
		tank->Hp = tank->maxHp;//��ֹһ���Իظ�����ֵ�ع�ͷ
	timecount = 0;//��ջ��۵�ά��ʱ��
}//ά�޺���
void Repairtime(int p, int& Timecount, deque<Tank*>& tank) {
	if (p - 1 >= 0)
	{
		for (int k = 0; k < p; k++)
			tank[k]->repairtime += Timecount;
	}
}//����Ҫά�޵�̹�˼�¼ά��ʱ��
Iterator get_iterator(deque<Tank*>& tmp) {
	for (Iterator k = tmp.begin(); k != tmp.end(); k++)
		if ((*k)->Hp <= 0)return k;
}//����ָ��ս�ܵ�̹�˵�ָ��ĵ�����
int main()
{
	int time = 0;
	int totalmoney;//��ʼ�ܽ��
	int invadedtime;//�з��������ʱ��
	int starlevel_spy;//��������Ǽ�
	string input;
	deque<Tank*> own;
	deque<Tank*> enemy;
	cin >> totalmoney;
	while (true)
	{
		cin >> input;
		if (input == "Bear") { enemy.push_back(new Bear()); continue; }
		if (input == "Phantom") { enemy.push_back(new Phantom()); continue; }
		if (input == "Prism") { enemy.push_back(new Prism()); continue; }
		if (input == "Apocalypse") { enemy.push_back(new Apocalypse()); continue; }
		else { invadedtime = atoi(input.c_str()); break; }
	}//�����з�̹��
	cin >> starlevel_spy; Spy spy(starlevel_spy);
	if (true)
	{
		if ((totalmoney == 0 || invadedtime == 0) && enemy.empty())
		{
			cout << "Time:" << time << " Deadlock! It ended in a draw!";
			return 0;
		}//�������޷�����̹���ҵз�Ҳ��̹��

		if (totalmoney == 0 || invadedtime == 0)
		{
			cout << "Time:" << time << " You lost the war!";
			return 0;
		}//��������ʼ���Ϊ���з������������

		if (enemy.empty())
		{
			cout << "Time:" << time << " You won the war!";
			return 0;
		}//���з�û��̹�ˣ���������

	}//�ж��Ƿ���Բ�ս��ʤ/��
	while (time != invadedtime && totalmoney >= 600)
	{
		producing(totalmoney, time, invadedtime, own);
	}
	if (true)
	{
		if (totalmoney < 600 && time == invadedtime)
		{
			cout << "Time:" << time << " Money is empty, Invaded by enemy spies and production stalled,";
			for (Iterator i = own.begin(); i != own.end(); i++)
			{
				cout << ' ' << (*i)->name;
			}
			cout << '.';
		}//�з�������ֺͽ�����Ĵ���ͬʱ����
		if (totalmoney >= 600 && time == invadedtime)
		{
			cout << "Time:" << time << " Invaded by enemy spies and production stalled,";
			for (Iterator i = own.begin(); i != own.end(); i++)
			{
				cout << ' ' << (*i)->name;
			}
			cout << '.';
		}//���δ���Ĵ������з��������
		if (totalmoney < 600 && time < invadedtime)
		{
			cout << "Time:" << time << " Money is empty and production stalled,";
			for (Iterator i = own.begin(); i != own.end(); i++)
			{
				cout << ' ' << (*i)->name;
			}
			cout << '.';
			time = invadedtime;
			cout << endl << "Time:" << time << " Invaded by enemy spies.";
		}//������Ĵ����з����δ����
	}
	int invationTime = time + spy.invasion_time;
	int round = 1;//ս����ʼ
	int flag = 1;//�ü������ֻ����һ�Σ�
	for (int i = 0, j = 0; !own.empty() && !enemy.empty();)
	{
		i %= own.size(); j %= enemy.size();//forѭ���н���ѭ�������������ñ��ʽ�����Էŵ���������������ַ�ĸΪ������
		own[i]->transformation = 1;//ÿ�غϿ�ʼ���ñ���״̬
		enemy[j]->transformation = 1;
		int timecount = 0;
		time += 5;
		if (i - 1 >= 0)own[i - 1]->basestate = 1;
		if (j - 1 >= 0)enemy[j - 1]->basestate = 1;//����һ�غ�ʤ����̹�˻ص�����
		if (time > invationTime && time - 5 <= invationTime)
		{
			repair(own[i], own[i]->repairtime);
			repair(enemy[j], enemy[j]->repairtime);//��սǰͳһ���ά�޹���
			for (Iterator k = own.begin(); k != own.end(); k++)
			{
				if ((*k)->basestate)(*k)->starlevel_up();
			}
			cout << endl << "Time:" << invationTime + 0.5 << " Spy successfully steal enemy tank technology,";
			for (Iterator k = own.begin(); k != own.end(); k++)
			{
				if ((*k)->basestate)
					cout << ' ' << (*k)->name;
			}
			cout << " will be upgraded!";
			timecount -= 5;//������������һ���ӵ�
		}//��ֹʱ����һ�غϽ�����ǡ����[invationTime-5,invationTime]֮��
		timecount += 5;
		cout << endl << "Time:" << time << " Round " << round << " Start, " << own[i]->name << own[i]->starlevel << " vs " << enemy[j]->name << enemy[j]->starlevel << '.' << endl;
		while (own[i]->Hp > 0 && enemy[j]->Hp > 0)
		{
			repair(own[i], own[i]->repairtime);
			repair(enemy[j], enemy[j]->repairtime);//��սǰͳһ���ά�޹���
			fighting(own[i], enemy[j]);
			if (time == invationTime)
			{//�����������ʱ
				for (Iterator k = own.begin(); k != own.end(); k++)
				{
					if ((*k)->basestate)(*k)->starlevel_up();
				}
				cout << "Time:" << invationTime + 0.5 << " Spy successfully steal enemy tank technology,";
				for (Iterator k = own.begin(); k != own.end(); k++)
				{
					if ((*k)->basestate)
						cout << ' ' << (*k)->name;
				}
				cout << " will be upgraded!" << endl;
			}

			time++;
			timecount++;
		}
		cout << "Time:" << time << " Round " << round << " End, ";
		Repairtime(i, timecount, own);
		Repairtime(j, timecount, enemy);//��¼��Ҫά��̹�˵�ά��ʱ��
		if (true)
		{
			if (own[i]->Hp <= 0 && enemy[j]->Hp <= 0)
			{
				cout << "Deadlock!";
				own.erase(get_iterator(own));
				enemy.erase(get_iterator(enemy));
				if (i == own.size())i=0;
				if (j == enemy.size())j=0;//����ս��̹�˴Ӷ����Ƴ�ǰ�±�ǡ��λ�ڶ���ĩβ�����Ƴ����±���ڶ��г��ȵ�����Խ��
			}//ƽ��
			else if (own[i]->Hp > 0 && enemy[j]->Hp <= 0)
			{
				cout << "You won the encounter!";
				enemy.erase(get_iterator(enemy));
				if (j - 1 >= 0)j %= enemy.size();//������غϵз����˶�ǰһ�غ�Ӯ������Ҫ�����±꣬����Խ��
				if (i + 1 < own.size())
				{
					i++;
				}//�������д���̹����>=2ʱ����Ҫ���±����������¾���ս�����һ��
			}//����̹��ʤ��
			else if (own[i]->Hp <= 0 && enemy[j]->Hp > 0)
			{
				cout << "You lost the encounter!";
				own.erase(get_iterator(own));
				if (i - 1 >= 0)i %= own.size();
				if (j + 1 < enemy.size())
				{
					j++;
				}
			}//�з�̹��ʤ��
		}
		if (!own.empty())
		{
			int f = 0;//ѭ������������������������������
			for (Iterator k = find(own.begin(), own.end(), own[i]); f < own.size(); f++, k++)
			{
				if (k == own.end())k = own.begin();
				if ((*k)->basestate)cout << ' ' << (*k)->name << (*k)->starlevel;
			}
			if(own.size()!=1)//���ս������ʱ������ʣһ��̹�ˣ����ʱ�䲻�ڻ��أ�����Ҫ���"."
			cout << '.';
		}
		round++;
	}
	if (own.empty() && enemy.empty())
		cout << " It ended in a draw!";
	if (!own.empty() && enemy.empty())
		cout << " You won the war!";
	if (own.empty() && !enemy.empty())
		cout << " You lost the war!";
	return 0;
}
//20000 Prism Bear Bear Bear Apocalypse Apocalypse Phantom Phantom Bear 34 1





//#include <iostream>
//#include <string>
//using namespace std;
//#define Tank_Num_Max  100//��ʾ˫���������������̹����Ŀ
//long double Time = 0;//��Ϸ����ʱ��
//int Spy_Grade = 0;//����Ǽ�
//int Invade_Time = 0;//����ʱ��
//
//void Time_Out() {//ʱ���������
//	cout << "Time:" << Time << " ";
//}
//
//class Tank {//����̹��
//public:
//	string Name;
//	int ATK;//��ͨ����
//	int DEF;//����
//	int HP;//Ѫ��
//	int TI;//����ʱ��
//	int PR;//�۸�
//	int Jud_Ser;//�Ƿ���Ҫά���ж�λ
//	int Ret_Time;//���ػ���ʱ��
//	int HP_Max;//���Ѫ��ֵ
//	int Str_Time;//����ʱ��
//	Tank() :ATK(0), DEF(0), HP(0), TI(0), PR(0), Name("Tank"), Jud_Ser(0), Ret_Time(0), HP_Max(0), Str_Time(0) {}//��ʼ������
//	Tank(int A, int D, int H, int T, int P, string N, int J, int R, int H_M, int S) :ATK(A), DEF(D), HP(H), TI(T), PR(P), Name(N), Jud_Ser(J), Ret_Time(R), HP_Max(H_M), Str_Time(S) {}
//	void Start(void) {//�ӻ��س�������
//		Jud_Ser = 0;
//		Str_Time = (int)Time;
//	}
//	void Back(void) {//���ػ��غ���(���ж�����)
//		Jud_Ser = 1;
//		Ret_Time = (int)Time + 5;//������Ҫ5��ʱ�䣬��ʱTimeΪ����ս��ʱ��
//	}
//	virtual void Skill(int Harm) {}//ÿ��̹�˵ļ��ܣ������̹���յ����˺�������ʵ�ú�����Ϊ��Ӱ������̹��׼����
//	virtual void Attack(Tank* s1) {}//��������
//};
//
//class Bear :public Tank {//����
//public:
//	Bear() :Tank(30, 15, 100, 1, 600, "Bear", 0, 0, 100, 0) {}//��ʼ��
//	void Attack(Tank* s1) {
//		s1->HP -= (ATK - s1->DEF);
//		s1->Skill(ATK - s1->DEF);
//	}
//	void Skill(int Harm) {}//�����⼼��
//};
//
//class Phantom :public Tank {//��Ӱ
//public:
//	int Tran;//�����ж�λ����ʼ��Ϊ1������һ���ܵ��˺�
//	Phantom() :Tank(40, 15, 100, 2, 1000, "Phantom", 0, 0, 100, 0), Tran(1) {}
//	void Attack(Tank* s1) {
//		s1->HP -= (ATK - s1->DEF);
//		s1->Skill(ATK - s1->DEF);
//	}
//	void Skill(int Harm) {//��ͬһ�غ��ڣ��ܵ��˺�����һ�ν�����
//		if (Harm == 0) {//�ж��Ƿ��ܵ��˺�
//			Tran = 1;//��ͬһ�غ��ڣ������һ��û�ܵ��˺�����ô�Ժ�Ҳ�����ܵ��˺�������1����
//		}
//		else {
//			if (Tran % 2 == 0) {
//				HP += Harm;
//			}
//			Tran++;
//		}
//	}
//};
//
//class Prism :public Tank {//����
//public:
//	int Lig_ATK;//���⹥���Ĺ�����
//	Prism() :Tank(0, 10, 100, 4, 1200, "Prism", 0, 0, 100, 0), Lig_ATK(50) {}
//	void Attack(Tank* s1) {
//		s1->HP -= Lig_ATK;//���ӷ���
//		s1->Skill(Lig_ATK);
//	}
//	void Skill(int Harm) {}//�����⼼��
//};
//
//class Apocalypse :public Tank {//����
//public:
//	double Avoid;
//	Apocalypse() :Tank(60, 20, 120, 6, 1750, "Apocalypse", 0, 0, 120, 0), Avoid(0.2) {}
//	void Attack(Tank* s1) {
//		s1->HP -= (ATK - s1->DEF);
//		s1->Skill(ATK - s1->DEF);
//	}
//	void Skill(int Harm) {//�������˼���
//		HP += (int)(Harm * Avoid);
//	}
//};
//
//class Site {//�������
//public:
//	int Gold;//�����
//	Tank* List[Tank_Num_Max];//ս��˳��������̹�˷��뵱��
//	int List_Num;//ս��˳����е�̹����Ŀ
//	Tank* Combat;//����ս����̹��
//	Tank* Winner[Tank_Num_Max];//ʤ��������̹��(��Ҫά��)
//	int Winner_Num;//ʤ�������ڻ������̹����Ŀ
//	Site() {//��ʼ������
//		Gold = 0;
//		List_Num = 0;
//		Winner_Num = 0;
//		Combat = NULL;
//		for (int i = 0; i < Tank_Num_Max; i++) {
//			List[i] = NULL;
//			Winner[i] = NULL;
//		}
//	}
//	void Service() {//���ص�ά��̹�˺���
//		for (int i = 0; i < Winner_Num; i++) {
//			if (Winner[i]) {//�ж��Ƿ��ǿ�ָ��NULL
//				if (Winner[i]->Jud_Ser && Time > Winner[i]->Ret_Time) {//��Ҫͬʱ����ά���жϱ�־λΪ1�͵�ǰʱ����ڸ�̹�˷��ػ���ʱ��
//					Winner[i]->HP += 4;
//					if (Winner[i]->HP > Winner[i]->HP_Max) {//�жϵ�ǰ����ֵ�Ƿ�������HP
//						Winner[i]->HP = Winner[i]->HP_Max;//Ѫ��ֱ�Ӹ�ֵΪ���ֵ
//						Winner[i]->Jud_Ser = 0;//��ά���жϱ�־λ��0
//					}
//				}
//			}
//		}
//	}
//
//};
//
//class My_Site :public Site {//�ҷ�����
//public:
//	Tank* PD_List_Tank[4];//̹������˳���
//	My_Site() :Site() {//��������˳��
//		PD_List_Tank[0] = new Bear(); PD_List_Tank[1] = new Phantom();
//		PD_List_Tank[2] = new Prism(); PD_List_Tank[3] = new Apocalypse();
//	}
//	void MY_PD();//�ҷ�������������
//};
//
//class Your_Site :public Site {//�з�����
//public:
//	Your_Site() :Site() {}//���캯��
//	void YO_PD(const string s);//�з�������������
//};
//
//void My_Site::MY_PD() {//�ҷ���������
//	int i = 0;
//	int Spy_Jud = 0;//�ж���������ԭ���Ƿ��������ֵ��£�
//	for (i = 0; Gold >= PD_List_Tank[0]->PR && Time < Invade_Time; ++i %= 4) {
//		if (Gold >= PD_List_Tank[i]->PR) {
//			if ((Time + PD_List_Tank[i]->TI) > Invade_Time) {//���ʱ�䳬���������ʱ����ֹͣ
//				Spy_Jud = 1;
//				break;
//			}
//			Gold -= PD_List_Tank[i]->PR;
//			Time += PD_List_Tank[i]->TI;
//			switch (i) {
//			case 0:List[List_Num] = new Bear();
//				break;
//			case 1:List[List_Num] = new Phantom();
//				break;
//			case 2:List[List_Num] = new Prism();
//				break;
//			case 3:List[List_Num] = new Apocalypse();
//				break;
//			}
//			List_Num++;
//		}
//	}
//	if (Gold < PD_List_Tank[0]->PR && (Spy_Jud || Time >= Invade_Time)) {//�����ǰ����������������κ�̹�˲��������ڼ�����ֵ���
//		Time = Invade_Time;//��ʱʱ����ڼ������ʱ��					 //���и���������������պ����������һ��̹��ʱ��������ʱ��
//		Time_Out();														 //�պõ��ڼ������ʱ��ʱ��Spy_Jud������Ч������Ҫ����ʱ���ж�
//		cout << "Money is empty, Invaded by enemy spies and production stalled, ";
//	}
//	else if (Spy_Jud || Time >= Invade_Time) {//���ֻ����Ϊ������ֵ���
//		Time = Invade_Time;//��ʱʱ����ڼ������ʱ��
//		Time_Out();
//		cout << "Invaded by enemy spies and production stalled, ";
//	}
//	else if (Gold < PD_List_Tank[0]->PR) {//���ֻ����Ϊ��Ҳ�������
//		Time_Out();
//		cout << "Money is empty and production stalled, ";
//	}
//	for (i = 0; i < List_Num; i++) {//�����ǰ�Ѿ�������̹��
//		if (i == 0) {
//			cout << List[i]->Name;
//		}
//		else {
//			cout << " " << List[i]->Name;
//		}
//	}
//	cout << "." << endl;
//	if (Time < Invade_Time) {//�ж�ʱ���Ƿ񵽴�������ʱ�䣬ǰ��ֻ��ֻ����Ϊ��Ҳ��������޷����������δ��ʱ���޸ģ�����Ҳֻ�и������Ҫ�����Invaded by enemy spies.��
//		Time = Invade_Time;//��ʱʱ����ڼ������ʱ��
//		Time_Out();
//		cout << "Invaded by enemy spies." << endl;
//	}
//}
//
//bool Jud_Spy_0ut = true;//�����������Ƿ�ִ�е��жϱ���
//My_Site MY;//�ҷ�ʵ�ʻ���
//Your_Site Your;//�ط�ʵ�ʻ���
//int Round = 0;//�غ�����
//
//void Spy_Out(Site& M) {//�ҷ�������������
//	cout << "Time:" << (Time + 0.5) << " ";
//	if (M.List_Num == 0) {//�жϵ�ǰ�����Ƿ���̹��
//		cout << "Spy successfullysteal enemy tank technology." << endl;
//	}
//	else {
//		cout << "Spy successfully steal enemy tank technology, ";
//		for (int i = 0; i < M.List_Num; i++) {
//			if (M.List[i]->Ret_Time <= (Time + 0.5) || M.List[i]->Str_Time >= (Time + 0.5) || M.List[i]->Str_Time == 0) {//�ڳ���֮ǰ���߻���֮�����ڳ���ʱ���ʼ����0�����ڻ���δ������̹�˳���ʱ��Ϊ��
//				cout << M.List[i]->Name << " ";
//				M.List[i]->Name += "*";
//				M.List[i]->ATK += 5;
//				M.List[i]->DEF += 5;
//			}
//		}
//		cout << "will be upgraded!" << endl;
//	}
//	Jud_Spy_0ut = false;//�����ж��Ƿ���Ҫ����ú�������ʡʱ��
//}
//
//void My_Spy_Act() {//����ж��������������ж�λΪ0����Ҫ���뺯��if�ڲ�
//	if (Jud_Spy_0ut) {
//		if (Spy_Grade == 3) {
//			if (Time == (5.0 + Invade_Time)) {
//				Spy_Out(MY);
//			}
//		}
//		else if (Spy_Grade == 2) {
//			if (Time == (20.0 + Invade_Time)) {
//				Spy_Out(MY);
//			}
//		}
//		else if (Spy_Grade == 1) {
//			if (Time == (40.0 + Invade_Time)) {
//				Spy_Out(MY);
//			}
//		}
//	}
//}
//
//void Road() {//̹�˳������򷵻أ���ǰ�����򷵻أ�ʱ�亯��
//	for (int i = 0; i < 5; i++) {//��Ҫ�����λʱ��
//		My_Spy_Act();//�ҷ�������жϺ���
//		MY.Service();//�ҷ����ص�ά�޺���
//		Your.Service();//�з����ص�ά�޺���
//		Time++;
//	}
//}
//
//void Road_Fight() {//ս�����̵�ʱ�䴦��
//	My_Spy_Act();//�ҷ�������жϺ���
//	MY.Service();//�ҷ����ص�ά�޺���
//	Your.Service();//�з����ص�ά�޺���
//	Time++;
//}
//
//void Your_Site::YO_PD(const string s) {//�з����ص���������
//	if (s == "Bear") {
//		List[List_Num] = new Bear();
//		List_Num++;
//	}
//	else if (s == "Phantom") {
//		List[List_Num] = new Phantom();
//		List_Num++;
//	}
//	else if (s == "Prism") {
//		List[List_Num] = new Prism();
//		List_Num++;
//	}
//	else if (s == "Apocalypse") {
//		List[List_Num] = new Apocalypse();
//		List_Num++;
//	}
//}
//
//bool Jud_S_N(const string s) {//�ж������ַ�������������
//	if (s[0] <= 57 && s[0] >= 48) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}
//
//void Game_Init() {//��ʼ����Ϸ
//	cin >> MY.Gold;//�����Ǯ
//	string temp;//����
//	while (cin >> temp && Jud_S_N(temp)) {//����з����ص�̹�˺�˳��
//		Your.YO_PD(temp);
//	}
//	Invade_Time = std::stoi(temp);//�ַ���ת���ֺ�������������ʱ��
//	cin >> Spy_Grade;//�����������Ǽ�
//	if (MY.Gold >= MY.PD_List_Tank[0]->PR && Your.List[0] != NULL && Invade_Time >= 1) {//˫������̹�����
//		MY.MY_PD();
//	}
//	else {//һ��û��̹�����������Ҫս���ˣ�����ֱ�ӵó�ս�����������ù��̣��ҷ�����û�н���̹����������MY.List[0] == NULL���Գ���
//		Time_Out();
//		if (Your.List[0] != NULL && (MY.Gold < MY.PD_List_Tank[0]->PR || Invade_Time == 0)) {//ʧ������
//			cout << "You lost the war!" << endl;
//		}
//		if (Your.List[0] == NULL && (MY.Gold >= MY.PD_List_Tank[0]->PR && (Invade_Time > 0))) {//��ʤ����
//			cout << "You won the war!" << endl;
//		}
//		if (Your.List[0] == NULL && (MY.Gold < MY.PD_List_Tank[0]->PR || Invade_Time == 0)) {//�;�����
//			cout << "It ended in a draw!" << endl;
//		}
//	}
//}
//
//bool Jud_Insert_Winner(Site& M) {//�ж��Ƿ���Ҫ����ʤ��̹�˲���Winner������жϵ�ַ
//	for (int i = 0; i < M.Winner_Num; i++) {
//		if (M.Combat == M.Winner[i]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//
//void Clear_List(Site& M) {//����ʹ�ã���ս��ʧ�ܵ�̹��delete��,�����ж�WInner�������Ƿ��У���ɾ��
//	for (int i = 0; i < M.Winner_Num; i++) {
//		if (M.Combat == M.Winner[i]) {
//			delete M.Combat;
//			for (int j = i; j < M.Winner_Num - 1; j++) {
//				M.Winner[j] = M.Winner[j + 1];
//			}
//			M.Winner[M.Winner_Num - 1] = NULL;
//			M.Combat = NULL;
//			M.Winner_Num--;
//		}
//	}
//	if (M.Combat) {
//		delete M.Combat;
//		M.Combat = NULL;
//	}
//}
//
//void Ready_List(Site& Y) {//ս��ǰʹ�ã���List�������򣬲�ɾ��(�����ǽ���detele����List��̹��ǰ��һλ����һλ����Combat)
//	Y.Combat = Y.List[0];
//	Y.List[0] = NULL;
//	int i = 0;
//	for (i = 0; i < Y.List_Num - 1; i++) {
//		Y.List[i] = Y.List[i + 1];
//	}
//	Y.List[i] = NULL;
//	Y.List_Num--;
//}
//
//void Sort_List(Site& Y) {//Ӯ��ʹ�ã�����˳��
//	if (Jud_Insert_Winner(Y)) {//�жϻ�ʤ��̹���Ƿ��Ѿ�����Winner����
//		Y.Winner[Y.Winner_Num] = Y.Combat;//սʤ��̹�˲���սʤ��̹�˵�������
//		Y.Winner_Num++;
//	}
//	Y.List[Y.List_Num] = Y.Combat;//սʤ��̹�˲���ս��˳����β
//	Y.List_Num++;
//}
//
//void Clear_Place(Site& M, Site& Y) {//Ϊ��һ�غ���׼��(����ս����̹���л�����ʤ��̹�˷��ػ���ά��(�и����ص�ǰ������)���Ҳ嵽��β��ʧ�ܵ�̹��ֱ��delete�����������ص�List_Num��һ��Ȼ����������һ�³���˳��
//	if (M.Combat && Y.Combat) {//�ж��Ƿ��п�ָ��
//		if (M.Combat->HP > 0 && Y.Combat->HP <= 0) {//Ӯ��
//			Clear_List(Y);
//			Sort_List(M);
//		}
//		else if (M.Combat->HP <= 0 && Y.Combat->HP > 0) {//����
//			Clear_List(M);
//			Sort_List(Y);
//		}
//		else {//ƽ��
//			Clear_List(M);
//			Clear_List(Y);
//		}
//	}
//}
//
//void Phantom_Round_Init(Site& M) {//��Ӱ̹�˼��ܵĻغϳ�ʼ��
//	if (M.Combat->Name == "Phantom" || M.Combat->Name == "Phantom*") {
//		M.Combat->Skill(0);
//	}
//}
//
//void Depart_Tank(Site& M, Site& Y) {//̹�˵ĳ�������
//	Y.Combat = Y.List[0];
//	M.Combat = M.List[0];
//	Ready_List(M);
//	Ready_List(Y);
//	if (Y.Combat && M.Combat) {//�ж��Ƿ��п�ָ��
//		M.Combat->Start();
//		Y.Combat->Start();
//		Phantom_Round_Init(M);
//		Phantom_Round_Init(Y);
//	}
//}
//
//void Round_Start(Site& M, Site& Y) {//�غϿ�ʼ����
//	Depart_Tank(M, Y);
//	Road();
//	Time_Out();
//	if (Y.Combat && M.Combat) {//�ж��Ƿ��п�ָ��
//		Round++;
//		cout << "Round " << Round << " Start, " << M.Combat->Name << " " << "vs " << Y.Combat->Name << "." << endl;
//	}
//}
//
//void Jud_Result() {//�ж�˫���������ճɰܽ������
//	if (MY.List[0] == NULL && Your.List[0] != NULL) {
//		cout << " You lost the war!";
//	}
//	else if (MY.List[0] != NULL && Your.List[0] == NULL) {
//		cout << " You won the war!";
//	}
//	else if (MY.List[0] == NULL && Your.List[0] == NULL) {
//		cout << " It ended in a draw!";
//	}
//	cout << endl;
//}
//
//void My_Tank(Site& M) {//��������µ�̹�ˣ�ÿ�غϽ�����ʹ�ã�
//	for (int i = 0; i < M.List_Num; i++) {
//		cout << " " << M.List[i]->Name;
//	}
//	if (M.List_Num != 0) {
//		cout << ".";
//	}
//}
//
//void Round_End(Site& M, Site& Y) {//�غϽ�������ָ�����(��Ҫ����̹�˻���)
//	Time_Out();
//	cout << "Round " << Round << " End, ";
//	if (M.Combat && Y.Combat) {
//		if (M.Combat->HP > 0 && Y.Combat->HP <= 0) {//Ӯ��
//			M.Combat->Back();
//			cout << "You won the encounter!";
//			My_Tank(M);
//		}
//		else if (M.Combat->HP <= 0 && Y.Combat->HP > 0) {//����
//			Y.Combat->Back();
//			cout << "You lost the encounter!";
//			My_Tank(M);
//		}
//		else {//ƽ��
//			cout << "Deadlock!";
//			My_Tank(M);
//		}
//	}
//}
//
//void Fight_Course(Site& M, Site& Y) {//ս����
//	if (M.Combat && Y.Combat) {//˫��ս��ǰ�������ǿ�ָ��
//		while (M.Combat->HP > 0 && Y.Combat->HP > 0) {//���ÿ��ս��ǰ���߱��붼����
//			M.Combat->Attack(Y.Combat);
//			Y.Combat->Attack(M.Combat);
//			Road_Fight();//ս��ʱ�䴦����
//		}
//	}
//}
//
//int main() {
//	Game_Init();//��Ϸ��ʼ��
//	while (MY.List[0] && Your.List[0]) {//�ж�˫���Ƿ���̹��
//		Round_Start(MY, Your);//�غϿ�ʼ
//		Fight_Course(MY, Your);//ս����
//		Round_End(MY, Your);//�غϽ���
//		Clear_Place(MY, Your);//��ɨս��
//		Jud_Result();//�ж�˫���������ճɰܽ������
//	}
//	return 0;
//}