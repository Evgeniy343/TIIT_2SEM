#include "Huffman tree.h"
struct Word
{
	vector<char> word;
	vector<int> number;
	vector <vector<int>> binary;
	Word()
	{

	}

	Word(char word, int number)
	{
		this->word.push_back(word);
		this->number.push_back(number);
	}
};
list<int> Sort(list<int> tree1);
Word Write(char *weight1, int *size1, int s1, int count1);
void SORT(int s, vector<Word>& Words);



void Print_tree(Tree &tree)
{
	vector<Word> Words;
	string path = "Huffman.txt";
	int size[100] = { NULL }, s = 0;
	char check[100] = { NULL };
	int counter = 0, p = 0, k = 0, m = 0;
	char wrd[100] = { NULL };
	int g = 0;
P:for (int j = 0; j <= tree.n - 1; j++)
{
	if (p > 1)
	{
		j = g;
	}
	if (j > tree.n - 1)
	{
		break;
	}
	check[m] = tree.str[j];
	p = 0;
	k++;
	for (int i = 0; i <= tree.n - 1; i++)
	{
		if (tree.str[j] == tree.str[i])
		{
			counter++;
		}
	}
	for (int i = 0; i < k; i++)
	{
		if (check[m] == check[i])
		{
			p++;
		}
	}
	if (p > 1)
	{
		if (counter >= 2)
		{

			counter = 0;
			tree.t--;
			m++;
			g++;
			goto P;
		}
	}
	size[s] = counter;
	wrd[s] = tree.str[j];
	counter = 0;
	tree.t--;
	m++;
	s++;
	g++;
}
  int count = 0;
  for (int i = 0; i < s; i++)
  {
	  Words.push_back(Write(wrd, size, s, count));
	  count++;
  }


  SORT(s,Words);
  int counter_repeat = 0;
  list<int> tree1;
  for (int i = 0; i < s; i++)
  {
	  tree1.push_back(size[i]);
  }
  tree1 = Sort(tree1);
  for (int i = 0; i < s; i++)
  {
	  Words[i].binary.resize(s);
  }
  for (auto iter = tree1.cbegin(); iter != tree1.cend(); iter++)
  {
	  if (s == 1)
	  {
		  for (int i = 0; i <= Words[0].number.at(0); i++)
		  {
			  if (i == Words[0].number.at(0))
			  {
				  goto W;
			  }
			  Words[0].binary[0].push_back(1);
			  cout << Words[0].binary[0][i];
		  }
	  }
	  iter = tree1.cbegin();
	  int sum = 0;
	  auto iter1 = tree1.cbegin();
	  advance(iter1, 2);
	  while (iter != iter1)
	  {
		  sum += *iter;
		  for (int i = 0; i < s; i++)
		  {
			  if (Words[i].number.at(0) == *iter || Words[i + 1].number.at(0) == *iter)
			  {
				  if (counter_repeat == 1)//запись 1 во 2 элемент скрещивания
				  {
					  auto iter4 = Words[i + 1].number.cbegin();
					  Words[i + 1].number.erase(iter4);
					  Words[i + 1].number.push_back(sum);
					  if (Words[i + 1].word.size() - Words[i].word.size() >= 2)
					  {
						  for (int j = 0; j < Words[i + 1].word.size() - Words[i].word.size(); j++)
						  {
							  Words[i + 1].binary[j].push_back(1);
						  }
						  auto iterw1 = Words.cbegin();
						  Words.erase(iterw1);
						  s--;
						  goto M;
					  }
					  Words[i + 1].binary[0].push_back(1);
					  auto iterw = Words.cbegin();
					  Words.erase(iterw);
					  s--;
				  }
				  if (counter_repeat == 0)//запись 0 в 1 элемент скрещивания
				  {
					  if (Words[i].word.size() >= 2)
					  {
						  int w = 0;
						  auto iter5 = Words[i].word.cbegin();
						  for (int j = 0; j < Words[i].word.size(); j++)
						  {
							  auto iter6 = Words[i].binary[w].cbegin();
							  for (int p = 0; p < Words[i].binary[w].size(); p++)
							  {
								  Words[i + 1].binary[Words[i + 1].word.size()].push_back(*iter6);
								  iter6++;
							  }
							  Words[i + 1].binary[Words[i + 1].word.size()].push_back(0);
							  Words[i + 1].word.push_back(*iter5);
							  iter5++;
							  w++;
						  }
						  goto M;
					  }
					  Words[i + 1].binary[Words[i + 1].word.size()].push_back(0);
					  auto iter3 = Words[i].word.cbegin();
					  Words[i + 1].word.push_back(*iter3);
				  }
			  M:counter_repeat++;
			  }
			  break;
		  }
		  tree1.erase(iter);//удаление частоты вектора
		  iter = tree1.cbegin();
	  }
	  counter_repeat = 0;
	  tree1.emplace(iter, sum);
	  tree1 = Sort(tree1);
	  SORT(s,Words);
	  iter = tree1.cbegin();
  }
  for (int j = 0; j < m; j++)
  {
	  for (int i = 0; i < m; i++)
	  {
		  if (tree.str[j] == Words[0].word[i])
		  {
			  auto iter7 = Words[0].binary.at(i).cend() - 1;
			  for (iter7; iter7 != Words[0].binary.at(i).cbegin(); iter7--)
			  {
				  cout << *iter7;
			  }
			  if (iter7 == Words[0].binary.at(i).cbegin())
			  {
				  cout << *iter7;
			  }
			  break;
		  }
	  }
  }
W:
  cout << endl << endl;
}







