import Foundation

func isValidDate(day: Int, month: Int) -> Bool {
    return day >= 1 && day <= 31 && month >= 1 && month <= 12
}

func checkNumber(_ num: Int) -> String {
    let numStr = String(num)
    if numStr.first == "0" && numStr.count > 1 {
        return "NO"
    }
    let n = numStr.count
    for i in 1..<n {
        let dayStr = String(numStr.prefix(i))
        let monthStr = String(numStr.dropFirst(i))
        if dayStr.first == "0" {
            continue
        }
        if let day = Int(dayStr), let month = Int(monthStr), isValidDate(day: day, month: month) {
            return "YES"
        }
    }
    return "NO"
}

print("Введите целые числа через пробел (например, 3 1244 32 199):")
guard let inputStr = readLine()?.trimmingCharacters(in: .whitespaces) else {
    print("Ошибка: Не удалось прочитать ввод.")
    exit(1)
}

// Проверка на пустую строку или пробелы
if inputStr.isEmpty || inputStr.allSatisfy({ $0.isWhitespace }) {
    print("Ошибка: Введена пустая строка или только пробелы.")
    exit(1)
}

// Проверка на некорректные символы
if !inputStr.allSatisfy({ $0.isNumber || $0.isWhitespace }) {
    print("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).")
    exit(1)
}

let numbers = inputStr.split(separator: " ").compactMap { Int($0) }
if numbers.isEmpty {
    print("Ошибка: Не введено ни одного числа.")
    exit(1)
}

let result = numbers.map(checkNumber)

// Формат 1: строка
print("Результат (формат 1): \(result.joined(separator: " "))")

// Формат 2: столбец
print("Результат (формат 2):")
result.forEach { print($0) }