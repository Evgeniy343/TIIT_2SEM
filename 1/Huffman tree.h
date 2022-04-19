#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<Windows.h>
#include<vector>
#include<list>
#include<iterator>
using namespace std;


struct Tree
{
	int n, t;
	char str[100];
	Tree(const char* str = "NULL", int n = 0, int t = 0)
	{
		strcpy_s(this->str, str);
		this->n = n;
		this->t = t;
	}
};

Tree reading_text_from_a_file(string path);
void Printf_trees(Tree* trees);
int Search(Tree* trees);
int numb_of_characters(Tree* trees,int j);
bool check_text(char *text);
void Print_tree(Tree& tree);