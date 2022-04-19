#include<iostream>
#include<conio.h>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

struct Lots
{
	char name;//имя множества
	vector<vector<string>> lot;//множество
	void filling_sets();//заполнение множеств
	void print(char name, int i);//вывод множеств
	void difference(int choice1, int choice2);//разность множеств
};


Lots mass_lots[6];
ifstream in;
int size(vector<vector<string>>& lot, int i);
bool bez_ycheta(int size1, int choice1, int p);

int main()
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			in.open("input.txt");
		}
		mass_lots[i].filling_sets();
	}
	in.close();
	char name = 'A';
	int numb = 1;
	for (int i = 0; i < 6; i++)
	{
		cout << numb << ") ";
		mass_lots[i].print(name, i);
		(int)name++;
		numb++;
	}
	int choice1, choice2;
	while (true)
	{
		cout << "Выберите первое множество: ";
		cin >> choice1;
		choice1--;
		cout << "Выберите второе множество: ";
		cin >> choice2;
		choice2--;
		Lots dif;
		cout << mass_lots[choice1].name << (char)92 << mass_lots[choice2].name << " = ";
		cout << "{";
		dif.difference(choice1, choice2);
		cout << "}";
		cout << endl;
	}
	return 0;
}

void Lots::filling_sets()
{
	lot.resize(16);
	for (int i = 0; i < 16; i++)
	{
		lot[i].resize(16);
	}
	char ch;
	int counter_bracket = 0, counter_arrow = 0;
	for (int i = 0; i < 1000; i++)
	{
		in.get(ch);
		if (ch == '{')
		{
			counter_bracket++;//подсчёт кол-ва скобок( { ) 
			while (ch != '}')
			{
				for (int i = 0; i < 1000; i++)
				{
					counter_arrow = 0;
					for (int j = 0; j < 1000; j++)
					{
						in.get(ch);
						if (ch == '<')
						{
							counter_arrow++;
						}
						if (ch == '>')
						{
							counter_arrow--;
						}
						if (ch == ',' && counter_bracket == 1 && counter_arrow == 0)
						{
							break;
						}
						if (ch == '{')
						{
							counter_bracket++;
						}
						if (ch == '}')
						{
							counter_bracket--;
						}
						if (ch == '}' && counter_bracket == 0)
						{
							break;
						}
						lot[i][j].push_back(ch);
					}
					if (ch == '}' && counter_bracket == 0)
					{
						break;
					}
				}
			}
		}
		if (ch == '\n')
		{
			break;
		}
	}
}

void Lots::print(char name, int i)
{
	mass_lots[i].name = name;
	cout << name << " = " << "{";
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (lot[i][j] == "")
			{
				break;
			}
			cout << lot[i][j];
		}
		if (lot[i + 1][0] == "")
		{
			cout << "}" << endl;
			break;
		}
		else
		{
			cout << ",";
		}
	}
}

