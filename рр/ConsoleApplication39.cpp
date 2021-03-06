// graf2.cpp: определяет точку входа для консольного приложения.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void cycle(int a, int b, int c, vector<vector<int> > &array_main, int n, int m, int znak, int mas[], int kol, vector<vector<int> > &array2, int dvymer)

{

	int d, d1;

	if (a == 0)
	{

		for (d = 0; d < n; d++)
		{
			if (d != b)
			{
				if (array_main[d][c] != 0)
				{
					for (d1 = 0; d1 < kol; d1++)
					{
						if (d == mas[d1] && kol > 2)
						{
							for (int i = 0;; i++)
							{
								if (i == 98)return;//если кол циклов превышает 99
								if (array2[i][0] == -1)
								{
									dvymer = i;
									break;
								}
							}
							int x = d1;

							for (int y = 0; y < kol - d1; y++)
							{
								array2[dvymer][y] = mas[x];
								x++;

							}
							array2[dvymer][kol - d1] = -1;
							dvymer++;
							array2[dvymer][0] = -1;
							return;
						}
					}

					mas[kol] = d;


					cycle(a = 1, d, c, array_main, n, m, znak, mas, kol + 1, array2, dvymer);
				}
			}
		}
	}
	else
	{
		for (d = 0; d < m; d++)
			if (d != c)
			{

				if (array_main[b][d] != 0)
					cycle(a = 0, b, d, array_main, n, m, znak, mas, kol, array2, dvymer);

			}
	}

}

int peresech(int mass_A[], int mass_B[], int moch_B, int mass_C[], int moch_A)
{

	int c = 0;
	int a = 0;
	int b = 0;


	for (;;)
	{

		if (mass_A[a] == mass_B[b])
		{
			if (a == moch_A) break;
			mass_C[c] = mass_A[a];
			c++;
			b = 0;
			a++;
		}
		else
		{
			b++;
			if (b == moch_B)
			{
				if (a == moch_A) break;
				b = 0;
				a++;
			}
		}
	}
	mass_C[c] = -1;
	return c;
}

void sect(int mas_c[], int a, int b, int c, vector<vector<int> > &array_main, int n, int m, int mas[], int kol, vector<vector<int> > &array2, int kol_c, int granich1, int granich2, int mas_reb[])
{

	int d, d1, dvymer;

	if (a == 0)
	{

		for (d = 0; d < n; d++)
		{
			if (d != b)
			{
				if (array_main[d][c] != 0)
				{

					for (d1 = 0; d1 < kol_c; d1++)
					{
						if (d == mas_c[d1] && kol > 1)
						{
							for (int i = 0; i < 99; i++)
								if (array2[i][0] == -1)
								{
									dvymer = i;
									break;
								}


							for (int y = 0; y < kol; y++)
								array2[dvymer][y] = mas[y];



							array2[dvymer][kol] = d;

							array2[dvymer][kol + 1] = -1;
							dvymer++;
							array2[dvymer][0] = -1;
							return;
						}
						if (d == mas_c[d1] && kol == 1)
						{
							if (kol_c > 3)
							{


								if (d != granich1 && d != granich2)
								{
									for (int i = 0; i < 99; i++)
										if (array2[i][0] == -1)
										{
											dvymer = i;
											break;
										}



									array2[dvymer][0] = mas[0];
									array2[dvymer][1] = d;
									array2[dvymer][2] = -1;
									dvymer++;
									array2[dvymer][0] = -1;
									mas_reb[c] = -2;
									return;

								}
							}
							return;
						}
					}


					mas[kol] = d;


					sect(mas_c, a = 1, d, c, array_main, n, m, mas, kol + 1, array2, kol_c, granich1, granich2, mas_reb);
				}
			}
		}
	}
	else
	{
		for (d = 0; d < m; d++)
			if (d != c)
			{

				if (array_main[b][d] != 0)
				{
					sect(mas_c, a = 0, b, d, array_main, n, m, mas, kol, array2, kol_c, granich1, granich2, mas_reb);
				}

			}
	}

}
void grani(int mas_c[], int poloj, int kol_c, int granich[])
{
	if (poloj == 0)
	{
		granich[0] = mas_c[kol_c - 1];
		granich[1] = mas_c[1];
	}
	if (poloj == kol_c - 1)
	{
		granich[0] = mas_c[kol_c - 2];
		granich[1] = mas_c[0];
	}
	if (poloj != 0 && poloj != kol_c - 1)
	{
		granich[0] = mas_c[poloj - 1];
		granich[1] = mas_c[poloj + 1];
	}
}
void sector(int mas_c[], int kol_c, vector<vector<int> > &array_main, vector<vector<int> > &array_sect, int mas[], int n, int m)
{
	int mas_reb[99];
	int granich[2];

	int d, d1, a;
	for (d1 = 0; d1 < m; d1++)
		mas_reb[d1] = d1;
	mas_reb[m] = -1;

	for (a = 0; a < kol_c; a++)
	{
		grani(mas_c, a, kol_c, granich);
		mas[0] = mas_c[a];
		sect(mas_c, 1, mas_c[a], -1, array_main, n, m, mas, 1, array_sect, kol_c, granich[0], granich[1], mas_reb);

	}
}
void raznost(int mass_A[], int mass_B[], int moch_A, int moch_B, int mass_C[])
{

	int a = 0;
	int b = 0;
	int c = 0;
	if (moch_A == 0 && moch_B == 0)
	{
		mass_C[0] = -1;
		return;
	}
	else
	{
		if (moch_A == 0)
		{
			mass_C[0] = -1;
			return;
		}
		if (moch_B == 0)
		{
			for (a = 0; a < moch_A; a++)
				mass_C[a] = mass_A[a];
			mass_C[moch_A] = -1;
			return;
		}
	}
	a = 0;
	for (;;)
	{
		if (mass_A[a] == mass_B[b])
		{
			if (a == moch_A - 1) break;

			a++;
			b = 0;
		}
		else
		{
			if (b == moch_B - 1)
			{
				mass_C[c] = mass_A[a];
				c++;
				if (a == moch_A - 1) break;

				a++;
				b = 0;
			}
			else
			{
				b++;
			}
		}

	}
	mass_C[c] = -1;

}
int podchet_stolb(vector<vector<int> > &arr, int stroka)
{
	int b;
	for (b = 0;; b++)
	{
		if (arr[stroka][b] == -1)break;
	}
	return b;
}
int podchet_strok(vector<vector<int> > &arr, int stolb)
{
	int b;
	for (b = 0;; b++)
	{
		if (arr[b][stolb] == -1)break;
	}
	return b;
}

