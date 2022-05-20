
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <ctime>

using namespace std;

#define N 15					//число городов
#define CN V+2			//численность потомка

class pop;
static pop* population;
static pop* Childs;
static pop* Newpop;


static class In
{
public:
	double** D = new double* [N];
	In()
	{
		for (int i = 0; i < N; i++)
		{
			D[i] = new double[N];
		}
		
		ifstream in("input.txt");
		if (in.is_open())
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					in >> D[i][j];
				}
			}
		}

	}


	double output(int c1, int c2)
	{
		return D[c1 - 1][c2 - 1];
	}
	void Output()
	{
		
		
		for (int i = 0; i < N; i++)
		{
	
			for (int j = 0; j < N; j++)
			{
				cout << setw(5) << fixed << setprecision(2) << output(i + 1, j + 1) << "  ";
			}
			cout << endl;
		}
	}
}in;
class pop  
{
	int* X;
	int len;
public:
	pop()
	{
		X = new int[1];
		X[0] = 0;
		len = 1;
	}
	pop(const int& k)
	{
		X = new int[k];
		len = k;
	}

	void Output(const int& k)
	{
		if (k != 0)
		{
			cout << "" << setw(2);
			int i;
			for (i = 0; i < k - 1; i++)
			{
				cout << X[i] << " ";
			}
			cout << X[i];
		}
		else
		{
			cout << "-";
		}

	}
	int output(const int& k)
	{
		return X[k];
	}
	void input(const int& pos, const int& c)
	{
		X[pos] = c;
	}
	void insert(const int& c1, const int& size, const int& c2)//вставка в с1 с2
	{
		int pos = -1;
		for (int i = 0; i < size; i++)
		{
			if (X[i] == c1)
			{
			pos = i;
			}
		}
		pos++;
		int tam;
		tam = X[pos + 1];
		X[pos + 1] = X[pos];
		for (int i = pos + 1; i < size + 1; i++)
		{
			int tam2 = X[i + 1];
			X[i + 1] = tam;
			tam = tam2;
		}
		X[pos] = c2;
		len++;
	}
	pop& operator=(const pop& t) {
		if (this == &t) { return *this; }
		delete[]X;

		X = new int[(len = t.len) + 1];
		for (int i = 0; i < len; i++)
		{
			X[i] = t.X[i];
		}
		return *this;
	}
	friend int operator == (const pop& a, const pop& b)
	{
		int result = -1;
		if (a.len != b.len) { return 0; }
		else
		{
			for (int i = 0; i < a.len; i++)
			{
				if (a.X[i] != b.X[i])
				{
					return 0;
				}
			}
			return 1;
		}

	}
	void set_len(int len2) { len = len2; }
	int  get_len() { return len; }
	double Len()//пройденный путь

	{

		double res = 0;
		for (int i = 0; i < len - 1; i++)
		{
			int  c1, c2;
			c1 = X[i];
			c2 = X[i + 1];
			res = res + in.output(c1, c2);
		}
		return res;
	}
	int find(const int& c)
	{
		int pos = -1;
		for (int i = 0; i < len; i++)
		{
			if (X[i] == c)
			{
				pos = i;
				break;
			}
		}
		if (pos == -1)
		{
			cout << endl << "не существует" << endl;
		}
		return pos;
	}
	void change(const int& c1, const int& c2)		// гор1->гор2
	{
		int pos;
		pos = this->find(c1);
		this->input(pos, c2);
	}
	void Delete(const int& c)
	{
		int pos;
		pos = this->find(c);
		for (int i = pos; i < len - 1; i++)
		{
			this->input(i, X[i + 1]);
		}
		len--;
	}
	double  prisp() // приспособленность
	{
		double lenput = this->Len();
		double res;
		if (lenput == 0)
		{
			return 0;
		}
		else
		{
			res = 1 / lenput;// 1/длина пройденного пути
			return  res;
		}

	}
	double getprisp(double  sum) //получить присп
	{
		return this->prisp() / sum;
	}
	void zamena(const int& c1, const int& c2)	// заменить гор 1 с гор 2
	{
		int pos1, pos2;
		pos1 = this->find(c1);
		pos2 = this->find(c2);
		this->input(pos1, c2);
		this->input(pos2, c1);

	}

};

