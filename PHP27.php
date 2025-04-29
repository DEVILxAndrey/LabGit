<?php

function is_valid_date($day, $month) {
    return $day >= 1 && $day <= 31 && $month >= 1 && $month <= 12;
}

function check_number($num) {
    $num_str = (string)$num;
    if ($num_str[0] === '0' && strlen($num_str) > 1) {
        return "NO";
    }
    $n = strlen($num_str);
    for ($i = 1; $i < $n; $i++) {
        $day_str = substr($num_str, 0, $i);
        $month_str = substr($num_str, $i);
        if ($day_str[0] === '0') {
            continue;
        }
        if (is_numeric($day_str) && is_numeric($month_str)) {
            $day = (int)$day_str;
            $month = (int)$month_str;
            if (is_valid_date($day, $month)) {
                return "YES";
            }
        }
    }
    return "NO";
}

echo "Введите целые числа через пробел (например, 3 1244 32 199):\n";
$input_str = trim(fgets(STDIN));

// Проверка на пустую строку или пробелы
if (empty($input_str) || preg_match('/^\s+$/', $input_str)) {
    echo "Ошибка: Введена пустая строка или только пробелы.\n";
    exit(1);
}

// Проверка на некорректные символы
if (!preg_match('/^[\d\s]+$/', $input_str)) {
    echo "Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).\n";
    exit(1);
}

$numbers = array_filter(array_map('intval', preg_split('/\s+/', $input_str)));
if (empty($numbers)) {
    echo "Ошибка: Не введено ни одного числа.\n";
    exit(1);
}

$result = array_map('check_number', $numbers);

// Формат 1: строка
echo "Результат (формат 1): " . implode(" ", $result) . "\n";

// Формат 2: столбец
echo "Результат (формат 2):\n";
foreach ($result as $res) {
    echo "$res\n";
}

?>