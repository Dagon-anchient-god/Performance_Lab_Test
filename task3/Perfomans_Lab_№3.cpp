#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

/*
На вход в качестве аргументов программы поступают три пути к файлу (в приложении к заданию
находятся примеры этих файлов):
● values.json содержит результаты прохождения тестов с уникальными id
● tests.json содержит структуру для построения отчета на основе прошедших тестов
(вложенность может быть большей, чем в примере)
● report.json - сюда записывается результат.
Напишите программу, которая формирует файл report.json с заполненными полями value для
структуры tests.json на основании values.json.
Структура report.json такая же, как у tests.json, только заполнены поля “value”.
*/

int main()
{
    /*
    values.json Названия тестовых файлов для упрощения тестирования
    tests.json
    report.json
    */
    string file_patch; //Путь для фалов чтения
    string report_patch; //Путь для файла записи
    string line;
    string write_line;
    string id_number;
    string value_m;
    map<int, string> id_value; //Словарь, в котором будем хранить номер теста и его результат

    cin >> file_patch;

    //Создание словаря
    ifstream in_values(file_patch); //Открываем файл с результатами тестов
    if (in_values.is_open())
    {
        while (getline(in_values, line))//Проходим файл построчно
        {
            auto id = line.find("\"id\"");//Проверяем ести ли в строке "id"
            if (id != string::npos)
            {
                id += 6;//Если есть, передвигам значение параметра туда, где начинается число
                while (line[id] != ',')
                {
                    id_number += line[id];//Добавляем все символы до запятой
                    id++;
                }

            }
            else
            {
                auto value = line.find("\"value\"");//Проверяем ести ли в строке "value"
                if (value != string::npos)
                {
                    value += 10;//Если есть, передвигам значение параметра туда, где начинается значение
                    while (line[value] != '"')//Значение можно было определять по первому символу (f - failed;p - passed), но был выбран более универсальный подход (на случай появления новых значений)
                    {
                        value_m += line[value];
                        value++;
                    }
                    id_value[stoi(id_number)] = value_m; //Преобразуем id_number в число, и создаём запись в словаре
                    value_m = ""; //Очищаем переменные, чтобы новые значения не сливались со старыми
                    id_number = "";
                }
            }

        }
    }
    in_values.close();

    cin >> file_patch;

    ifstream in_tests(file_patch);//Открываем файл со структурой
    if (in_tests.is_open())
    {
        ofstream out_report;
        cin >> report_patch;
        out_report.open(report_patch);//Открываем файл для записи
        if (out_report.is_open())
        {
            while (getline(in_tests, line))
            {
                auto id = line.find("\"id\"");
                if (id != string::npos)
                {
                    id_number = "";//Необходимо перезаписывать переменную, чтобы убрать id, для которых нет значений в словаре
                    id += 6;
                    while (line[id] != ',')
                    {
                        id_number += line[id];//Запоминаем id теста
                        id++;
                    }
                }
                auto value = line.find("\"value\"");
                if (value != string::npos)
                {
                    write_line = line.substr(0, value + 10) + id_value[stoi(id_number)]+ line.substr(value + 10, line.size()-1);//Вставляем результаты теста между двух ковычек
                    out_report << write_line << "\n";
                }
                else
                    out_report << line << "\n";//Все остальные строки переносим в файл без изменений
            }
        }
        out_report.close();
    }
    in_tests.close();
}

