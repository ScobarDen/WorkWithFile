#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

void DataToCMDfromFile(string wayfort);//Функция для вывода файла в консоль
void CheckTheHash(string wayfort);//Проверка хэша функции
void WriteToBin(string wayfort, string wayforb);//Запись данных в бинарный файл из текстового
void ReadFromBin(string wayforb);//Чтение данных из бинарного файла


int main()
{
	setlocale(LC_ALL, "ru");
	string wayfortext = "d://test.txt";//переменная пути к файлу
	string wayforbin = "d://testbinof.bin";

	int push = 0;
	while (push!=5)
	{
		cout << "Выберите функцию:" << endl << "1 - Функция для вывода файла в консоль" << endl
			<< "2 - Проверка хэша функции" << endl << "3 - Запись данных в бинарный файл из текстового"
			<< endl << "4 - Чтение данных из бинарного файла" << endl << "5 - Выход" << endl
			<< "Введите число: ";
		cin >> push;
		cout << "\n" << endl;
		switch (push)
		{
		case 1:
		{
			cout << "Укажите путь к файлу: ";
			cin >> wayfortext;
			DataToCMDfromFile(wayfortext);
			break;
		}
		case 2:
		{
			cout << "Укажите путь к файлу: ";
			cin >> wayfortext;
			CheckTheHash(wayfortext);
			break;
		}
		case 3:
		{
			cout << "Укажите путь к файлам (сначала текстовый, потом бинарный)" << endl;
			cin >> wayfortext;
			cin >> wayforbin;
			WriteToBin(wayfortext, wayforbin);
			break;
		}
		case 4:
		{
			cout << "Укажите путь к файлу: ";
			cin >> wayforbin;
			ReadFromBin(wayforbin);
			break;
		}
		default:
			break;
		}
	}
	

	return 0;
}

void DataToCMDfromFile(string wayfort)//Вывод файла в консоль
{
	ifstream fin(wayfort);
	if (!fin.is_open())//проверка того, удалось ли открыть файл
	{
		cout << "Неверный путь к файлу, либо такого файла не существует" << endl;

	}
	else
	{
		cout << "Файл открыт:" << endl;
		char ch;
		while (fin.get(ch))//посимвольный вывод данных
		{
			cout << ch;
		}
		cout << endl;
	}
	fin.close();
	cout << "\n" << endl;
}

void CheckTheHash(string wayfort)
{
	ifstream fin(wayfort);
	cout << "Проверка хэша:" << endl;
	string str, clearstr;
	vector<string> data;
	vector<string> cleardata;
	int i = 0;
	while (!fin.eof())
	{
		str = " ";
		getline(fin, str);
		//cout << str << endl;
		data.push_back(str);
		stringstream ss(data[i]);
		while (!ss.eof())
		{
			getline(ss, clearstr, ' ');
			if (clearstr.size() < 5)//для удаления строк с датой и временем
			{
				cleardata.push_back(clearstr);
			}
		}
		i++;
	}
	fin.close();

	vector<int> numbers;
	stringstream strtoi;
	int num;
	for (int i = 0; i < cleardata.size(); i++) {
		strtoi.clear();
		strtoi << cleardata[i];
		strtoi >> num;
		numbers.push_back(num);
	}

	for (int q = 0; q < (numbers.size() / 7); q++)
	{
		int sum = 0;
		int* psum = &sum;

		for (int k = 0; k < 6; k++)
		{
			*psum += numbers[k + 7 * q];
		}
		size_t hsum = hash<int>{}(sum);
		size_t hhash = hash<int>{}(numbers[6 + 7 * q]);
		if (hsum != hhash)//если я правильно понял, то хэш функция и есть сумма эти чисел
		{
			cout << "Строка с данными № " << q + 1 << " не соответствует функции хэша" << endl;
		}
		else
		{
			cout << "Строка с данными № " << q + 1 << " соответствует функции хэша" << endl;
		}
	}
	cout << "\n" << endl;
}

void WriteToBin(string wayfort, string wayforb)
{
	cout << "Чтение и запись бинарного файла:" << endl;
	ofstream testbinof(wayforb, ios::binary);
	ifstream finforbin;
	vector<string> vecofstr;//вектор строк для записи в файл
	if (!testbinof.is_open())//проверка того, удалось ли открыть файл
	{
		cout << "Неверный путь к бинарному файлу, либо такого файла не существует" << endl;

	}
	else
	{

		finforbin.open(wayfort);
		cout << "Данные из файла расположенного по пути <<" << wayfort <<">> записаны в бинарный файл <<" << wayforb << ">>." << endl;
		string binstrout;
		while (getline(finforbin, binstrout))//посимвольный вывод данных
		{
			vecofstr.push_back(binstrout);
		}
		finforbin.close();
		for (int i = 0; i < vecofstr.size(); i++)
		{
			testbinof.write((char*)&vecofstr[i], sizeof(vecofstr[i]));
		}
	}
	testbinof.close();
	cout << "\n" << endl;
}

void ReadFromBin(string wayforb)
{
	ifstream testbinin(wayforb, ios::binary);
	cout << "Результат чтения бинарного файла:" << endl;
	vector<string> vecofstr;
	vector<char> vecofchar;
	if (!testbinin.is_open())//проверка того, удалось ли открыть файл
	{
		cout << "Неверный путь к бинарному файлу, либо такого файла не существует" << endl;

	}
	else
	{
		string binstrin;
		char ch;
		while (testbinin.get(ch))//посимвольный вывод данных
		{
			vecofchar.push_back(ch);
		}
		for (int i = 0; i < vecofchar.size(); i++)
		{
			//testbinin >> vecofchar[i];
			testbinin.read((char*)&vecofchar[i], 1);
			cout << vecofchar[i];
		}
	}
	testbinin.close();
}
