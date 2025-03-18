#include <iostream>
#include <cmath>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");
    double width, height;

    // Запросить размеры прямоугольника
    std::cout << "Введите ширину прямоугольника: ";
    std::cin >> width;
    std::cout << "Введите длину прямоугольника: ";
    std::cin >> height;

    // Вычислить периметр
    double perimeter = 2 * (width + height);

    // Вычислить площадь
    double area = width * height;

    // Вычислить длину диагонали
    double diagonal = std::sqrt(width * width + height * height);

    // Вывести результаты
    std::cout << "Периметр прямоугольника: " << perimeter << std::endl;
    std::cout << "Площадь прямоугольника: " << area << std::endl;
    std::cout << "Длина диагонали прямоугольника: " << diagonal << std::endl;
 
    return 0;
}