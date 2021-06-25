#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <functional>
#include <string> 

using namespace std;

//Слияние
void merge(vector<long long>& arr, long long low, long long mid, long long high)
{
	vector <long long> temp(high + 1);
	long long i = low;
	long long j = mid + 1;
	long long count = 0;

	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
			temp[count++] = arr[i++];
		else
			temp[count++] = arr[j++];
	}

	while (i <= mid)
		temp[count++] = arr[i++];

	while (j <= high)
		temp[count++] = arr[j++];

	count--;

	while (count >= 0)
	{
		arr[count + low] = temp[count];
		count--;
	}
}

//Сортировка слиянием
void mergeSort(vector<long long>& arr, long long low, long long high)
{
	long long mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

//Запуск метода сортировки слиянием
void startMergeSort(vector<long long>& arr, long long size)
{
	mergeSort(arr, 0, size - 1);
}

void mergeThree(vector<long long>& arr, long long low, long long lmid, long long rmid, long long high)
{
	vector <long long> temp(high + 1);
	long long i = low;
	long long j = lmid + 1;
	long long k = rmid + 1;
	long long count = 0;

	while (i <= lmid && j <= rmid && k <= high)
	{
		if (arr[i] <= arr[j])
			if (arr[i] <= arr[k])
				temp[count++] = arr[i++];
			else
				temp[count++] = arr[k++];
		else
			if (arr[j] <= arr[k])
				temp[count++] = arr[j++];
			else
				temp[count++] = arr[k++];
	}

	while (i <= lmid && k <= high)
	{
		if (arr[i] <= arr[k])
			temp[count++] = arr[i++];
		else
			temp[count++] = arr[k++];
	}

	while (i <= lmid && j <= rmid)
	{
		if (arr[i] <= arr[j])
			temp[count++] = arr[i++];
		else
			temp[count++] = arr[j++];
	}

	while (k <= high && j <= rmid)
	{
		if (arr[k] <= arr[j])
			temp[count++] = arr[k++];
		else
			temp[count++] = arr[j++];
	}

	while (i <= lmid)
		temp[count++] = arr[i++];

	while (j <= rmid)
		temp[count++] = arr[j++];

	while (k <= high)
		temp[count++] = arr[k++];

	count--;

	while (count >= 0)
	{
		arr[count + low] = temp[count];
		count--;
	}
}

void mergeThreeSort(vector<long long>& arr, long long low, long long high)
{
	long long lmid, rmid;

	if (low < high)
	{
		lmid = low + (high - low) / 3;
		rmid = low + ((high - low) / 3 ) * 2;

		mergeThreeSort(arr, low, lmid);
		mergeThreeSort(arr, lmid + 1, rmid);
		mergeThreeSort(arr, rmid + 1, high);
		mergeThree(arr, low, lmid, rmid, high);
	}
}

void startMergeThreeSort(vector<long long>& arr, long long size)
{
	mergeThreeSort(arr, 0, size - 1);
}

//Генерация элементов с случайными значениями от 0 до 5
void gen5(vector<long long>& arr, long long size)
{
	for (long long i = 0; i < size; i++)
	{
		arr[i] = rand() % 6;
	}
}

//Генерация элементов с случайными значениями от 0 до 4000
void gen4000(vector<long long>& arr, long long size)
{
	for (long long i = 0; i < size; i++)
	{
		arr[i] = rand() % 4001;
	}
}

//Генерация элементов отсортированными с перестановками
void genSwap(vector<long long>& arr, long long size)
{
	//Кол-во свапов
	long long n = 2 + (size / 100) * 2;
	long long tempNumber;
	for (long long i = 0; i < size; i++)
	{
		arr[i] = i;
	}

	//свапаем n пар
	for (long long i = 0; i < n; i++)
	{
		long long r1 = rand() % size;
		long long r2 = rand() % size;
		tempNumber = arr[r2];
		arr[r2] = arr[r1];
		arr[r1] = tempNumber;
	}
}

//Генерация от 4100 до 0
void gen4100(vector<long long>& arr, long long size)
{
	long long tempNumber = 4099;
	for (long long i = 0; i < size; i++)
	{
		arr[i] = tempNumber;
		tempNumber--;
	}
}

bool isSorted(vector <long long>& arr, long long size)
{
	bool flag = true;
	for (long long i = 1; i < size; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			flag = false;
			break;
		}
	}
	return flag;
}