void Lots::difference(int choice1, int choice2)
{
	int open_bracket = 0, close_bracket = 0, count_bracket = 0, end = 0, count_arrow = 0, numb_of_bracket = 0;
	int p = 0, t = 0, a = 0, elements = 0;
	char ch[2];
next:
	for (int i = 0; i < 16; i++)
	{
		end = 0;
		int size1 = size(mass_lots[choice1].lot, p);//размер элемента первого множества
		int size2 = size(mass_lots[choice2].lot, i);//размер элемента второго множества
		if (size1 == 0)
		{
			break;
		}
		for (int j = 0; j < 16; j++)
		{
			if (mass_lots[choice1].lot[p][t] == "}" && size1 == 0)
			{
				p++;
				t = 0;
				i = -1;
				j = 0;
				break;
			}
			if (mass_lots[choice2].lot[i][j] == "" && size1 != 0 && i > 3)
			{
				bool check;
				check = bez_ycheta(size1, choice1, p);
				if (check == true)
				{
					if (elements != 0)
					{
						cout << ",";
					}
					for (int j = 0; j < 16; j++)
					{
						if (mass_lots[choice1].lot[p][j] == "")
						{
							break;
						}
						cout << mass_lots[choice1].lot[p][j];
					}
					p++;
					t = 0;
					i = -1;
					j = 0;
					elements++;
					break;
				}
				p++;
				t = 0;
				i = -1;
				break;
			}
			if (mass_lots[choice1].lot[p][t] == "")
			{
				i = -1;
				p++;
				t = 0;
				break;
			}
			if (mass_lots[choice2].lot[i][j] == "")
			{
				break;
			}
			if (size1 == size2)//сравнение размеров множества
			{

/////////////////////////////////////////////////////////////////////////////////////////////
				if (mass_lots[choice1].lot[p][t] == "<")//поиск кортежей
				{
					while (true)
					{
						if (mass_lots[choice1].lot[p][t] == "")
						{
							break;
						}
						if (mass_lots[choice2].lot[i][j] == "<")//кортеж открыт
						{
							count_arrow++;
						}
						if (mass_lots[choice1].lot[p][t] == mass_lots[choice2].lot[i][j] && count_arrow != 0)
						{
							size1--;
							t++;
							j = 0;
						}
						if (mass_lots[choice2].lot[i][j] == ">")//кортеж закрыт
						{
							count_arrow--;
						}
						if (mass_lots[choice2].lot[i][j] == "" && size1 != 0)//вывод элемента разности
						{
							bool check;
							check = bez_ycheta(size1, choice1, p);
							if (check == true)
							{
								if (elements != 0)
								{
									cout << ",";
								}
								for (int j = 0; j < 30; j++)
								{
									if (mass_lots[choice1].lot[p][j] == "")
									{
										break;
									}
									cout << mass_lots[choice1].lot[p][j];
								}
								p++;
								t = 0;
								i = -1;
								j = 0;
								elements++;
								goto next;
							}
							p++;
							t = 0;
							i = -1;
							goto next;
						}
						if (size1 != 0 && mass_lots[choice2].lot[i][j] == ">")
						{
							size1 = size(mass_lots[choice1].lot, p);
							t = 0;
							i++;
							j = -1;
						}
						j++;
					}
				}
				if (mass_lots[choice1].lot[p][t] == mass_lots[choice2].lot[i][j] && mass_lots[choice1].lot[p][t] != "{")//элементы не содержащие скобок
				{
					size1--;
					t++;
				}
				if (mass_lots[choice1].lot[p][t] == "{")//элемент являющийся подмножеством
				{
					if (mass_lots[choice1].lot[p][t] == "{")
					{
						t++;
					}
					if (mass_lots[choice2].lot[i][j] == "{")
					{
						j++;
					}
					for (int n = 0; n < size1; n++)
					{
						if (mass_lots[choice1].lot[p][n] == "{")//подмножество открыто
						{
							count_bracket++;
						}
						if (mass_lots[choice1].lot[p][n] == "}" && mass_lots[choice1].lot[p][n + 1] == "")
						{
							//поиск подмножеств в подмножестве
							numb_of_bracket = count_bracket;
							count_bracket = 0;
							if (numb_of_bracket == 1 && choice1 == choice2)
							{
								t--;
								j--;
							}
							break;
						}
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////
					while (true)
					{
						if (mass_lots[choice2].lot[i][j] == "")
						{
							break;
						}
						if (size1 == 2)
						{
							p++;
							break;
						}
						if (mass_lots[choice2].lot[i][j] == "{")
						{
							count_bracket++;
						}
						if (mass_lots[choice2].lot[i][j] == "}")
						{
							count_bracket--;
						}
						///////////////////////////////////////////////////////////////////////////////////////////////////////
						if (mass_lots[choice1].lot[p][t] == "{")
						{
							while (count_bracket != 0)
							{
								if (mass_lots[choice1].lot[p][t] == mass_lots[choice2].lot[i][j] && count_bracket != 0)//поиск элемента подмножества
								{
									if (mass_lots[choice1].lot[p][t] == "}")//дошёл до конца
									{
										end++;
									}
									size1--;
									t++;
									j = 0;
								}
								if (mass_lots[choice1].lot[p][t] != "" && size1 > 2 && mass_lots[choice1].lot[p][t - 1] == "}")
								{
									count_bracket = 0;
									j = 0;
									break;
								}
								if (size1 > 2 && mass_lots[choice1].lot[p][t] == "}" && end != 0)
								{
									bool check;
									check = bez_ycheta(size1, choice1, p);
									if (check == true)
									{
										if (elements != 0)
										{
											cout << ",";
										}
										for (int j = 0; j < 16; j++)
										{
											if (mass_lots[choice1].lot[p][j] == "")
											{
												break;
											}
											cout << mass_lots[choice1].lot[p][j];
										}
										p++;
										t = 0;
										i = -1;
										j = 0;
										elements++;
										goto next;
									}
									p++;
									t = 0;
									i = -1;
									goto next;
								}
								if (mass_lots[choice2].lot[i][j] == "}")//подмножество закрыто
								{
									count_bracket--;
								}
								if (mass_lots[choice1].lot[p][t] == "}" && end != 0)
								{
									j = 1;
									t++;
									if (size1 == 2)
									{
										p++;
										t = 0;
										goto next;
									}
								}
								j++;
							}
						}
						if (t == 1 && mass_lots[choice1].lot[p][t - 1] == "{" && numb_of_bracket == 1)
						{
							j++;
							continue;
						}
						///////////////////////////////////////////////////////////////////////////////////////////////////////						
						if (mass_lots[choice1].lot[p][t] == mass_lots[choice2].lot[i][j] && count_bracket == 0)
						{
							size1--;
							t++;
							j = 0;
							count_bracket = 0;
						}
						j++;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
}

int size(vector<vector<string>>& lot, int i)
{
	int size = 0;
	while (lot[i][size] != "")
	{
		size++;
	}
	return size;
}

bool bez_ycheta(int size1, int choice1, int p)
{
	int k = 0, d = 0;
	int size2 = 0;
	for (int i = 0; i < p; i++)
	{
		size2 = size(mass_lots[choice1].lot, i);
		for (int j = 0; j < size2; j++)
		{
			if (size1 != size2 && d == 0)
			{
				break;
			}
			else
			{
				if (mass_lots[choice1].lot[p][k] == mass_lots[choice1].lot[i][j])
				{
					k++;
					size1--;
					d--;
				}
			}

		}
	}
	if (size1 == 0)
	{
		return false;
	}
	if (size1 != 0 || size2 == 0)
	{
		return true;
	}
	
}
