import java.util.*;
import java.util.stream.Collectors;

public class Variant27 {
    static boolean isValidDate(int day, int month) {
        return day >= 1 && day <= 31 && month >= 1 && month <= 12;
    }

    static String checkNumber(int num) {
        String numStr = Integer.toString(num);
        if (numStr.charAt(0) == '0' && numStr.length() > 1) {
            return "NO";
        }
        int n = numStr.length();
        for (int i = 1; i < n; i++) {
            String dayStr = numStr.substring(0, i);
            String monthStr = numStr.substring(i);
            if (dayStr.charAt(0) == '0') {
                continue;
            }
            try {
                int day = Integer.parseInt(dayStr);
                int month = Integer.parseInt(monthStr);
                if (isValidDate(day, month)) {
                    return "YES";
                }
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return "NO";
    }

    public static void main(String[] args) {
        System.out.println("Введите целые числа через пробел (например, 3 1244 32 199):");
        Scanner scanner = new Scanner(System.in);
        String inputStr = scanner.nextLine().trim();

        // Проверка на пустую строку или пробелы
        if (inputStr.isEmpty() || inputStr.matches("\\s+")) {
            System.out.println("Ошибка: Введена пустая строка или только пробелы.");
            scanner.close();
            return;
        }

        // Проверка на некорректные символы
        if (!inputStr.matches("[0-9\\s]+")) {
            System.out.println("Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).");
            scanner.close();
            return;
        }

        List<Integer> numbers;
        try {
            numbers = Arrays.stream(inputStr.split("\\s+"))
                           .map(Integer::parseInt)
                           .collect(Collectors.toList());
            if (numbers.isEmpty()) {
                System.out.println("Ошибка: Не введено ни одного числа.");
                scanner.close();
                return;
            }
        } catch (NumberFormatException e) {
            System.out.println("Ошибка: Введите корректные целые числа.");
            scanner.close();
            return;
        }

        List<String> result = numbers.stream().map(Variant27::checkNumber).collect(Collectors.toList());

        // Формат 1: строка
        System.out.println("Результат (формат 1): " + String.join(" ", result));

        // Формат 2: столбец
        System.out.println("Результат (формат 2):");
        result.forEach(System.out::println);

        scanner.close();
    }
}