void Best(int V)
{
	
	pop res(N + 1);
	double len, x = 0;
	len = 99999;
	int k = -1;
	for (int i = 0; i < V; i++)
	{
		if (len > population[i].Len())
		{
			k = i;
			len = population[i].Len();
			x = population[i].prisp();
			res = population[i];
		}

	}
	cout << endl;
	cout<< "лучшая особь  " << k << "=";
	res.Output(N + 1);
	cout << "\t\t" << len << "\t\t\t" << x << endl;
}


void Initpop(int a1,int V)
{

	srand(time(NULL));
	cout << endl;
	cout << "начальная популяция " << endl << endl;
	cout << "\t\t\t\t\t Длинна \t\t приспособленность " << endl;
	for (int i = 0; i < V; i++)
	{
		
			if (a1 == 1)
			{		
			pop X(N);			
			for (int i = 0; i < N; i++)
			{
				X.input(i, i + 1);// 0-15
			}

			pop S(N + 1);	
			int gen;
			for (int i = 0; i < N; i++)
			{
				gen = rand() % (N - i);
				S.input(i, X.output(gen));//вставляет случайный 
				
				X.input(gen, X.output(N - i - 1));// вместо выбранного вставляет предыдущий чтобы исключить повтор
				for (int i = 0; i < N; i++)
				cout << X.output(i);
				cout << endl;
			}
			S.input(N, S.output(0));//приход в конец
			population[i] = S;

			cout << i << " =";
			population[i].Output(N + 1);
			cout << "\t\t\t" << setprecision(4) << population[i].Len() << "\t\t\t"  << setprecision(4) << population[i].prisp() << "\n";

			

			}
		
			if (a1 == 2)
			{

			pop X(N);
			pop S(N + 1);					
			for (int i = 0; i < N; i++)
			{
				X.input(i, i + 1);
			}
			int size = N;
			int k = 1;
			int xi = rand() % size;
			S.input(k - 1, X.output(xi));
			X.input(xi, X.output(size - 1));
			size--;
			while (size != 0)
			{
				double min = 99;
				for (int j = 0; j < size; j++)
				{
					if (in.output(S.output(k - 1), X.output(j)) < min)
					{
						xi = j;
						min = in.output(S.output(k - 1), X.output(j));
					}
				}

				k++;
				S.input(k - 1, X.output(xi));
				X.input(xi, X.output(size - 1));
				size--;

			}
			S.input(N, S.output(0));
			population[i] = S;
			cout << i << "=";
			population[i].Output(N + 1);
			cout << "\t\t\t" << setprecision(4) << population[i].Len() << "\t\t\t" << setprecision(4) << population[i].prisp() << "\n";

			
			}
		
			else if((a1!=1) && (a1!=2))
			{
				cout << endl;
				cout  << "повторите ввод" << endl;
			cin >> a1;
			i = -1;
			}
		
	}
	Best(V);
}


