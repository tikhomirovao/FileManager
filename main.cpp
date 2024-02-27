#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdio.h> //стандартная библиотека ввода-вывода языка С, в том числе и для работы с файлами
#include <io.h> //библиотека ввода-вывода, для работы с файлами используется в плане "в плане доступа"
#include <stdlib.h>
#include <direct.h> //библиотека для работы с директориями(каталог(папка))
#include <time.h>
#include <string>



using namespace std;

//прототипы функций для работы с файлами
//Создание файла
void Create_File();
//Поиск файла
void Find_File();
//Переименование файла
void Rename_File();
//Перемещение файла
void Move_File();
//Копирование файла
void Copy_File(const char*, const char*); //откуда и куда копировапть
//Удаление файла
void Remove_File(const char*);
//прототипы функций для работы с директориями
//Создание директории
void Create_Directory(const char*);
//Переименование директории
void Rename_Directory();
//Перемещение директории
void Move_Directory();
//Копирование директории
void Copy_Directory(const char*, const char*); //откуда и куда копировать
//Удаление директории
void Remove_Directory(const char*);
//Просмотр содержимого директории
void Show_Directory(string = ""); //по умолчанию показ содержимого текущего каталога

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //Создание файла
    Create_File();
    //Поиск файла
    Find_File();
    //Переименование файла
    Rename_File();
    // перемещение файла
    Move_File();
    //Копирование файла
    char Source[MAX_PATH]{};
    char Destination[MAX_PATH]{};
    cout << "Введите имя исходного файла,  с указанием пути к нему: ";
    gets_s(Source);
    cout << "Введите имя файла назначения, с указанием пути к нему: ";
    gets_s(Destination);
    Copy_File(Source, Destination);
    //Удаление файла
     char Name[MAX_PATH]{};
     cout << "Введите имя файла с указанием пути: ";
     gets_s(Name);
     Remove_File(Name);
     //Создание директории
     //char Name[MAX_PATH]{};
     //cout << "Введите имя директории с указанием пути к ней: ";
     //gets_s(Name);
     //Create_Directory(Name);
     //Переименование директории
     //Rename_Directory();   
     //Перемещение директории
    // Move_Directory();
     //Удаление директории
     /*char Name[MAX_PATH]{};
     cout << "Введите имя директории с указанием пути к ней: ";
     gets_s(Name);
     Remove_Directory(Name);*/
     //Просмотр содержимого директории
     /*string Name;
     cout << "Введите имя директории с указанием пути к ней: ";
     getline(cin,Name);
     Show_Directory(Name);*/

     //Копирование директории
     /*char Source[MAX_PATH]{};
     char Destination[MAX_PATH]{};
     cout << "Введите имя исходной директории,   с указанием пути к ней: ";
     gets_s(Source);
     cout << "Введите имя директории назначения, с указанием пути к ней: ";
     gets_s(Destination);
     Copy_Directory(Source, Destination);*/

}
//Создание файла
void Create_File()
{
    //можно добавить запрос какой файл создавать: текстовый или двоичный
    //запрос имени файла с учетом пути к нему(полного имени файла)
    char Name[MAX_PATH]{}; //_MAX_PATH
    int i = 2;
    //string Name; //объект класса string
    cout << "Введите имя файла, с указанием пути к нему: ";
    gets_s(Name); //cin.getline(Name, MAX_PATH);
    //getline(cin, Name); //для string    

    //создаем указатель на объект структуры FILE 
    FILE* File = nullptr;

    //проверка существования файла с таким же именем
    //попытка открытия файла на чтение, fopen_s возвращает 0 если удалось открыть файл 
    //и код ошибки если не удалось
    if (!fopen_s(&File, Name, "rb")) //r - чтение, w - запись, a - дозапись, b - двоичный режим(открытие двоичного файла) 
        //if(!fopen_s(&File,Name.c_str(),"rb") //для string
    {
        cout << "Файл с таким именем уже существует" << endl;
        if (fclose(File) == EOF)perror("Ошибка зарытия файла"); //закрытие файла 
        char drive[3];//хранит символ диска
        char dir[MAX_PATH]{};//хранит каталог и подкаталоги
        char fname[MAX_PATH]{};//хранит имя 
        char ext[MAX_PATH]{};//хранит расширение
        char FullName[MAX_PATH]{};//новое полнео имя
        //функция расщепляет полный путь на диск,каталог,имя, расширение
        _splitpath_s(Name, drive, dir, fname, ext);
        char Index[4]{};
        Index[0] = '(';
        Index[1] = i + 48;
        Index[2] = ')';
        Index[3] = '\0';
        strcat_s(FullName, drive);
        strcat_s(FullName, dir);
        strcat_s(FullName, fname);
        strcat_s(FullName, Index);
        strcat_s(FullName, ext);
        cout << FullName << endl;
        if (Name == FullName)
            fopen_s(&File, FullName, "w"); //открывает текстовый файл на запись
        i++;
    }

    //создаем файл
    fopen_s(&File, Name, "w"); //открывает текстовый файл на запись
    //fopen_s(&File, Name, "wb"); //открывает двоичный файл на запись
    //fopen_s(&File, Name.c_str(), "w"); //для string
    if (!File)
    {
        perror("Ошибка создания файла");
        return;
    }
    //если нужен не пустой файл, добавляем в него:
    //fputc(' ', File); //запись одного символа
    //fputs("Привет, Мир!\n", File);
    if (fclose(File) == EOF)perror("Ошибка зарытия файла"); //закрытие файла
    else cout << "Файл успешно создан!" << endl;

}
//Поиск файла
void Find_File()
{
    //запрос пути к директории для поиска файлов
    char Path[MAX_PATH]{};
    cout << "Введите путь к директории для поиска файлов: " << endl;
    gets_s(Path);
    //если не ввели путь, то ищем в текущей директории(директория из которой запущена наша программма)
    if (!strlen(Path))GetCurrentDirectoryA(MAX_PATH, Path);
    //запрос маску для поиска файла
    char Mask[MAX_PATH]{};
    cout << "Введите маску для поиска файлов(например . или *.txt):" << endl;
    gets_s(Mask);
    if (!strlen(Mask))strcpy_s(Mask, ".");
    //соединяем путь и маску
    char FullPath[MAX_PATH]{}; //D:\PD322 \ *.txt
    strcpy_s(FullPath, Path);
    strcat_s(FullPath, "\\");
    strcat_s(FullPath, Mask);
    //string FP = Path; FP += "\\"; FP += Mask; //для string
    //динамический объект структуры для хранения данных о файлах
    _finddata_t* InfoFiles = new _finddata_t{};
    //начинаем поиск
    intptr_t Done = _findfirst(FullPath, InfoFiles);
    //если Done == -1 значит ничего не найдено
    intptr_t MayWeWork = Done; //для проверки закончились ли найденые файла
    int CountFiles = 0; //кол-во найденных файлов
    while (MayWeWork != EOF)   //while(MayWeWork!=-1)
    {
        //пропускаем все найденные директории
        if (!(InfoFiles->attrib & _A_SUBDIR)) //поиск только файлов
            //if((InfoFiles->attrib & _A_SUBDIR)&&strcmp(InfoFiles->name,".")&&strcmp(InfoFiles->name, "..")) //поиск только директорий
        {
            CountFiles++;
            //Выводи имя найденного файла
            cout << InfoFiles->name << endl;
            //можно вывести данные о файле из структуры InfoFiles
        }
        MayWeWork = _findnext(Done, InfoFiles);
    }
    //выводим кол-во найденных файлов
    cout << "Было найдено " << CountFiles << " файл(а/ов) в директории " << Path << " по маске " << Mask << endl;
    _findclose(Done); //завершение поиска
    delete InfoFiles; //освобождаем память
}
//Переименование файла
void Rename_File()
{
    //текущее и новое имя файла
    char OldName[MAX_PATH]{};
    char NewName[MAX_PATH]{};
    cout << "Введите старое имя файла, с указанием пути к нему: ";
    gets_s(OldName);
    cout << "Введите новое  имя файла: ";
    gets_s(NewName);
    char drive[3];//хранит символ диска
    char dir[MAX_PATH]{};//хранит каталог и подкаталоги
    char fname[MAX_PATH]{};//хранит имя 
    char ext[MAX_PATH]{};//хранит расширение
    char FullName[MAX_PATH]{};//новое полнео имя
    //функция расщепляет полный путь на диск,каталог,имя, расширение
    _splitpath_s(OldName, drive, dir, fname, ext);
    //функция создает строку составного пути из отдельных компонентов
    _makepath_s(FullName, drive, dir, NewName, ext);

    //переименование и проверка
    if (rename(OldName, FullName)) //возвращает 0 если удалось и код ошибки если не удалось
    {
        perror("Ошибка переименования файла! Проверьте имя и закрыт ли файл");
        return;
    }
    else cout << "Файл успешно переименован!" << endl;

}
//Перемещение файла
void Move_File()
{
    //текущее и новое имя файла
    char Source[MAX_PATH]{};
    char Destination[MAX_PATH]{};
    cout << "Введите имя и полный путь файла: ";
    gets_s(Source);
    cout << "Введите новый  путь к файлу(без указания имени): ";
    gets_s(Destination);
    char drive[3];//хранит символ диска
    char dir[MAX_PATH]{};//хранит каталог и подкаталоги
    char fname[MAX_PATH]{};//хранит имя 
    char ext[MAX_PATH]{};//хранит расширение

    //функция расщепляет полный путь на диск,каталог,имя, расширение
    _splitpath_s(Source, drive, dir, fname, ext);
    //к указанному пути добавляем "\"
    strcat_s(Destination, "\\");
    //добавляем извлеченное имя
    strcat_s(Destination, fname);
    //добавляем расширение
    strcat_s(Destination, ext);

    if (Source[0] = Destination[0])
    {
        if (rename(Source, Destination)) //возвращает 0 если удалось и код ошибки если нет
        {
            perror("Ошибка перемещения файла!");
            return;
        }
        else cout << "Файл успешно перемещен!" << endl;
        return;
    }
    Copy_Directory(Source, Destination);
    Remove_Directory(Source); //Remove_Directory(); должна удалять не пустые папки

}
//Копирование файла
void Copy_File(const char* Source, const char* Destination) //что копировать и куда
{
    //Указатели на структуру FILE
    FILE* Src = nullptr, * Dest = nullptr;
    //открываем файл в бинарном(двоичном) режиме на чтение
    if (fopen_s(&Src, Source, "rb"))
    {
        perror("Ошибка открытия копируемого файла!");
        return;
    }
    //получение дескриптор файла
    int hSrc = _fileno(Src);
    //определяем размер файла
    long long Length = _filelengthi64(hSrc);
    //long long Size = 0;
    size_t Size = 0;
    if (Length >= 104857600)Size = Size = (Length / 100) + 1; //Буфер как 1% от размера файла +1 Байт
    else Size = Length; //Буфер для копирования файлов, размером меньше 100Мб
    char* Data = new char[Size] {}; //выделение памяти под буфер
    //проверка выдеделения памяи
    if (!Data)
    {
        cout << "Ошибка выделения памяти, при создании буфера для копирования файла!" << endl;
        fclose(Src);
        return;
    }
    //открываем(создаем) файл в месте назначения в бинарном(двоичном) режиме на запись
    if (fopen_s(&Dest, Destination, "wb"))
    {
        perror("Ошибка создания копии файла");
        fclose(Src);
        delete[] Data;
        return;
    }
    //Объем копируемых данных
    size_t DataValue = 0;
    //счетчик скопированных данных
    int Counter = 0;
    //считываем данные в цикле по частям(блокам) размером Size
    while (!feof(Src)) //пока не дошли до конца копируемого файла
    {
        //считываем данных в массив Data, подсчитываем объем данных и помещаем его в DataValue
        DataValue = fread(Data, sizeof(char), Size, Src);
        //куда, размер 1 объекта, кол-во объектов, откуда
        system("cls");
        //для размера буфера 100Мб
        //Counter += 100;
        //cout << "Скопировано: " << Counter << " МБ" << endl;
        //для размер абуфера в процентах
        Counter++;
        cout << "Скопировано: " << Counter << "%" << endl;
        if (DataValue) fwrite(Data, sizeof(char), DataValue, Dest);
        //откуда, размер 1 объекта, кол-во объектов, куда
    }
    //закрываем файлы
    if (fclose(Src) == EOF)perror("Ошибка закрытия файла"); //закрытие файла
    //fclose(Src);
    fclose(Dest);
    //освобождение память, выдленной под буфер
    delete[] Data;
    system("cls");
    cout << "Файл успешно скопирован!" << endl;
}
//Удаление файла
void Remove_File(const char* Name)
{
    //удаление и проверка
    if (remove(Name)) //возвращает 0 если удалось и код ошибки если нет
    {
        perror("Ошибка удаления файла! Проверьте имя и закрыт ли файл");
        return;
    }
    else cout << "Файл успешно удален!" << endl;
}
//Создание директории
void Create_Directory(const char* Name)
{
    //создание директории с проверкой
    if (_mkdir(Name) == EOF) // if (_mkdir(Name)==-1) //возвращает -1 при неудаче
    {
        perror("Ошибка при создании директории! Проверьте имя и путь");
        return;
    }
    else cout << "Директория успешно создана!" << endl;
}
//Переименование директории
void Rename_Directory()
{
    //текущее и новое имя директории
    char OldName[MAX_PATH]{};
    char NewName[MAX_PATH]{};

    cout << "Введите старое имя директории, с указанием пути к ней: ";
    gets_s(OldName);
    cout << "Введите новое  имя директории: ";
    gets_s(NewName);
    char drive[3];//хранит символ диска
    char dir[MAX_PATH]{};//хранит каталог и подкаталоги
    char fname[MAX_PATH]{};//хранит имя 
    char ext[MAX_PATH]{};//хранит расширение
    char FullName[MAX_PATH]{};//новое полнео имя
    //функция расщепляет полный путь на диск,каталог,имя, расширение
    _splitpath_s(OldName, drive, dir, fname, ext);
    //функция создает строку составного пути из отдельных компонентов
    _makepath_s(FullName, drive, dir, NewName, ext);

    //переименование и проверка
    if (rename(OldName, FullName)) //возвращает 0 если удалось и код ошибки если нет
    {
        perror("Ошибка переименования директории! Проверьте старый и новый путь и имя директории");
        return;
    }
    else cout << "Директория успешно переименована!" << endl;
}
//Перемещение директории
void Move_Directory()
{
    //текущее и новое имя директории
    char Source[MAX_PATH]{};
    char Destination[MAX_PATH]{};
    cout << "Введите старый путь к директории и имя: ";
    gets_s(Source);
    cout << "Введите новый  путь к директории(без указания имени): ";
    gets_s(Destination);
    char drive[3];//хранит символ диска
    char dir[MAX_PATH]{};//хранит каталог и подкаталоги
    char fname[MAX_PATH]{};//хранит имя 
    char ext[MAX_PATH]{};//хранит расширение

    //функция расщепляет полный путь на диск,каталог,имя, расширение
    _splitpath_s(Source, drive, dir, fname, ext);
    //к указанному пути добавляем "\"
    strcat_s(Destination, "\\");
    //добавляем извлеченное имя
    strcat_s(Destination, fname);
    //добавляем расширение
    strcat_s(Destination, ext);
    cout << Destination << endl;
    if (Source[0] = Destination[0])
    {
        if (rename(Source, Destination)) //возвращает 0 если удалось и код ошибки если нет
        {
            perror("Ошибка перемещения директории! Проверьте старый и новый путь и имя директории");
            return;
        }
        else cout << "Директория успешно перемещена!" << endl;
        return;
    }
    Copy_Directory(Source, Destination);
    Remove_Directory(Source); //Remove_Directory(); должна удалять не пустые папки

}
//Копирование директории
void Copy_Directory(const char* Source, const char* Destination)
{
    static int CountDirs = 0;  //кол-во скопированных директорий
    //static int CountDirs = 1; //если хотим считать саму исходную папку, даже если она пустая
    static int CountFiles = 0; //кол-во скопированных файлов
    char Path[MAX_PATH]{}; //пусть с маской для поиска всего содержимого директории
    strcpy_s(Path, Source); //копируем имя исходной директории
    strcat_s(Path, "\\.");//добвляем маску для поиска всех файлов и подкатологов в исходной директории
    //динамический объект структуры для хранения данных о файлах
    _finddata_t* InfoFiles = new _finddata_t;
    //начинаем поиск
    intptr_t Done = _findfirst(Path, InfoFiles);
    //если Done == -1 значит ничего не найдено
    intptr_t MayWeWork = Done; //для проверки закончились ли найденные файлы
    if (MayWeWork == EOF)  // if(MayWeWork == -1) 
    {
        cout << "Копируемая директория не существует!" << endl;
        delete InfoFiles;
        return;
    }
    //создаем директорию назначения
    Create_Directory(Destination); //для удаления создавать не нужно
    //поиск и копирование содержимого из исходного каталога
    while (MayWeWork != EOF) //while (MayWeWork != -1)
    {
        //исключаем обработку системных директорий . и ..
        if (strcmp(InfoFiles->name, ".") && strcmp(InfoFiles->name, ".."))
        {
            //временная строка для хранения полного пути к подкаталогу или файлу в источнике
            char SRC[MAX_PATH]{};
            //запоминаем полный путь к подкаталогу или файлу в источнике
            strcpy_s(SRC, Source); //путь к исходной директории(текущему каталогу)
            strcat_s(SRC, "\\"); //добавляем строку с символом '\'
            strcat_s(SRC, InfoFiles->name); //добавляем имя найденного подкаталога или файла
            //string SRC=Source; SRC+="\\";SRC+=InfoFiles->name; //через класс string

            //временная строка для хранения полного пути к подкаталогу или файлу в назначении
            char DEST[MAX_PATH]{};
            //запоминаем полный путь к подкаталогу или файлу в назначении
            strcpy_s(DEST, Destination); //путь к директории назначния(подкаталогу в директории назначения)
            strcat_s(DEST, "\\"); //добавляем строку с символом '\'
            strcat_s(DEST, InfoFiles->name); //добавляем имя найденного подкаталога или файла
            //string DEST=Destination; DEST+="\\";DEST+=InfoFiles->name; //через класс string

            //проверка директория ли
            if (InfoFiles->attrib & _A_SUBDIR) //если атрибут содержит "ключ" директория
            {
                //копируем подкаталог
                CountDirs++; //увеличиваем кол-во скопированных директорий
                Copy_Directory(SRC, DEST); //рекурсивно вызываем функции для копирования подкаталога
                //для удаления Remove_Directory(SRC)
            }
            else //иначе найден файл
            {
                //копируем файл
                CountFiles++; //увеличиваем кол-во скопированных файлов
                Copy_File(SRC, DEST);
                //для удаления Remove_File(SRC)
            }
        }
        MayWeWork = _findnext(Done, InfoFiles);
    }
    //_rmdir(Name); для удаления исходной папки после удаления всего её содержимого
    _findclose(Done); //завершения поиска
    delete InfoFiles; //освобождаем память
    system("cls");
    //выводим кол-во скопированных файлов и директорий
    cout << "Скопированно: " << CountDirs << " директорий и " << CountFiles << " файлов!" << endl;
}
//Удаление директории
void Remove_Directory(const char* Name)
{
    static int CountDirs = 0;  //кол-во удаленных директорий
    static int CountFiles = 0; //кол-во удаленных файлов
    //удаление и проверка
    if (_rmdir(Name) == EOF) // if(_rmdir(Name) == -1) //возвращает -1 при неудаче
    {
        perror("Ошибка удаления директории! Проверьте имя директории");
        char Path[MAX_PATH]{}; //пусть с маской для поиска всего содержимого директории
        strcpy_s(Path, Name); //копируем имя исходной директории
        strcat_s(Path, "\\.");//добвляем маску для поиска всех файлов и подкатологов в исходной директории
        //динамический объект структуры для хранения данных о файлах
        _finddata_t* InfoFiles = new _finddata_t;
        //начинаем поиск
        intptr_t Done = _findfirst(Path, InfoFiles);
        //если Done == -1 значит ничего не найдено
        intptr_t MayWeWork = Done; //для проверки закончились ли найденные файлы
        if (MayWeWork == EOF)  // if(MayWeWork == -1) 
        {
            cout << "Удаляемая директория не существует!" << endl;
            delete InfoFiles;
            return;
        }
        //поиск и копирование содержимого из исходного каталога
        while (MayWeWork != EOF) //while (MayWeWork != -1)
        {
            //исключаем обработку системных директорий . и ..
            if (strcmp(InfoFiles->name, ".") && strcmp(InfoFiles->name, ".."))
            {
                //временная строка для хранения полного пути к подкаталогу или файлу в источнике
                char SRC[MAX_PATH]{};
                //запоминаем полный путь к подкаталогу или файлу в источнике
                strcpy_s(SRC, Name); //путь к исходной директории(текущему каталогу)
                strcat_s(SRC, "\\"); //добавляем строку с символом '\'
                strcat_s(SRC, InfoFiles->name); //добавляем имя найденного подкаталога или файла
                //string SRC=Source; SRC+="\\";SRC+=InfoFiles->name; //через класс string
                //проверка директория ли
                if (InfoFiles->attrib & _A_SUBDIR) //если атрибут содержит "ключ" директория
                {
                    Remove_Directory(SRC);
                    CountDirs++;
                }
                else //иначе найден файл
                {
                    Remove_File(SRC);
                    CountFiles++;
                }
            }
            MayWeWork = _findnext(Done, InfoFiles);
        }
        _rmdir(Name);// для удаления исходной папки после удаления всего её содержимого
        _findclose(Done); //завершения поиска
        delete InfoFiles; //освобождаем память
        system("cls");
        cout << "Директория успешно удалена!" << endl;
        cout << "Удалено: " << CountDirs << " директорий и " << CountFiles << " файлов!" << endl;
    }
    else cout << "Директория успешно удалена!" << endl;
}
//Просмотр содержимого директории
void Show_Directory(string Name)
{
    //можно написать по аналогии с Find_File()
    //массив символов для хранения текущего каталога
    char CurDir[MAX_PATH]{};
    if (!Name.size()) //if(Name=="")
    {
        GetCurrentDirectoryA(MAX_PATH, CurDir);
        Name = CurDir; //помещаем в имя директории назавание текущего каталога 
    }
    //полный путь с маской для всего содержимого каталога
    string FullPath = Name + "\\."; //D:\PV323\.

    //динамический объект структуры для хранения данных о файлах
    _finddata_t* InfoFiles = new _finddata_t;
    //начинаем поиск
    intptr_t Done = _findfirst(FullPath.c_str(), InfoFiles);
    //если Done == -1 значит ничего не найдено
    intptr_t MayWeWork = Done; //для проверки закончились ли найденные файлы
    int CountFiles = 0, CountDirs = 0; //кол-во найденных файлов и директорий
    if (MayWeWork == EOF)  // if(MayWeWork == -1) 
    {
        cout << "Директория не существует!" << endl;
        delete InfoFiles;
        return;
    }
    if (Name != CurDir) cout << "Содержимое директории " << Name << endl;
    else cout << "Содержимое текущей директории " << Name << endl;
    while (MayWeWork != EOF) //while (MayWeWork != -1)
    {
        //исключаем обработку системных директорий . и ..
        if (strcmp(InfoFiles->name, ".") && strcmp(InfoFiles->name, ".."))
        {
            char Temp[26]{};
            tm Time{};
            gmtime_s(&Time, &InfoFiles->time_create); //преобразует время в объект стуректуры time
            asctime_s(Temp, &Time); //преобразует объект структуры time в строку
            Temp[24] = '\0'; //замена перевод строки на символ конца строки
            cout << Temp << " | ";
            //проверка директория ли
            if (InfoFiles->attrib & _A_SUBDIR) //если атрибут содержит "ключ" директория
            {
                cout << "Директория: \t|\t";
                CountDirs++;
            }
            else //иначе найден файл
            {
                cout << "Файл: \t|" << InfoFiles->size << "\t";
                CountFiles++;
            }
            if (InfoFiles->size <= 999999)cout << "\t";
            cout << "|" << InfoFiles->name << endl;
        }
        MayWeWork = _findnext(Done, InfoFiles);
    }
    //выводим кол-во найденных файлов и директорий
    cout << "Кол-во файлов: " << CountFiles << " кол-во директорий: " << CountDirs << endl;
    _findclose(Done); //завершения поиска
    delete InfoFiles; //освобождаем память
}