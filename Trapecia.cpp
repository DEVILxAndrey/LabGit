#include <iostream>
#include <cmath>

using namespace std;

// Функция для вычисления периметра
double perimeter(double a, double b, double c, double d) {
    return a + b + c + d;
}

// Функция для вычисления длины средней линии
double midLine(double a, double b) {
    return (a + b) / 2;
}

// Функция для вычисления площади через высоту
double heightarea(double a, double b, double c, double d) {
    double midLine = (a + b) / 2;
    return midLine * sqrt((pow(c, 2) - (pow((pow(a - b, 2) + pow(c, 2) - pow(d, 2)) / (2 * (a - b)), 2))));
}

int main() {
    setlocale(LC_ALL, "rus");
    double a, b, c, d;
    cout << "Введите параметры сторон трапеции (сначала основания, затем стороны): ";
    cin >> a >> b >> c >> d;
// Вывод данных
    cout << "Периметр: " << perimeter(a, b, c, d) << endl;
    cout << "Средняя линия: " << midLine(a, b) << endl;
    cout << "Площадь: " << heightarea(a, b, c, d) << endl;

}
