#include <iostream>
#include <cmath>

int main() {
    double a, b, c;

    // Запросить длины сторон треугольника
    std::cout << "Введите длину первой стороны треугольника: ";
    std::cin >> a;
    std::cout << "Введите длину второй стороны треугольника: ";
    std::cin >> b;
    std::cout << "Введите длину третьей стороны треугольника: ";
    std::cin >> c;

    // Проверка на существование треугольника
    if (a + b > c && a + c > b && b + c > a) {
        // Вычислить периметр
        double perimeter = a + b + c;

        // Вычислить площадь по формуле Герона
        double s = perimeter / 2;
        double area = std::sqrt(s * (s - a) * (s - b) * (s - c));

        // Проверка на равнобедренность и вывод результатов
        std::cout << "Периметр треугольника: " << perimeter << std::endl;
        std::cout << "Площадь треугольника: " << area << std::endl;

        if (a == b || b == c || a == c) {
            std::cout << "Треугольник равнобедренный." << std::endl;
        } else {
            std::cout << "Треугольник не равнобедренный." << std::endl;
        }
    } else {
        std::cout << "Треугольник с такими сторонами не существует." << std::endl;
    }ввел изнение

    return 0;
}
