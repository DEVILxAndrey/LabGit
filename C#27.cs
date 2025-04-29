using System;
using System.Collections.Generic;
using System.Linq;

class Program {
    static bool IsValidDate(int day, int month) {
        return day >= 1 && day <= 31 && month >= 1 && month <= 12;
    }

    static string CheckNumber(int num) {
        string numStr = num.ToString();
        if (numStr[0] == '0' && numStr.Length > 1) {
            return "NO";
        }
        int n = numStr.Length;
        for (int i = 1; i < n; i++) {
            string dayStr = numStr.Substring(0, i);
            string monthStr = numStr.Substring(i);
            if (dayStr[0] == '0') {
                continue;
            }
            try {
                int day = int.Parse(dayStr);
                int month = int.Parse(monthStr);
                if (IsValidDate(day, month)) {
                    return "YES";
                }
            } catch {
                continue;
            }
        }
        return "NO";
    }

    static void Main() {
        Console.WriteLine("Введите целые числа через пробел (например, 3 1244 32 199):");
        string inputStr = Console.ReadLine()?.Trim() ?? "";

        // Проверка на пустую строку или пробелы
        if (string.IsNullOrWhiteSpace(inputStr)) {
            Console.WriteLine("Ошибка: Введена пустая строка или только пробелы.");
            return;
        }

        // Проверка на некорректные символы
        if (!inputStr.All(c => char.IsDigit(c) || char.IsWhiteSpace(c))) {
            Console.WriteLine("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).");
            return;
        }

        List<int> numbers;
        try {
            numbers = inputStr.Split().Select(int.Parse).ToList();
            if (!numbers.Any()) {
                Console.WriteLine("Ошибка: Не введено ни одного числа.");
                return;
            }
        } catch {
            Console.WriteLine("Ошибка: Введите корректные целые числа.");
            return;
        }

        var result = numbers.Select(CheckNumber).ToList();

        // Формат 1: строка
        Console.WriteLine("Результат (формат 1): " + string.Join(" ", result));

        // Формат 2: столбец
        Console.WriteLine("Результат (формат 2):");
        foreach (var res in result) {
            Console.WriteLine(res);
        }
    }
}