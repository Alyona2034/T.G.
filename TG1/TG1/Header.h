#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int inf = 100000;

struct Edge
{
	int src, dest, weight;
};

class Graph
{
public:
	vector<Edge> array{};
	int size;
	ifstream File;
	string path;
	char key;

	void getPath()
	{
		cout << "Enter the path to the file: ";
		cin >> path;
		cout << "Enter the key: ";
		cin >> key;
	}

	vector<Edge> getGraph()
	{

		File.open(path);

		if (key == '-h')
		{
			cout << "СПРАВКА" << endl << "Работу выполнили: Кожихова А.А., Ампилова А.А." << endl <<
				"Группа: М3О-219Бк-21" << endl << 
				"Ключи: -h - справка, -e - список ребер, -m - матрица смежности, -l - списки смежности" << endl;
		}
		else if (key == '-e')
		{
			int i = 0;
			while (!File.eof())
			{
				File >> array[i].src;
				File >> array[i].dest;
				File >> array[i].weight;
				i++;
			}
			size = i - 1;
			return array;
		}
		else if (key == '-m')
		{

		}
		else if (key == '-m')
		{

		}
		else
		{
			cout << "Ошибка! Неверный ключ" << endl;
			return;
		}

	}

	int Weight(int VertexI, int VertexJ)
	{
		int vi = VertexI;
		int vj = VertexJ;
		int i = 0;
		int j = 0;
		vector <Edge> array = getGraph();

		while (array[i].src != vi - 1)
		{
			i++;
		}
		j = i;
		while (array[i].dest != vj - 1)
		{
			i++;
		}
		cout << "Вес ребра = " << array[i].weight << endl;
	}

	void listOfEdges()
	{
		vector <Edge> array = getGraph();
		for (int i = 0; i < size; i++)
		{
			cout << "№" << i << ": ";
			cout << array[i].src << "  ";
			cout << array[i].dest << "  ";
			cout << array[i].weight << endl;
		}
	}

	void listOfEdges(int Vertex)
	{
		vector <Edge> array = getGraph();
		int v = Vertex;
		int i = 0;

		while (array[i].src != v - 1)
		{
			i++;
		}
		cout << "Список ребер, инцидентных данной вершине/исходящих из нее:" << endl;
		while (array[i].src == v - 1)
		{
			cout << array[i].src << " - " << array[i].dest << "   ";
		}
		cout << endl;
	}
	
	void adjacencyList(int Vertex)
	{
		vector <Edge> array = getGraph();
		int v = Vertex;
		int i = 0;
	
		while (array[i].src != v - 1)
		{
			i++;
		}
		cout << "Список вершин, смежных данной:" << endl;
		while (array[i].src == v - 1)
		{
			cout << array[i].dest << "  ";
		}
		cout << endl;
	}

	bool isEdge(int VertexI, int VertexJ)
	{
		int vi = VertexI;
		int vj = VertexJ;
		vector <Edge> array = getGraph();
		int i = 0;
		while (array[i].src != vi - 1)
		{
			i++;
		}
		while ((array[i].dest != vj - 1) and (array[i].src == vi - 1))
		{
			i++;
		}
		if (array[i].dest == vj - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int **adjacencyMatrix()
	{
		vector <Edge> array = getGraph();
		int value = 0; // вес ребра
		int **matr = new int*[size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			matr[i] = new int[size - 1];
		}

	// Инициализация матрицы связей
		for (int i = 0; i < size - 1; i++)
		{
			matr[i][i] = inf; // вершины не имеют путь к самим себе
			for (int j = 0; j < size - 1; j++)
			{
				if (matr[i][j] != inf) // если путь может существовать, то вводим его значение
				{
					if (isEdge(i, j))
					{
						while (array[i].src != i)
						{
							i++;
						}
						while (array[i].dest != j)
						{
							i++;
						}
						value = array[i].weight;
					}
					else
					{
						value = 0;
					}
					if (value != 0) // если вес ребра не равен 0, то данное ребро принимает
						// введенное значение, и соответствующее ему значение, находящееся
						// симметрично ему относительно главной диагонали, принимает значение
						// либо 0, либо бесконечность, в зависимости от соотношения индексов
					{
						matr[i][j] = value;
						if (j < i)
						{
							matr[j][i] = 0;
						}
						else
						{
							matr[j][i] = inf;
						}
					}
					else // если введенный вес = 0, то текущий вес тоже становится = 0
					{
						matr[i][j] = value;
					}
				}
				else // если путь не существует, то ставим 0
				{
					matr[i][j] = 0;
				}
			}
		}
		cout << endl;
		return matr;
	}

	bool isDirected()
	{
		int** matr = new int* [size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			matr[i] = new int[size - 1];
		}
		matr = adjacencyMatrix();
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (matr[i][j] != matr[j][i])
				{
					return false;
				}
			}
		}
		return true;
	}
};

