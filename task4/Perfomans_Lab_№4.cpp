#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

/*
Дан массив целых чисел nums.
Напишите программу, выводящую минимальное количество ходов, требуемых для приведения всех
элементов массива к одному числу.
За один ход можно уменьшить или увеличить число массива на 1.
Имеется ограничение по максимальному количеству ходов – 20.
Необходимо вывести минимальное количество ходов. В случае, если за 20 ходов это сделать
невозможно, необходимо вывести соответствующее сообщение.
*/

using namespace std;
int main()
{
    //test.TXT Имя файла для быстрой проверки
    setlocale(LC_ALL, ""); //Необходимо для выведения кирилицы в консоль
    int temp;
    int moves = 20;
    int flag = 1;
    int med;
    vector<int> numbers;
    string file_adress;
    cin >> file_adress;
    ifstream in(file_adress);

    if (in.is_open())
    {
        while (in >> temp)
            numbers.push_back(temp); //Берём элементы массива
    }
    in.close();

    sort(numbers.begin(), numbers.end());//Сортируем массив
    //Ищем медиану.Поскольку медиана делит упорядоченный массив на две равный части имено к ней за меньшее кол-во ходов можно привести все элементы массива
    if (numbers.size() % 2 == 1)
    {
        med = numbers[(int)(numbers.size() / 2)];
    }
    else
    {
        med = (int)(numbers[(int)(numbers.size() / 2)] + numbers[(int)(numbers.size() / 2) - 1]) / 2;
        flag = 0;//Флаг используется, поскольку вслучае чётного кол-во элементов мендиана может быть дробной, и в одних случаях быстрее приводить меньшему, в других к большему значению
    }
    if (flag == 1)
    {
        for (auto i : numbers)
        {
            moves -= abs(med - i);//Считаем кол-во оставшихся действий 
            if (moves < 0) //Их стало меньше 0, прерываем
                break;
        }
    }
    else
    {
        int second_mov = 20;
        for (auto i : numbers)
        {
            second_mov -= abs(med - i);
            if (second_mov < 0)
                break;
        }

        if (med >= 0)// Проверка для отрицателных чисел, чтобы взять именно большее значние
            med++;
        else
            med--;

        for (auto i : numbers)
        {
            moves -= abs(med - i);
            if (moves < 0)
                break;
        }

        moves = max(moves, second_mov);//Берём иммено большее значение, поскольку считаем оставшиеся действия
    }

    if (moves >= 0)
        cout << 20 - moves;
    else
        cout << "20 ходов недостаточно для приведения всех элементов массива к одному числу";

}