long long sortCheck(vector <long long>& arr, long long size, function <void(vector<long long>&, long long)> f)
{

	vector <long long> tempArr(size);
	//перед каждой сортировкой копировать
	//элементы эталонного массива в рабочий массив, который и сортировать.
	for (long long i = 0; i < size; i++)
	{
		tempArr[i] = arr[i];
	}

	//Запись изначального массива
	std::fstream fin;
	fin.open("input.txt", std::ios::out);
	if (fin.is_open())
	{
		fin << "Size = " << size << "\n";
		for (long long i = 0; i < size; i++)
		{
			fin << arr[i] << " ";
		}
	}
	fin.close();

	vector<long long> timeVal(102);//Массив замеров времени работы алгоритма

	for (long long i = 0; i < 102; i++)
	{
		//Обновление массива
		for (long long i = 0; i < size; i++)
		{
			tempArr[i] = arr[i];
		}

		//Подсчет времени работы алгоритма
		auto start_time = std::chrono::high_resolution_clock::now();
		f(tempArr, size);//Запускаем для копии массива заданного размера
		auto end_time = std::chrono::high_resolution_clock::now();

		auto time = end_time - start_time;
		timeVal[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
	}

	long long res = 0;

	//Проверка отсортированности массива
	bool flag = isSorted(tempArr, size);

	//Запись отсортированного массива
	std::fstream fout;
	fout.open("output.txt", std::ios::out);
	if (fout.is_open())
	{
		//Вывод если не отсортирован
		if (!flag)
		{
			cout << "Not sorted!" << "\n";
			fout << "Not sorted!" << "\n";
		}
		for (long long i = 0; i < size; i++)
		{
			fout << tempArr[i] << " ";
		}
	}
	fout.close();

	for (long long i = 2; i < 102; i++)
	{
		res += timeVal[i];
	}
	res /= 100;//Среднее время работы алгоритма


	return res;
}

//Статический массив функций

function<void(vector<long long>&, long long)> sort[2] = { startMergeSort, startMergeThreeSort };

/// <summary>
/// Запускает метод с нахождением среднего времени для данного массива 
/// для всех -ми сортивок и записывает их в строку
/// </summary>
/// <param name="arr"></param>
/// <param name="size"></param>
/// <returns></returns>
string checkAllSorts(vector <long long>& arr, long long size)
{
	string timeInfo = to_string(size) + ";";

	for (long long i = 0; i < 2; i++)
	{
		timeInfo += to_string(sortCheck(arr, size, sort[i])) + ";";
	}

	timeInfo += "\n";

	return timeInfo;
}

/// <summary>
/// Проверяет все возможные 10 размеров массивов
/// от 50 до 300 с шагом 50
/// и для 1100 до 4100 с шагом 1000
/// </summary>
/// <param name="arr"></param>
/// <param name="typeGen"></param>
/// <returns></returns>
string checkIntarvals(vector <long long>& arr, string typeGen)
{
	//Главная строка
	string timeInfoRes = typeGen + "\nСлиянием;Тройным Слиянием" + "\n";

	//Проверка массивов размера от 50 до 300 
	for (long long i = 50; i <= 300; i += 50)
	{
		timeInfoRes += checkAllSorts(arr, i);
	}

	//Проверка массивов размера от 50 до 300 
	for (long long i = 1100; i <= 4100; i += 1000)
	{
		timeInfoRes += checkAllSorts(arr, i);
	}

	timeInfoRes += checkAllSorts(arr, 256);
	timeInfoRes += checkAllSorts(arr, 243);

	return timeInfoRes;
}

/// <summary>
/// Записываем массив в файл
/// </summary>
/// <param name="arr"></param>
void arrayToTXT(vector <long long>& arr, long long size, string name)
{
	//Запись массива
	std::fstream fout;
	fout.open(name + ".txt", std::ios::out);
	if (fout.is_open())
	{
		fout << "Размер сгенерированного массива=" << size << "\n";
		for (long long i = 0; i < size; i++)
		{
			fout << to_string(arr[i]) << " ";
		}
	}
	fout.close();
}

/// <summary>
/// Метод с запуском тестирования сортировок
/// </summary>
void startTesting()
{
	//Запускаем все сортировки в холостую
	vector<long long> arr(100);
	for (long long i = 0; i < 2; i++)
	{
		sort[i](arr, 100);
	}

	//Создаем 4 основных массива, на которых будем тестировать сортировки
	vector<long long> gen1(4100);
	vector<long long> gen2(4100);
	vector<long long> gen3(4100);
	vector<long long> gen4(4100);

	gen5(gen1, 4100);//Случайные до 5
	gen4000(gen2, 4100);//Случайные до 4000
	genSwap(gen3, 4100);//Отсорт с перестановками
	gen4100(gen4, 4100);//Обратный порядок

	//Сохраненяю в txt все сгенерированные массивы
	//Нужно просто для визуальной ручной проверки, что именно генерирует
	arrayToTXT(gen1, 4100, "gen1");
	arrayToTXT(gen2, 4100, "gen2");
	arrayToTXT(gen3, 4100, "gen3");
	arrayToTXT(gen4, 4100, "gen4");

	//Создание и запись в таблицу данных по времени
	std::fstream fin;
	fin.open("timeInfo.csv", std::ios::out);
	if (fin.is_open())
	{
		//Записываем в строку (в таблицу) данные тестривания на разных массивах
		fin << checkIntarvals(gen1, "Случайные до 5");
		fin << "\n" + checkIntarvals(gen2, "Случайные до 4000");
		fin << "\n" + checkIntarvals(gen3, "Отсортированный с перестановками");
		fin << "\n" + checkIntarvals(gen4, "Обратный порядок");

	}
	fin.close();

}


int main()
{
	srand(time(NULL));
	//Запуск сортировки
	startTesting();
}