void vospr(int a2,int V)
{

	srand(time(NULL));
	cout << "Потомки ";

	for (int num = 0; num < (CN); num++)
	{
		//случайный выбор родителей 
		int rod1, rod2;
		rod1 = rand() % V;
		rod2 = rand() % V;

		while (rod1 == rod2)
		{
			rod2 = rand() % V;
		}

		pop father, mother;
		father = population[rod1];
		mother = population[rod2];

		pop child(N+1);
			if(a2==1)
		{
			
		
			int pos = rand() % (N - 1) + 1; 
			// Частичного отображения - PMX
			pop X(pos);			
			for (int i = 0; i < pos; i++)
			{
				X.input(i, mother.output(i));
			}
			//удаляет повторы
			for (int i = 0; i < pos; i++)
			{
				int t;
				t = mother.find(father.output(i));
				if (t < pos)
				{
					
					X.Delete(father.output(i));
				}

			}
		
			int k = 0;
			//мать берет гены отца
			for (int i = 0; i < pos; i++)
			{
				int t;
				t = mother.find(father.output(i));
				if (t >= pos)
				{

					mother.change(father.output(i), X.output(k));
					k++;
				}

			}
			//Операторы кроссовера для порядкового кодирования (одноточечного)
			for (int i = 0; i < N; i++)
			{
				if (i >= pos)
				{
					
					child.input(i, mother.output(i));
				}
				else
				{
					child.input(i, father.output(i));
				}

			}
			child.input(N, child.output(0));
			Childs[num] = child;
			

	
		}
		
			if(a2==2)
		{
			
		
			int pos1 = rand() % (N - 1) + 1;
			int pos2 = rand() % (N - 1) + 1;
			while (pos1 == pos2)
			{
				pos2 = rand() % (N - 1) + 1;
			}
			if (pos1 > pos2)
			{
				swap(pos1, pos2);
			}			
			pop X(pos2 - pos1);
			for (int i = pos1; i < pos2; i++)
			{
				X.input(i - pos1, mother.output(i));

			}

			
			for (int i = pos1; i < pos2; i++)
			{
				int t;
				t = mother.find(father.output(i));
				if (t < pos2 && t >= pos1)
				{
					
					X.Delete(father.output(i));
				}

			}
			
			int k = 0;
			for (int i = pos1; i < pos2; i++)
			{
				int t;
				t = mother.find(father.output(i));
				if (t >= pos2 || t < pos1)
				{

					mother.change(father.output(i), X.output(k));
					k++;
				}

			}

			
			for (int i = 0; i < N; i++)
			{
				if (i < pos2 && i >= pos1)
				{
					child.input(i, father.output(i));
				}
				else
				{
					child.input(i, mother.output(i));
				}

			}
			child.input(N, child.output(0));
			Childs[num] = child;
			

	

		}
		
			else if ((a2 != 1) && (a2 != 2))
		{
				cout << endl;
				cout << "повторите ввод" << endl;
			cin >> a2;
			num = -1;
		}
		

	}

}


void Mutation(int a3,double pm,int V)
{
	
	srand(time(NULL));
	
	cout << "\t\t\t\t\t Длинна \t\t приспособленность " << endl;
	for (int i = 0; i < CN; i++)
	{
	
			if(a3==1)//генная (меняет местами в детях два гена)
		{
			double t = double(rand() % 101) / 100;
			
			if (t < pm)
			{
				int pos1 = rand() % N;
				int pos2 = rand() % N;
				while (pos1 == pos2)
				{
					pos2 = rand() % (N - 1) + 1;
				}

				int c1 = Childs[i].output(pos1);
				int  c2 = Childs[i].output(pos2);
				Childs[i].zamena(c1, c2);

				if (pos1 == 0 || pos2 == 0) 
				{
					Childs[i].input(N, Childs[i].output(0));
				}
			}
		
		}

		
		if(a3==2)//Макромутация (сальтация)
		{
			double t = double(rand() % 100) / 100;
			
			if (t < pm)
			{
				 int pos1 = rand() % N;
				int pos2 = rand() % N;
				while (pos1 == pos2)
				{
					pos2 = rand() % (N - 1) + 1;
				}
				if (pos1 > pos2)
				{
					swap(pos1, pos2);
				}

				int c1 = Childs[i].output(pos1);
				int c2 = Childs[i].output(pos2);
				Childs[i].Delete(c1);
				Childs[i].insert(c2, N, c1);
				if (pos1 == 0)
				{
					Childs[i].input(N, Childs[i].output(0));
				}

			}


		}
		
		else if ((a3 != 1) && (a3 != 2))
		{
			cout << endl;
			cout << "повторите ввод" << endl;
			cout << "Мутация: 1-Генная мутация 2-Макромутация ";
			cin >> a3;
			i = 0;
		}
	
		
		cout << endl  << i << "=";
		Childs[i].Output(N + 1);
		cout << "\t\t\t" << Childs[i].Len() << "\t\t\t" << Childs[i].prisp();
	}


}

 
void Select(int a4,int V,int B,double G)
{
	
	srand(time(NULL));
	Newpop = new pop[V];
	
		if(a4==1)//пропорциональная
	{
		double  sumprob = 0.0;		// присп род
		double sumver = 0.0;	
		double* sumprisp = new double[CN];	// приспособленности
		double* popsum= new double[V];//популяционная сумма вер
	
		for (int i = 0; i < V; i++)
		{
			sumprob += population[i].prisp();
		}
		double  sumpristchild = 0.0;		// приспособленность потомков
		
		for (int i = 0; i < CN; i++)
		{
			sumpristchild += Childs[i].prisp();
		}
		
		for (int i = 0; i < V; i++)
		{
			pop select(N + 1);

			if (i >= (G * V))			// из всех,т е вместе с родителями
			{
				double p = ((double)rand()) / RAND_MAX; //(0/1)
				for (int i = 0; i < V; i++)
				{
					sumver += population[i].getprisp(sumprob);	// Сумма значения функции приспособленности для 0 до i особи
					popsum[i] = sumver;
					if (p < popsum[i])
					{
						select = population[i];
						sumver = 0;
						break;
					}
				}

			}
			else // только потомки
			{
				double p = ((double)rand()) / RAND_MAX;
				for (int i = 0; i < CN; i++)
				{
					sumver += Childs[i].getprisp(sumpristchild);	
					sumprisp[i] = sumver;

					if (p < sumprisp[i])
					{
						select = Childs[i];
						sumver = 0;
						break;
					}
				}
			}

			Newpop[i] = select;


		}
		delete[]sumprisp;
		delete[]popsum;
		sumprisp = NULL;
		popsum = NULL;
		
	}
	
		if(a4==2)//б-турнир
	{
		
		 
		int i=0;
		while(i<V)
		{
			pop* tur = new pop[B];

			// турнир 
			for (int j = 0; j < B; j++)
			{
				int randm = rand() % CN;
				tur[j] = Childs[randm];
			}

			// лучшая
			pop best(N + 1);
			best = tur[0];
			
			for (int j = 1; j < B; j++)
			{
				if (best.Len() > tur[j].Len())
				{
					best = tur[j];
				}
				
			}

			Newpop[i] = best;
			i++;
		}
		
	}
	
		else if ((a4 != 1) && (a4 != 2))
	{
			cout << endl;
			cout << "повторните ввод" << endl;
		cout << "селекция: 1-Пропорциональная 2-B-турнир";
		cin >> a4;
		Select(a4,V,B,G);
	}
	
	cout << endl << endl << "новая популяция";
	cout << "\t\t\t\t Длинна \t\t\t приспособленность " << endl;
	for (int i = 0; i < V; i++)
	{
		population[i] = Newpop[i];
		
		cout << endl;
		cout << i << "=";
		population[i].Output(N + 1);
		cout << "\t\t\t" << population[i].Len() << "\t\t\t" << population[i].prisp();
	}
	cout << endl;
	Best(V);

}


