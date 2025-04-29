import * as readline from 'readline';

function isValidDate(day: number, month: number): boolean {
    return day >= 1 && day <= 31 && month >= 1 && month <= 12;
}

function checkNumber(num: number): string {
    const numStr = num.toString();
    if (numStr[0] === '0' && numStr.length > 1) {
        return "NO";
    }
    const n = numStr.length;
    for (let i = 1; i < n; i++) {
        const dayStr = numStr.slice(0, i);
        const monthStr = numStr.slice(i);
        if (dayStr[0] === '0') {
            continue;
        }
        try {
            const day = parseInt(dayStr, 10);
            const month = parseInt(monthStr, 10);
            if (!isNaN(day) && !isNaN(month) && isValidDate(day, month)) {
                return "YES";
            }
        } catch {
            continue;
        }
    }
    return "NO";
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Введите целые числа через пробел (например, 3 1244 32 199):\n', (inputStr: string) => {
    const trimmed = inputStr.trim();

    // Проверка на пустую строку или пробелы
    if (!trimmed || /^\s+$/.test(trimmed)) {
        console.log("Ошибка: Введена пустая строка или только пробелы.");
        rl.close();
        return;
    }

    // Проверка на некорректные символы
    if (!/^[0-9\s]+$/.test(trimmed)) {
        console.log("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).");
        rl.close();
        return;
    }

    const numbers = trimmed.split(/\s+/).map(num => parseInt(num, 10)).filter(num => !isNaN(num));
    if (numbers.length === 0) {
        console.log("Ошибка: Не введено ни одного числа.");
        rl.close();
        return;
    }

    const result = numbers.map(checkNumber);

    // Формат 1: строка
    console.log("Результат (формат 1):", result.join(" "));

    // Формат 2: столбец
    console.log("Результат (формат 2):");
    result.forEach(res => console.log(res));

    rl.close();
});