void del_same(vector<vector<int> > &array_sect, int num_finish[], int i)
{
	int mass1[99];
	int mass2[99];
	int mass3[99];
	int num[99];
	int num2[99];
	int a, t, h, q, w = 0, b;
	for (a = 0; a < i; a++)
	{

		t = podchet_stolb(array_sect, a);
		for (h = 0; h < t; h++)
			mass1[h] = array_sect[a][h];

		for (b = a + 1; b < i; b++)
		{
			q = podchet_stolb(array_sect, b);
			if (q == t)
			{
				for (h = 0; h < q; h++)
					mass2[h] = array_sect[b][h];
				if (peresech(mass1, mass2, q, mass3, t) == q)
				{
					num[w] = b;
					w++;
					break;
				}
			}
		}
	}
	for (a = 0; a < i; a++)
		num2[a] = a;
	raznost(num2, num, i, w, num_finish);

}
void mass_cycle(vector<vector<int> > &array2, int i, int mas_c[])
{
	int a, num = 0, w, b, num_mas;
	int mass[99];
	del_same(array2, mass, i);
	for (a = 0; ; a++)
		if (mass[a] == -1) break;
	if (a == 0)
	{
		for (b = 0; b < i; b++)
		{
			mass[b] = b;
		}
		mass[i] = -1;
		a = i;
	}
	for (int c = 0; c < a; c++)
	{
		int j = podchet_stolb(array2, mass[c]);
		
	}
	for (b = 0; b < a; b++)
	{
		w = podchet_stolb(array2, mass[b]);
		if (num < w)
		{
			num = w;
			num_mas = b;
		}
	}

	for (a = 0; a < num; a++)
	{
		mas_c[a] = array2[mass[num_mas]][a];
	}
	mas_c[num] = -1;

}

void obmen(int mas[], int x) {
	int a, b = 0;
	int mass2[20];
	for (a = 0; a < x; a++) {
		mass2[a] = mas[b];
		b++;
	}
	b = 0;
	for (a = x - 1; a >= 0; a--) {
		mas[a] = mass2[b];
		b++;
	}
}

