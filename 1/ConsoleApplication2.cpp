#include"Huffman tree.h"
#include<fstream>
#include<string>
#include<string.h>
#include<iostream>
#include<vector>
#include<conio.h>

using namespace std;

void main()
{

	setlocale(LC_ALL, "russian");
	Tree trees[10];
	menu1:int i = 0;
	fstream file("Trees.txt", fstream::in | fstream::out | fstream::app);
	while (file.read((char*)& trees[i], sizeof(Tree)))
	{
		i++;
	}
	file.close();
	i = 0;
menu:
	while (strcmp(trees[i].str,"NULL") != 0)
	{
		i++;
	}
	Tree tree;
	cout << "1.Создать дерево" << endl;
	cout << "2.Просмотреть деревья" << endl;
	cout << "3.Корректировать дерево" << endl;
	cout << "4.Выход" << endl;
	int choice;
	cin >> choice;
	system("cls");
	cin.ignore();
	switch (choice)
	{
	case 1:
	{
	P:cout << "Введите текст:";
		char text[100];
		gets_s(text);
		if (check_text(text) == true)
		{
			system("cls");
			string path = "Huffman.txt";
			tree = reading_text_from_a_file(path);
			trees[i] = tree;
			fstream file("Trees.txt", fstream::in | fstream::out | fstream::app);
			file.write((char*)& trees[i], sizeof(Tree));
			file.close();
			i++;
		}
		else
		{
			cout << "Некорректно введён текст!" << endl;
			goto P;
		}
		choice = 0;
		cout << "1.Создать ещё одно дерево" << endl;
		cout << "2.Вернуться в меню" << endl;
			cin >> choice;
			system("cls");
			cin.ignore();
		if (choice == 1)
		{
			goto P;
		}
		if (choice == 2)
		{
			goto menu;
		}
		break;
	}
	case 2:
	{
		i = 0;
		tr:Printf_trees(trees);
		cout << "Выберите дерево,которое хотите вывести" << endl;
		cin >> i;
		if (trees[i - 1].n == 0 || i > 100)
		{
			cout << "Дерево не найдено!" << endl;
			_getch();
			system("cls");
			goto tr;
		}
		system("cls");
		tree = trees[i - 1];
		cout << endl << endl;
		cout << i << "." << tree.str << "->";
		Print_tree(tree);
		cout << "1.Хотите вывести ещё одно дерево" << endl;
		cout << "2.Вернуться в меню" << endl;
		choice = 0;
		cin >> choice;
		system("cls");
		if (choice == 1)
		{
			goto tr;
		}
		if (choice == 2)
		{
			goto menu;
		}
	}
	case 3:
	{
	edit:
		Printf_trees(trees);
		cout << "Введите дерево,которое хотите изменить" << endl;
		int j = Search(trees);
		system("cls");
		if (j > 10)
		{
			cout << "Дерево не найдено" << endl;
			_getch();
			system("cls");
			goto edit;
		}
		cout << trees[j].str << endl;
		char text[100];
		N:
		cout << "Введите новый текст" << endl;
		strcpy_s(trees[j].str,gets_s(text));
		system("cls");
		if (check_text(text) == true)
		{
			goto D;
		}
		else
		{
			cout << "Некорректно введён текст!" << endl;
			_getch();
			system("cls");
			goto N;
		}
	D:
		trees[j].n = numb_of_characters(trees, j);
		trees[j].t = numb_of_characters(trees, j);
		fstream file("Trees.txt", fstream::in | fstream::out | fstream::trunc);
		for (int i = 0; i < 10; i++)
		{
			if (trees[i].str == "NULL")
			{
				break;
			}
			file.write((char*)& trees[i], sizeof(Tree));
		}
		file.close();
		cout << "1.Хотите исправить ещё одно дерево" << endl;
		cout << "2.Вернуться в меню" << endl;
		choice = 0;
		cin >> choice;
		system("cls");
		cin.ignore();
		if (choice == 1)
		{
			goto edit;
		}
		if (choice == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				trees[i].n = 0;
				trees[i].t = 0;
				strcpy_s(trees[i].str, "NULL");
			}
			goto menu1;
		}
	}
	}
	system("pause");
}




