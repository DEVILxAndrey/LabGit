use std::io;

fn is_valid_date(day: i32, month: i32) -> bool {
    day >= 1 && day <= 31 && month >= 1 && month <= 12
}

fn check_number(num: i32) -> String {
    let num_str = num.to_string();
    if num_str.starts_with('0') && num_str.len() > 1 {
        return "NO".to_string();
    }
    let n = num_str.len();
    for i in 1..n {
        let day_str = &num_str[..i];
        let month_str = &num_str[i..];
        if day_str.starts_with('0') {
            continue;
        }
        if let (Ok(day), Ok(month)) = (day_str.parse::<i32>(), month_str.parse::<i32>()) {
            if is_valid_date(day, month) {
                return "YES".to_string();
            }
        }
    }
    "NO".to_string()
}

fn main() {
    println!("Введите целые числа через пробел (например, 3 1244 32 199):");
    let mut input_str = String::new();
    match io::stdin().read_line(&mut input_str) {
        Ok(_) => {
            let input_str = input_str.trim();
            // Проверка на пустую строку или пробелы
            if input_str.is_empty() || input_str.chars().all(char::is_whitespace) {
                println!("Ошибка: Введена пустая строка или только пробелы.");
                return;
            }

            // Проверка на некорректные символы
            if !input_str.chars().all(|c| c.is_digit(10) || c.is_whitespace()) {
                println!("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).");
                return;
            }

            let numbers: Vec<i32> = input_str
                .split_whitespace()
                .filter_map(|s| s.parse::<i32>().ok())
                .collect();

            if numbers.is_empty() {
                println!("Ошибка: Не введено ни одного числа.");
                return;
            }

            let result: Vec<String> = numbers.into_iter().map(check_number).collect();

            // Формат 1: строка
            println!("Результат (формат 1): {}", result.join(" "));

            // Формат 2: столбец
            println!("Результат (формат 2):");
            for res in result {
                println!("{}", res);
            }
        }
        Err(_) => println!("Ошибка: Не удалось прочитать ввод."),
    }
}