int first(int kol_gran, int arr2[], vector<vector<int> > &gran, vector<vector<int> > &array_sect, int kol_sect, int num_str)
{
	int a, i, kol_mest = 0, num = 0, b, c, k, kol_mass2, z, r;
	int mass[99], mass2[99], kol_mes[99], mass3[99], mass4[99];
	for (a = 0; a < kol_gran; a++)
	{
		i = podchet_stolb(gran, a);
		for (b = 0; b < i; b++)
			mass[b] = gran[a][b];

		if (peresech(mass, arr2, 2, mass2, i) == 2)
		{
			kol_mest++;
			kol_mes[num] = a;
			num++;
		}

	}

	if (kol_mest == 0) return 0;
	else
	{
		for (z = 0; z < podchet_stolb(gran, kol_mes[0]); z++)
		{
			if (gran[kol_mes[0]][z] == arr2[0] || gran[kol_mes[0]][z] == arr2[1])break;
		}
		if (gran[kol_mes[0]][z] == arr2[1])
		{
			r = podchet_stolb(gran, kol_mes[0]);
			for (z = 0; z < podchet_stolb(gran, kol_mes[0]); z++)
				mass4[z] = gran[kol_mes[0]][z];
			for (z = 0; z < podchet_stolb(gran, kol_mes[0]); z++)
			{
				gran[kol_mes[0]][z] = mass4[r - 1];
				r--;
			}

		}

		i = podchet_stolb(gran, kol_mes[0]);
		for (b = 0; b < kol_sect; b++)
			mass2[b] = array_sect[num_str][b];

		b = kol_sect;
		if (gran[kol_mes[0]][i - 1] == array_sect[num_str][kol_sect - 1])
		{
			if (gran[kol_mes[0]][0] != array_sect[num_str][0])
			{
				for (c = 0; gran[kol_mes[0]][c] != array_sect[num_str][0]; c++)
					mass3[c] = gran[kol_mes[0]][c];

				for (a = 0; a < c; a++)
				{
					mass2[b] = mass3[a];
					b++;
				}
				kol_mass2 = b;
				mass2[b] = -1;
			}
		}
		if (gran[kol_mes[0]][i - 1] != array_sect[num_str][kol_sect - 1])
		{
			for (k = 0; k < i; k++)
				if (gran[kol_mes[0]][k] == array_sect[num_str][kol_sect - 1])break;
			for (c = k + 1; c < i; c++)
			{
				mass2[b] = gran[kol_mes[0]][c];
				b++;
			}
			kol_mass2 = b;
			mass2[b] = -1;
			if (gran[kol_mes[0]][0] != array_sect[num_str][0])
			{
				for (c = 0; gran[kol_mes[0]][c] != array_sect[num_str][0]; c++)
					mass3[c] = gran[kol_mes[0]][c];
				for (a = 0; a < c; a++)
				{
					mass2[b] = mass3[a];
					b++;
				}
				kol_mass2 = b;
				mass2[b] = -1;
			}
		}
		int e = 0;
		for (k = 0;; k++)
			if (gran[kol_mes[0]][k] == -1)break;
		int kol_toch = k;
		for (k = 0; k < kol_toch; k++)
			if (gran[kol_mes[0]][k] == arr2[0])break;
		int gr1 = k;
		for (k = 0; k < kol_toch; k++)
			if (gran[kol_mes[0]][k] == arr2[1])break;
		int gr2 = k;
		for (k = gr1 + 1; k < gr2; k++)
		{
			mass3[e] = gran[kol_mes[0]][k];
			e++;
		}
		mass3[e] = -1;
		for (b = 0; b < kol_mass2; b++)
			gran[kol_mes[0]][b] = mass2[b];
		gran[kol_mes[0]][kol_mass2] = -1;

		obmen(mass3, e);
		b = kol_sect;
		for (a = 0; a < e; a++)
		{
			mass2[b] = mass3[a];
			b++;
		}
		for (a = 0; a < b; a++)
			gran[kol_gran][a] = mass2[a];
		gran[kol_gran][b] = -1;
		kol_gran++;
	}
	return kol_gran;

}