int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	int I, V;
	 double  pm = 0.15;	
	int a1, a2, a3, a4;
	
	cout << "вероятность мутации-" << pm << endl;
	cout << "численность популяции-";
//	cin >> V;
	V = 10;
	cout << V << endl;
	cout << "количество итераций-";
//	cin >> I;
	I = 5;
	cout << I << endl;
	cout << "формирование начальной популяции: 1-случайный с контролем ограничений 2-жадный алгоритм (метод ближайшего соседа)" << endl;
	//cin >> a1;
	a1 = 1;
	cout << a1 << endl;
	cout << "кроссовер: 1-одноточечный кроссовер с выбором случайных родителей 2-двухточечный" << endl;
	//cin >> a2;
	a2 = 2;
	cout << a2 << endl;
	cout << "мутация: 1-генная 2-макромутация" << endl;
	//cin >> a3;
	a3 = 1;
	cout << a3 << endl;
	cout << "селекция: 1-пропорциональная 2-B-турнир" << endl;
	//cin >> a4;
	a4 = 1;
	cout << a4 << endl;
	double G;
	cout << endl;
	cout << "введите коэф для переключения поколений" << endl;
	//cin >> G;
	G = 0.7;
	cout << G << endl;
	int B;
	if (a4 == 2)
	{
		cout << "введите B " << endl;
		//cin >> B;
		B = 5;
		cout << B << endl;

	}
	else B = 0;
	cout << endl;
	cout << "число городов-" << N << endl;
	in.Output();
	population = new pop[V];
	Childs = new pop[CN];	
	Initpop(a1,V);
	for(int i=0;i<I;i++)
	{
		
		
		cout << " шаг " << (i + 1) << endl;
		vospr(a2,V);
		Mutation(a3,pm,V);
		Select(a4,V,B,G);

		
		cout << endl;
	}
	
}