#include <experimental/filesystem>
#include <iostream>
#include <cstring>

namespace fs = std::experimental::filesystem;
using std::endl;

auto& out = std::cout;
auto& in = std::cin;

int main() {
    try {
        std::string address;
        out << endl
            << "Enter the path of file:" << endl
            << "example: 'explorer/file.dat' " << endl << endl;
        out << "input:\t";
        in  >> address;

        //  Проверка существования файла по введенному адресу
        if(!fs::exists(address))
            throw std::runtime_error("ERROR: Wrong address! File does not exist!");

        //  Указываем путь к файлу file.dat.
        const fs::path filePath = address;

        //  Получаем имя файла file.dat.
        const fs::path textFilename = filePath.filename();
        //  Получаем время последннего изменения файла file.dat.
        auto ftime = fs::last_write_time(filePath);
        //  Интерпритируем данные времени в строку для вывода.
        std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

        out << endl
            << "name:\t\t" << textFilename << endl
            << "size:\t\t" << (double(fs::file_size(filePath)) / 1000) << " Kb" << endl
            << "date_mod:\t" << std::asctime(std::localtime(&cftime)) << endl;

    } catch(const std::exception& e) {
        out << e.what() << endl;
    }  
}
