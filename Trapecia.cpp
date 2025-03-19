#include <iostream>
#include <cmath>

using namespace std;

// Нахождение периметра
double perimeter(double a, double b, double c, double d) {
    return a + b + c + d;
}

// Нахождение средней линии
double midLine(double a, double b) {
    return (a + b) / 2;
}

// Нахождение площади
double heightarea(double a, double b, double c, double d) {
    double midLine = (a + b) / 2;
    return midLine * sqrt((pow(c, 2) - (pow((pow(a - b, 2) + pow(c, 2) - pow(d, 2)) / (2 * (a - b)), 2))));
}

int main() {
    setlocale(LC_ALL, "rus");
    double a, b, c, d;
    
    cout << "Введите основание и стороны трапеции (сначала основание, затем стороны): ";
    cin >> a >> b >> c >> d;

    // Проверка на отрицательные числа
    if (a < 0 || b < 0 || c < 0 || d < 0) {
        cout << "Ошибка: введены отрицательные числа." << endl;
        return 1;
    }

    // Проверка на существование трапеции
    if (c + d <= abs(a - b)) {
        cout << "Ошибка: Такой трапеции не существует!" << endl;
        return 1;
    }

    // Вывод
    cout << "Периметр: " << perimeter(a, b, c, d) << endl;
    cout << "Средняя линия: " << midLine(a, b) << endl;
    cout << "Площадь: " << heightarea(a, b, c, d) << endl;

    return 0;
}