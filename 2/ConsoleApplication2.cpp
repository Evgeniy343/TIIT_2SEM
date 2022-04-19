#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct Edge
{
	Edge* pNext;
	int data;
	Edge(int data = 0, Edge* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
};

Edge* push_back(int data, Edge* node);
bool check_peaks_of_an_odd_degree(bool check, int m, vector<vector<int>>& array_main, bool r);

int main()
{
	setlocale(LC_ALL, "Russian");
	ofstream out("euler.out", ios::trunc);
	out.close();
	ifstream in("euler.in");
	int  n, m;
	vector < vector <int> > array_main;
	for (int vv = 1; vv <= 1; vv++) {
		in >> n;
		in >> m;
		//cout << n << " " << m << endl << endl;
		array_main.resize(m);
		for (int a = 0; a < m; ++a)
			array_main[a].resize(2);
		char ch;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				in >> array_main[i][j];
				//cout << array_main[i][j] << " ";
				in.get(ch);
				if (ch == '\n')
				{
					break;
				}
			}
		}

		bool check = false, r = true;
		check = check_peaks_of_an_odd_degree(check, m, array_main, r);//проверка на наличие вершин нечётной степени
		int mass1[50000];
		if (check)//поиск Эйлерова цикла
		{
			int numb = 1, x = 0, count = 0, a = 0, b = 0;
			bool ch1 = true;
cycle_next:
			int d = numb, p = 0;
			bool check2 = false;
			Edge** check_graph = new Edge* [m];
			for (int i = 0; i < m; i++)
			{
				check_graph[i] = nullptr;
				for (int j = 0; j < array_main.at(i).size(); j++)
				{
					check_graph[i] = push_back(array_main.at(i).at(j), check_graph[i]);
				}
			}
			mass1[a] = numb;//массив записывающий Эйлеров цикл
			a++;
		cycle:
			ch1 = true;
			b = a;
			while (true)
			{
				if (numb == d && check2 == true)
				{
					numb++;
					goto cycle_next;
				}
				if (count == m - 1 && numb == d)
				{
					mass1[a] = numb;
					check = true;
					break;
				}
				for (x = p; x < m; x++)
				{
					if (check_graph[x]->data == d && count == 0)
					{
						goto pNext;
					}
					if (check_graph[x]->pNext->data == d && count == 0)
					{
						goto d;
					}
					if (check_graph[x]->pNext->data == numb)
					{
						goto pNext;
					}
					if (check_graph[x]->data == numb)
					{
						goto d;
					}
				}

d:
				mass1[a] = check_graph[x]->data;
				for (int i = p; i < m; i++)
				{
					if ((check_graph[x]->data == check_graph[i]->data || check_graph[x]->data == check_graph[i]->pNext->data) && x != i)
					{
						if (check_graph[x]->data == check_graph[i]->data)
						{
							numb = check_graph[i]->pNext->data;
						}
						if (check_graph[x]->data == check_graph[i]->pNext->data)
						{
							numb = check_graph[i]->data;
						}
						p = i;
						check_graph[x]->data = 0;
						check_graph[x]->pNext->data = 0;
						count++;
						a++;
						goto cycle;
					}
					if (i == m - 1 && a == b && ch1 == true)
					{
						i = -1;
						ch1 = false;
						continue;
					}
					if (i == m - 1 && ch1 == false)
					{
						count = 0;
						a = 0;
						check2 = true;
						goto cycle;
					}
				}
pNext:
				mass1[a] = check_graph[x]->pNext->data;
				for (int i = p; i < m; i++)
				{
					if ((check_graph[x]->pNext->data == check_graph[i]->data || check_graph[x]->pNext->data == check_graph[i]->pNext->data) && x != i)
					{
						if (check_graph[x]->pNext->data == check_graph[i]->data)
						{
							numb = check_graph[i]->pNext->data;
						}
						if (check_graph[x]->pNext->data == check_graph[i]->pNext->data)
						{
							numb = check_graph[i]->data;
						}
						p = i;
						check_graph[x]->data = 0;
						check_graph[x]->pNext->data = 0;
						count++;
						a++;
						goto cycle;
					}
					if (i == m - 1 && a == b && ch1 == true)
					{
						ch1 = false;
						i = -1;
						continue;
					}
					if (i == m - 1 && ch1 == false)
					{
						count = 0;
						a = 0;
						check2 = true;
						goto cycle;
					}
				}
			}
		}
		else//цикл не найден
		{
		cout << "No" << endl << endl << endl << endl;
			out.open("euler.out", ios::app);
			out << "No";
			out << endl << endl << endl << endl;
			out.close();
		}
		if (check)//вывод цикла
		{
			cout << "Yes" << endl;
			out.open("euler.out", ios::app);
			out << "Yes" << endl;
			for (int i = 0; i <= m; i++)
			{
				cout << mass1[i];
				out << mass1[i];
				if (i != m) { cout << "-"; out << "-"; }
			}
			cout << "\n\n\n\n";
			out << endl << endl << endl << endl;
			out.close();
		}
	}

		return 0;
	}



Edge* push_back(int data, Edge* node)
{
	if (node == nullptr)
	{
		node = new Edge(data);
	}
	else
	{
		Edge* current = node;
		while (current->pNext != 0)
		{
			current = current->pNext;
		}
		current->pNext = new Edge(data);
	}
	return node;
}

bool check_peaks_of_an_odd_degree(bool check, int m, vector<vector<int>>& array_main, bool r)
{
	int mass[1000];
	int p = 0, t = 0, counter = 1, counter1 = 0, k = 0, counter2 = 0;
g:
	for (int i = 0; i < m; i++)
	{
		if (p == m)
		{
			check = true;
			break;
		}
		for (int j = 0; j < 2; j++)
		{
			if (p == 0 && i == 0)
			{
				i = 1;
			}
			if (p > 0 && r == false)
			{
				while (true)// проверка на совпадение вершины
				{
					for (k = 0; k < 1000; k++)
					{
						if (p > m - 1)
						{
							goto g;
						}
						if (mass[k] < 0)
						{
							break;
						}
						if (mass[k] == array_main.at(p).at(t))
						{
							counter1++;
							p++;
							break;
						}
						else
						{
							counter2++;
						}
					}
					if (counter1 == 0)
					{
						r = true;
						break;
					}
					counter1 = 0;
					counter2 = 0;
				}
			}
			if (p == i && t == j)
			{
				goto r;
			}
			else
			{
				if (array_main[p][t] == array_main[i][j])
				{
					counter++;
				}
			}
		r:
			if (counter % 2 != 0 && i == m - 1 && j == 1)
			{
				break;
			}
			if (i == m - 1 && j == 1)
			{
				mass[k] = array_main.at(p).at(t);//запись вершины в массив
				p++;
				r = false;
				i = -1;
				counter = 1;
				break;
			}

		}
	}
	return check;
}


