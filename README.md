# README: Файловый менеджер на C++
## Описание
Простой консольный файловый менеджер, реализованный на C++ с использованием стандартной библиотеки <filesystem> (C++17). Поддерживает основные операции с файлами и директориями.
## Особенности
- Кроссплатформенность (Windows/Linux/macOS)
- Поддержка всех базовых файловых операций
- Чистый C++ без внешних зависимостей
- Подробный вывод информации о файлах
- Встроенная система помощи
## Команды

| Команда               | Описание                          | Пример использования       | Аналог в терминале      |
|-----------------------|-----------------------------------|----------------------------|-------------------------|
| `ls` или `dir`        | Список файлов и папок             | `ls`                       | `ls` (Linux), `dir` (Win) |
| `pwd`                 | Текущая директория                | `pwd`                      | `pwd`                   |
| `cd <путь>`           | Перейти в директорию              | `cd ../parent`             | `cd`                    |
| `mkdir <имя>`         | Создать папку                     | `mkdir new_folder`         | `mkdir`                 |
| `rmdir <имя>`         | Удалить папку (рекурсивно)        | `rmdir old_dir`            | `rm -r` (Linux), `rd` (Win) |
| `rm <файл>`           | Удалить файл                      | `rm file.txt`              | `rm` (Linux), `del` (Win) |
| `cp <источник> <цель>`| Копировать файл                   | `cp a.txt b.txt`           | `cp` (Linux), `copy` (Win) |
| `cat <файл>`          | Просмотр содержимого файла        | `cat log.txt`              | `cat` (Linux), `type` (Win) |
| `help`                | Справка по командам               | `help`                     | `--help`                |
| `exit` или `quit`     | Выйти из программы                | `exit`                     | `exit`                  |
## Сборка и запуск
### Требования
- Компилятор с поддержкой C++17 (GCC 8+, Clang 7+, MSVC 19.14+)
- CMake 3.10+
### Инструкция по сборке
```
git clone https://github.com/your-repo/file-manager-cpp.git
cd file-manager-cpp
mkdir build && cd build
cmake ..
make

./file_manager
```
Для Windows (Visual Studio):
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```
## Структура проекта
```
file_manager/
├── include/
│   ├── FileManager.hpp    
│   └── helpers.hpp        
├── src/
│   ├── FileManager.cpp    
│   └── main.cpp           
├── CMakeLists.txt         
├── README.md     
└── .gitignore
```       