int Harary_dop(vector<vector<int> > &sector2, int kol_gran, vector<vector<int> > &gran)
{
	int a, x;
	int  arr2[99];




	for (a = 0; a < podchet_strok(sector2, 0); a++)
	{


		if (podchet_stolb(sector2, a) > 2)//ни одна из неконтактных вершин в этом секторе не была использована
		{
			int x;
			x = podchet_stolb(sector2, a);
			arr2[0] = sector2[a][0];
			arr2[1] = sector2[a][x - 1];

			kol_gran = first(kol_gran, arr2, gran, sector2, x, a);
			if (kol_gran == 0)return 0;
		}
		else
		{
			arr2[0] = sector2[a][0];
			arr2[1] = sector2[a][1];

			kol_gran = first(kol_gran, arr2, gran, sector2, 2, a);
			if (kol_gran == 0)return 0;

		}
	}
	return kol_gran;
}
int second(vector<vector<int> > &gran, vector<vector<int> > &array_sect, int num_str, int mass_not_use[], int kol_gran)
{
	int a, i, b, num = 0, kol_mest = 0, d, y;
	int sec[99], mass_use_versh[99], mass[99], mass2[99], kol_mes[99], granich[2], mass3[99];
	int kol_sect = podchet_stolb(array_sect, num_str);
	for (a = 0; a < kol_sect; a++)
		sec[a] = array_sect[num_str][a];
	for (a = 0;; a++)
		if (mass_not_use[a] == -1)break;
	int kol_mass_not_use = a;
	if (kol_mass_not_use == 0)
	{
		for (a = 0; a < kol_sect; a++)
			mass_use_versh[a] = sec[a];
		mass_use_versh[kol_sect] = -1;

	}
	else raznost(sec, mass_not_use, kol_sect, kol_mass_not_use, mass_use_versh);
	for (a = 0;; a++)
		if (mass_use_versh[a] == -1)break;
	int kol_mass_use_versh = a;


	for (a = 0; a < kol_gran; a++)
	{
		i = podchet_stolb(gran, a);
		for (b = 0; b < i; b++)
			mass[b] = gran[a][b];

		if (peresech(mass, mass_use_versh, kol_mass_use_versh, mass2, i) == kol_mass_use_versh)
		{
			kol_mest++;
			kol_mes[num] = a;
			num++;
		}

	}
	if (kol_mest == 0) return 0;
	else
	{
		int c = 0;
		int metka = 0;
		vector<vector<int> > sector2(99, vector<int>(99));
		b = 0;
		for (a = 0;; a++)
		{
			if (metka == 2)break;
			for (;; )
			{
				if (metka == 2)break;
				if (b > 0)
				{
					for (d = 0; d < kol_mass_use_versh; d++)
					{
						if (mass_use_versh[d] == array_sect[num_str][c])
							metka = 1;
					}
					if (metka == 1)
					{
						sector2[a][b] = array_sect[num_str][c];
						if (c == kol_sect - 1)metka = 2;
						sector2[a][b + 1] = -1;
						sector2[a + 1][0] = -1;
						b = 0;
						break;
					}
					else
					{
						sector2[a][b] = array_sect[num_str][c];
						c++;
						b++;
						metka = 0;
					}
				}
				else
				{
					for (d = 0; ; d++)
					{
						if (gran[kol_mes[0]][d] == array_sect[num_str][c]) break;
					}
					for (y = 0; y < podchet_stolb(gran, kol_mes[0]); y++)
						mass3[y] = gran[kol_mes[0]][y];
					grani(mass3, d, podchet_stolb(gran, kol_mes[0]), granich);
					if (granich[0] == array_sect[num_str][c + 1] || granich[1] == array_sect[num_str][c + 1])
					{
						c++;
						if (c == kol_sect - 1)
						{
							metka = 2;
							sector2[0][0] = -1;
						}
					}
					else {
						sector2[a][b] = array_sect[num_str][c];
						c++;
						b++;
					}
				}
			}
		}
		kol_gran = Harary_dop(sector2, kol_gran, gran);
		return kol_gran;
	}
}


