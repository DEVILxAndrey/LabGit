

section .data
    prompt db "Введите целые числа через пробел (например, 3 1244 32 199):", 10, 0
    prompt_len equ $ - prompt
    err_empty db "Ошибка: Введена пустая строка или только пробелы.", 10, 0
    err_empty_len equ $ - err_empty
    err_invalid db "Ошибка: Ввод содержит недопустимые символы (только цифры и пробелы).", 10, 0
    err_invalid_len equ $ - err_invalid
    err_no_numbers db "Ошибка: Не введено ни одного числа.", 10, 0
    err_no_numbers_len equ $ - err_no_numbers
    yes_str db "YES", 0
    yes_len equ $ - yes_str
    no_str db "NO", 0
    no_len equ $ - no_str
    space db " ", 0
    space_len equ $ - space
    newline db 10, 0
    newline_len equ $ - newline
    result1_prefix db "Результат (формат 1): ", 0
    result1_prefix_len equ $ - result1_prefix
    result2_prefix db "Результат (формат 2):", 10, 0
    result2_prefix_len equ $ - result2_prefix

section .bss
    input_buffer resb 256      ; Буфер для ввода строки
    numbers resq 64            ; Массив указателей на строки чисел
    num_count resq 1           ; Количество чисел
    result_buffer resb 256     ; Буфер для результатов (YES/NO)
    temp_str resb 32           ; Временный буфер для строки числа

section .text
global _start

; Системные вызовы Linux x86_64
%define SYS_read 0
%define SYS_write 1
%define SYS_exit 60
%define STDIN 0
%define STDOUT 1

_start:
    ; Вывод приглашения
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, prompt
    mov rdx, prompt_len
    syscall

    ; Чтение строки ввода
    mov rax, SYS_read
    mov rdi, STDIN
    mov rsi, input_buffer
    mov rdx, 256
    syscall

    ; Проверка длины ввода
    cmp rax, 0
    jle error_empty

    ; Сохранение длины строки (без \n)
    mov rbx, rax
    mov byte [input_buffer + rbx - 1], 0  ; Удаление \n

    ; Проверка на пустую строку или пробелы
    mov rsi, input_buffer
    call check_empty_or_spaces
    cmp rax, 1
    je error_empty

    ; Проверка на корректные символы (цифры и пробелы)
    mov rsi, input_buffer
    call check_valid_chars
    cmp rax, 0
    je error_invalid

    ; Разделение строки на числа
    mov rsi, input_buffer
    mov rdi, numbers
    call parse_numbers
    mov [num_count], rax
    cmp rax, 0
    je error_no_numbers

    ; Обработка каждого числа и формирование результатов
    mov rbx, 0                    ; Индекс числа
    mov rsi, result_buffer
process_number:
    cmp rbx, [num_count]
    jge process_done

    ; Получение указателя на строку числа
    mov rax, [numbers + rbx * 8]
    mov rdi, rax
    call check_number
    mov rcx, rax                  ; Сохраняем результат (YES/NO)

    ; Запись результата в буфер
    cmp rcx, 1
    je write_yes
    mov rax, no_str
    mov rdx, no_len
    jmp write_result
write_yes:
    mov rax, yes_str
    mov rdx, yes_len
write_result:
    mov rdi, rsi
    call strcpy
    add rsi, rdx                  ; Сдвиг в буфере результатов

    ; Добавляем пробел, если не последнее число
    mov rax, [num_count]
    dec rax
    cmp rbx, rax
    je skip_result_space
    mov byte [rsi], ' '
    inc rsi
skip_result_space:
    mov byte [rsi], 0             ; Нулевой терминатор

    inc rbx
    jmp process_number

process_done:
    ; Вывод формата 1: строка
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, result1_prefix
    mov rdx, result1_prefix_len
    syscall

    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, result_buffer
    mov rdx, rsi
    sub rdx, result_buffer
    syscall

    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, newline
    mov rdx, newline_len
    syscall

    ; Вывод формата 2: столбец
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, result2_prefix
    mov rdx, result2_prefix_len
    syscall

    mov rbx, 0
print_column:
    cmp rbx, [num_count]
    jge done

    mov rax, [numbers + rbx * 8]
    mov rdi, rax
    call check_number

    cmp rax, 1
    je print_yes
    mov rsi, no_str
    mov rdx, no_len
    jmp do_print
print_yes:
    mov rsi, yes_str
    mov rdx, yes_len
do_print:
    mov rax, SYS_write
    mov rdi, STDOUT
    syscall

    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, newline
    mov rdx, newline_len
    syscall

    inc rbx
    jmp print_column

done:
    ; Выход
    mov rax, SYS_exit
    mov rdi, 0
    syscall

error_empty:
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, err_empty
    mov rdx, err_empty_len
    syscall
    jmp exit_error

error_invalid:
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, err_invalid
    mov rdx, err_invalid_len
    syscall
    jmp exit_error

error_no_numbers:
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, err_no_numbers
    mov rdx, err_no_numbers_len
    syscall
    jmp exit_error

exit_error:
    mov rax, SYS_exit
    mov rdi, 1
    syscall

; Проверка, пуста ли строка или содержит только пробелы
; Вход: rsi - указатель на строку
; Выход: rax = 1 (пустая/пробелы), 0 (иначе)
check_empty_or_spaces:
    push rbx
    mov rax, 0
check_empty_loop:
    mov bl, [rsi]
    cmp bl, 0
    je check_empty_done
    cmp bl, ' '
    je next_char
    cmp bl, 9
    je next_char
    cmp bl, 10
    je next_char
    mov rax, 0
    jmp check_empty_done
