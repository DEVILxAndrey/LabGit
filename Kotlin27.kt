fun isValidDate(day: Int, month: Int): Boolean {
    return day in 1..31 && month in 1..12
}

fun checkNumber(num: Int): String {
    val numStr = num.toString()
    if (numStr[0] == '0' && numStr.length > 1) {
        return "NO"
    }
    val n = numStr.length
    for (i in 1 until n) {
        val dayStr = numStr.substring(0, i)
        val monthStr = numStr.substring(i)
        if (dayStr[0] == '0') {
            continue
        }
        try {
            val day = dayStr.toInt()
            val month = monthStr.toInt()
            if (isValidDate(day, month)) {
                return "YES"
            }
        } catch (e: NumberFormatException) {
            continue
        }
    }
    return "NO"
}

fun main() {
    println("Введите целые числа через пробел (например, 3 1244 32 199):")
    val inputStr = readLine()?.trim() ?: ""
    
    // Проверка на пустую строку или пробелы
    if (inputStr.isEmpty() || inputStr.isBlank()) {
        println("Ошибка: Введена пустая строка или только пробелы.")
        return
    }

    // Проверка на некорректные символы
    if (!inputStr.all { it.isDigit() || it.isWhitespace() }) {
        println("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).")
        return
    }

    val numbers = inputStr.split("\\s+".toRegex()).mapNotNull {
        try {
            it.toInt()
        } catch (e: NumberFormatException) {
            null
        }
    }
    
    if (numbers.isEmpty()) {
        println("Ошибка: Не введено ни одного числа.")
        return
    }

    val result = numbers.map { checkNumber(it) }

    // Формат 1: строка
    println("Результат (формат 1): ${result.joinToString(" ")}")

    // Формат 2: столбец
    println("Результат (формат 2):")
    result.forEach { println(it) }
}