int Harary(int n, int mas_c[], int kol_c, vector<vector<int> > &array_sect, int num_finish[])
{
	int a, x, b, c;
	vector<vector<int> > gran(99, vector<int>(99));
	int versh[99], not_kontakt[99], arr[99], arr2[99], mass_not_use[99], not_kontakt2[99];
	for (a = 0;; a++)
		if (num_finish[a] == -1)break;
	int kol_num_finish = a;
	for (a = 0; a < n; a++)
		versh[a] = a;
	raznost(versh, mas_c, n, kol_c, not_kontakt);
	for (a = 0;; a++)
		if (not_kontakt[a] == -1)break;
	int kol_not_kontakt = a;

	for (a = 0; a < kol_c; a++)
	{
		gran[0][a] = mas_c[a];
		gran[1][a] = mas_c[a];
	}
	gran[0][kol_c] = -1;
	gran[1][kol_c] = -1;
	int kol_gran = 2;
	int kol_mest;


	for (a = 0; a < kol_num_finish; a++)
	{
		kol_mest = 0;

		x = podchet_stolb(array_sect, num_finish[a]);
		arr2[0] = array_sect[num_finish[a]][0];//заносим во временный массив все контактные вершины
		arr2[1] = array_sect[num_finish[a]][x - 1];
		if (x > 2) { 
			for (b = 1; b < x - 1; b++)
				arr[b - 1] = array_sect[num_finish[a]][b];//заносим во временный массив все неконтактные вершины
			arr[x - 1] = -1;
			int kol_arr = x - 2;

			for (c = 0;; c++)
				if (not_kontakt[c] == -1)break;
			int kol_not_kontakt;
			kol_not_kontakt = c;
			if (kol_arr == peresech(not_kontakt, arr, kol_arr, mass_not_use, kol_not_kontakt) && kol_not_kontakt != 0)//ни одна из неконтактных вершин в этом секторе не была использована
			{

				kol_gran = first(kol_gran, arr2, gran, array_sect, x, num_finish[a]);
				if (kol_gran == 0)return 0;

				raznost(not_kontakt, arr, kol_not_kontakt, kol_arr, not_kontakt2);

				for (c = 0;; c++)
					if (not_kontakt2[c] == -1)break;
				for (b = 0; b < c; b++)
					not_kontakt[b] = not_kontakt2[b];
				not_kontakt[c] = -1;
				kol_not_kontakt = c;
				continue;

			}
			if (kol_not_kontakt < peresech(not_kontakt, arr, kol_arr, mass_not_use, kol_not_kontakt) && kol_not_kontakt != 0)//какие то были использованы
			{
				kol_gran = second(gran, array_sect, a, mass_not_use, kol_gran);
				if (kol_gran == 0)return 0;
				raznost(not_kontakt, arr, kol_not_kontakt, kol_arr, not_kontakt2);
				for (a = 0;; a++)
					if (not_kontakt2[a] == -1)break;
				for (b = 0; b < a; b++)
					not_kontakt[b] = not_kontakt2[b];
				not_kontakt[a] = -1;
				kol_not_kontakt = a;
				continue;

			}
			if (peresech(not_kontakt, arr, kol_arr, mass_not_use, kol_not_kontakt) == 0)//все были использованы
			{
				kol_gran = second(gran, array_sect, a, mass_not_use, kol_gran);
				if (kol_gran == 0)return 0;
			}
		}
		else
		{
			for (b = 0; b < 2; b++)
				arr2[b] = array_sect[num_finish[a]][b];
			kol_gran = first(kol_gran, arr2, gran, array_sect, x, num_finish[a]);
			if (kol_gran == 0)return 0;



		}

	}
	return 1;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	
	ifstream in("graf.txt");

	for (int vv = 1; vv <= 5; vv++) {
		int  n, m;
		int num_finish[999];
		vector < vector <int> > array_main;
		in >> n;
		in >> m;
		array_main.resize(n);
		for (int a = 0; a < n; ++a)
			array_main[a].resize(m);

		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> array_main[i][j];
		
		int mas[99];
		vector<vector<int> > array2(99, vector<int>(99));
		array2[0][0] = -1;
		cycle(0, -1, 0, array_main, n, m, 0, mas, 0, array2, 0);


		int j, a, b, i;
		i = podchet_strok(array2, 0);
		if (i == 0)
		{
			cout << "Not cycles";
			system("pause");
			return 0;
		}


		vector<vector<int> > array_sect(99, vector<int>(99));
		array_sect[0][0] = -1;
		int mas_c[99];


		mass_cycle(array2, i, mas_c);
		for (a = 0;; a++)
			if (mas_c[a] == -1)
			{

				break;
			}
		int kol_c;
		kol_c = a;

		sector(mas_c, kol_c, array_main, array_sect, mas, n, m);

		i = podchet_strok(array_sect, 0);

		
		del_same(array_sect, num_finish, i);

		for (b = 0;; b++)
			if (num_finish[b] == -1)break;   
		int k = b;
		for (a = 0; a < k; a++)
		{
			j = podchet_stolb(array_sect, num_finish[a]);
		}


		vector<vector<int> > gran(99, vector<int>(99));
		for (a = 0;; a++)
		{
			if (num_finish[a] == -1)break;
		}
		if (Harary(n, mas_c, kol_c, array_sect, num_finish) == 1)
			cout << "Граф является планарным" << endl;
		else cout << "Граф не является планарным" << endl;

	}
	system("pause");
	return 0;
}