list<int> Sort(list<int> tree1)
{
	tree1.sort();
	return tree1;
}




Word Write(char *weight1, int *size1, int s1, int count1)
{
	Word result(0, 0);
	for (int i = count1; i < s1; i++)
	{
		vector<char> wr1;
		wr1.push_back(weight1[i]);
		vector<int> size;
		size.push_back(size1[i]);
		auto iter1 = wr1.cbegin();
		auto iter2 = size.cbegin();
		result = Word(*iter1, *iter2);
		break;
	}
	return result;

}


void SORT(int s, vector<Word>& Words)//сортировка массива структур по векторам
{
	for (int j = 0; j < s; j++)
	{
		for (int i = 0; i < s; i++)
		{
			if (i + 1 == s)
			{
				break;
			}
			if (Words[i].number.at(0) > Words[i + 1].number.at(0))
			{
				Word tmp(0, 0);
				tmp = Words[i];
				Words[i] = Words[i + 1];
				Words[i + 1] = tmp;
			}
		}
	}
}


bool check_text(char *text)
{
	bool check;
	for (int i = 0; i < 100; i++)
	{
		if (text[i] == 0)
		{
			check = true;
			break;
		}
		if ((int)text[i] > 48 && (int)text[i] < 57 || (int)text[i] < 0)
		{
			check = false;
			break;
		}
	}
	if (check == true)
	{
		for (int i = 0; i < 100; i++)
		{
			if (text[i] == 0)
			{
				break;
			}
		}
		string path = "Huffman.txt";
		ofstream file1(path, ofstream::trunc);
		file1 << text;
		file1.close();
	}
	return check;
}


Tree reading_text_from_a_file(string path)
{
	int t = 0, n = 0;
	char weight[100] = { NULL };
	char ch;
	ifstream file(path, ifstream::app);
	while (file.get(ch))
	{
		weight[t] = ch;
		t++;
		n++;
	}
	file.close();
	Tree new_tree = Tree(weight, n, t);
	return new_tree;
}




void Printf_trees(Tree* trees)
{
	for (int i = 0; i < 10; i++)
	{
		int result = strcmp(trees[i].str, "NULL");
		if (result == 0)
		{
			break;
		}
		cout << i + 1 << ".";
		cout << trees[i].str << endl;
	}
}



int Search(Tree *trees)
{
	int i = 0;
	char st[100];
	gets_s(st);
	int result = 0;
	for (i = 0; i < 10; i++)
	{
		result = strcmp(trees[i].str, st);
			if (result == 0)
			{
				return i;
			}
	}
	return 11;
}


int numb_of_characters(Tree *trees, int j)
{
	string path = "Huffman.txt";
	ofstream file1(path, ofstream::trunc);
	file1 << trees[j].str;
	file1.close();
	int t = 0, n = 0;
	char weight[100] = { NULL };
	char ch;
	ifstream file(path, ifstream::app);
	while (file.get(ch))
	{
		weight[t] = ch;
		t++;
		n++;
	}
	file.close();
	return t;
}