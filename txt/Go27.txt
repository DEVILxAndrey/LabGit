package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
    "unicode"
)

func isValidDate(day, month int) bool {
    return day >= 1 && day <= 31 && month >= 1 && month <= 12
}

func checkNumber(num int) string {
    numStr := fmt.Sprint(num)
    if numStr[0] == '0' && len(numStr) > 1 {
        return "NO"
    }
    n := len(numStr)
    for i := 1; i < n; i++ {
        dayStr := numStr[:i]
        monthStr := numStr[i:]
        if dayStr[0] == '0' {
            continue
        }
        day, err1 := strconv.Atoi(dayStr)
        month, err2 := strconv.Atoi(monthStr)
        if err1 == nil && err2 == nil && isValidDate(day, month) {
            return "YES"
        }
    }
    return "NO"
}

func main() {
    fmt.Println("Введите целые числа через пробел (например, 3 1244 32 199):")
    scanner := bufio.NewScanner(os.Stdin)
    scanner.Scan()
    inputStr := strings.TrimSpace(scanner.Text())

    // Проверка на пустую строку или пробелы
    if inputStr == "" || strings.TrimSpace(inputStr) == "" {
        fmt.Println("Ошибка: Введена пустая строка или только пробелы.")
        return
    }

    // Проверка на некорректные символы
    for _, r := range inputStr {
        if !unicode.IsDigit(r) && !unicode.IsSpace(r) {
            fmt.Println("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).")
            return
        }
    }

    parts := strings.Fields(inputStr)
    numbers := make([]int, 0)
    for _, part := range parts {
        if num, err := strconv.Atoi(part); err == nil {
            numbers = append(numbers, num)
        }
    }

    if len(numbers) == 0 {
        fmt.Println("Ошибка: Не введено ни одного числа.")
        return
    }

    result := make([]string, len(numbers))
    for i, num := range numbers {
        result[i] = checkNumber(num)
    }

    // Формат 1: строка
    fmt.Println("Результат (формат 1):", strings.Join(result, " "))

    // Формат 2: столбец
    fmt.Println("Результат (формат 2):")
    for _, res := range result {
        fmt.Println(res)
    }
}