next_char:
    inc rsi
    jmp check_empty_loop
check_empty_done:
    cmp rax, 0
    je not_empty
    mov rax, 1
not_empty:
    pop rbx
    ret

; Проверка, что строка содержит только цифры и пробелы
; Вход: rsi - указатель на строку
; Выход: rax = 1 (корректно), 0 (некорректно)
check_valid_chars:
    push rbx
    mov rax, 1
check_valid_loop:
    mov bl, [rsi]
    cmp bl, 0
    je check_valid_done
    cmp bl, '0'
    jl check_space
    cmp bl, '9'
    jle valid_char
check_space:
    cmp bl, ' '
    je valid_char
    cmp bl, 9
    je valid_char
    cmp bl, 10
    je valid_char
    mov rax, 0
    jmp check_valid_done
valid_char:
    inc rsi
    jmp check_valid_loop
check_valid_done:
    pop rbx
    ret

; Разделение строки на числа
; Вход: rsi - указатель на строку, rdi - массив для указателей
; Выход: rax - количество чисел
parse_numbers:
    push rbx
    push r12
    push r13
    mov r12, rdi          ; Сохраняем указатель на массив
    mov r13, 0            ; Счётчик чисел
parse_loop:
    mov bl, [rsi]
    cmp bl, 0
    je parse_done
    cmp bl, ' '
    je skip_space
    cmp bl, 9
    je skip_space
    cmp bl, 10
    je skip_space
    mov [r12 + r13 * 8], rsi
    inc r13
skip_number:
    inc rsi
    mov bl, [rsi]
    cmp bl, 0
    je parse_done
    cmp bl, ' '
    je end_number
    cmp bl, 9
    je end_number
    cmp bl, 10
    je end_number
    jmp skip_number
end_number:
    mov byte [rsi], 0
    inc rsi
    jmp parse_loop
skip_space:
    inc rsi
    jmp parse_loop
parse_done:
    mov rax, r13
    pop r13
    pop r12
    pop rbx
    ret

; Проверка числа на возможность формирования даты
; Вход: rdi - указатель на строку числа
; Выход: rax = 1 (YES), 0 (NO)
check_number:
    push rbx
    push r12
    push r13
    mov r12, rdi          ; Сохраняем указатель на строку

    ; Подсчёт длины строки
    mov rsi, r12
    call strlen
    mov r13, rax          ; Длина строки
    cmp r13, 2            ; Если длина < 2, дата невозможна
    jl no_valid_date

    mov rcx, 1            ; Позиция для '/'
check_position:
    cmp rcx, r13
    jge no_valid_date

    ; Копируем число во временный буфер
    mov rsi, r12
    mov rdi, temp_str
    call strcpy
    mov byte [temp_str + rcx], 0  ; Разделяем на day_str и month_str

    ; Проверка, что day_str не пустая
    mov bl, [temp_str]
    cmp bl, 0
    je next_position

    ; Преобразование day_str в число
    mov rsi, temp_str
    call atoi
    mov rbx, rax          ; day
    cmp rbx, 0
    je next_position

    ; Проверка, что month_str не пустая
    cmp byte [temp_str + rcx + 1], 0
    je next_position

    ; Преобразование month_str в число
    lea rsi, [temp_str + rcx + 1]
    call atoi
    mov rdx, rax          ; month
    cmp rdx, 0
    je next_position

    ; Проверка корректности даты
    cmp rbx, 1
    jl next_position
    cmp rbx, 31
    jg next_position
    cmp rdx, 1
    jl next_position
    cmp rdx, 12
    jg next_position

    mov rax, 1            ; YES
    jmp check_done

next_position:
    inc rcx
    jmp check_position

no_valid_date:
    mov rax, 0            ; NO

check_done:
    pop r13
    pop r12
    pop rbx
    ret

; Копирование строки
; Вход: rsi - источник, rdi - назначение
strcpy:
    push rbx
copy_loop:
    mov bl, [rsi]
    mov [rdi], bl
    cmp bl, 0
    je copy_done
    inc rsi
    inc rdi
    jmp copy_loop
copy_done:
    pop rbx
    ret

; Подсчёт длины строки
; Вход: rsi - указатель на строку
; Выход: rax - длина
strlen:
    push rbx
    mov rax, 0
strlen_loop:
    mov bl, [rsi + rax]
    cmp bl, 0
    je strlen_done
    inc rax
    jmp strlen_loop
strlen_done:
    pop rbx
    ret

; Преобразование строки в число
; Вход: rsi - указатель на строку
; Выход: rax - число
atoi:
    push rbx
    push rcx
    mov rax, 0
    mov rcx, 0
    ; Пропускаем ведущие нули
skip_leading_zeros:
    mov bl, [rsi + rcx]
    cmp bl, '0'
    jne start_conversion
    inc rcx
    cmp byte [rsi + rcx], 0
    je atoi_done
    jmp skip_leading_zeros
start_conversion:
    mov rax, 0
atoi_loop:
    mov bl, [rsi + rcx]
    cmp bl, 0
    je atoi_done
    sub bl, '0'
    cmp bl, 0
    jl atoi_invalid
    cmp bl, 9
    jg atoi_invalid
    imul rax, 10
    add rax, rbx
    inc rcx
    jmp atoi_loop
atoi_invalid:
    mov rax, 0
atoi_done:
    pop rcx
    pop rbx
    ret