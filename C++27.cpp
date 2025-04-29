#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

bool is_valid_date(int day, int month) {
    return day >= 1 && day <= 31 && month >= 1 && month <= 12;
}

std::string check_number(int num) {
    std::string num_str = std::to_string(num);
    if (num_str[0] == '0' && num_str.length() > 1) {
        return "NO";
    }
    int n = num_str.length();
    for (int i = 1; i < n; ++i) {
        std::string day_str = num_str.substr(0, i);
        std::string month_str = num_str.substr(i);
        if (day_str[0] == '0') {
            continue;
        }
        try {
            int day = std::stoi(day_str);
            int month = std::stoi(month_str);
            if (is_valid_date(day, month)) {
                return "YES";
            }
        } catch (...) {
            continue;
        }
    }
    return "NO";
}

int main() {
    std::cout << "Введите целые числа через пробел (например, 3 1244 32 199): ";
    std::string input_str;
    std::getline(std::cin, input_str);

    // Проверка на пустую строку или пробелы
    if (input_str.empty() || input_str.find_first_not_of(" \t\n\r") == std::string::npos) {
        std::cout << "Ошибка: Введена пустая строка или только пробелы.\n";
        return 1;
    }

    // Проверка на некорректные символы
    for (char c : input_str) {
        if (!std::isdigit(c) && !std::isspace(c)) {
            std::cout << "Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).\n";
            return 1;
        }
    }

    std::vector<int> numbers;
    std::stringstream ss(input_str);
    int num;
    try {
        while (ss >> num) {
            numbers.push_back(num);
        }
        if (numbers.empty()) {
            std::cout << "Ошибка: Не введено ни одного числа.\n";
            return 1;
        }

        std::vector<std::string> result;
        for (int num : numbers) {
            result.push_back(check_number(num));
        }

        // Формат 1: строка
        std::cout << "Результат (формат 1): ";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << (i < result.size() - 1 ? " " : "\n");
        }

        // Формат 2: столбец
        std::cout << "Результат (формат 2):\n";
        for (const auto& res : result) {
            std::cout << res << "\n";
        }
    } catch (...) {
        std::cout << "Ошибка: Введите корректные целые числа.\n";
        return 1;
    }

    return 0;
}