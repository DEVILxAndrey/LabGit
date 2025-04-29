def is_valid_date(day, month)
  day >= 1 && day <= 31 && month >= 1 && month <= 12
end

def check_number(num)
  num_str = num.to_s
  return "NO" if num_str[0] == '0' && num_str.length > 1
  n = num_str.length
  (1...n).each do |i|
    day_str = num_str[0...i]
    month_str = num_str[i..-1]
    next if day_str[0] == '0'
    begin
      day = day_str.to_i
      month = month_str.to_i
      return "YES" if is_valid_date(day, month)
    rescue
      next
    end
  end
  "NO"
end

puts "Введите целые числа через пробел (например, 3 1244 32 199):"
input_str = gets&.strip || ""

# Проверка на пустую строку или пробелы
if input_str.empty? || input_str.match?(/^\s+$/)
  puts "Ошибка: Введена пустая строка или только пробелы."
  exit 1
end

# Проверка на некорректные символы
unless input_str.match?(/^[0-9\s]+$/)
  puts "Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы)."
  exit 1
end

numbers = input_str.split.map { |s| s.to_i rescue nil }.compact
if numbers.empty?
  puts "Ошибка: Не введено ни одного числа."
  exit 1
end

result = numbers.map { |num| check_number(num) }

# Формат 1: строка
puts "Результат (формат 1): #{result.join(" ")}"

# Формат 2: столбец
puts "Результат (формат 2):"
result.each { |res| puts res }