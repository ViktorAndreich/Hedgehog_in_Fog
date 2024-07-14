#include <stdio.h>
#include <stdarg.h>
#include <tgmath.h>

// Определение типа для указателя на функцию с переменным количеством параметров
typedef double (*calculator_function)(int, ...);

// Функция сложения
double add(int num_args, ...) {
    va_list args;
    double sum = 0;
    va_start(args, num_args);
    for (int i = 0; i < num_args; i++) {
        sum += va_arg(args, double);
    }
    va_end(args);
    return sum;
}

// Функция вычитания
double subtract(int num_args, ...) {
    va_list args;
    double result = va_arg(args, double);
    va_start(args, num_args);
    for (int i = 1; i < num_args; i++) {
        result -= va_arg(args, double);
    }
    va_end(args);
    return result;
}

// Функция деления
double divide(int num_args, ...) {
    va_list args;
    double result = va_arg(args, double);
    va_start(args, num_args);
    for (int i = 1; i < num_args; i++) {
        result /= va_arg(args, double);
    }
    va_end(args);
    return result;
}

int main() {
    int choice, num_args;
    double result;

    // Массив указателей на функции
    calculator_function operations[] = {add, subtract, divide};

    while (1) {
        printf("Выберите операцию:\n");
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Деление\n");
        printf("0. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        if (choice > 3 || choice < 1) {
            printf("Неверный выбор. Попробуйте снова.\n");
            continue;
        }

        printf("Введите количество аргументов: ");
        scanf("%d", &num_args);

        // Ввод аргументов
        double arguments[num_args];
        printf("Введите %d чисел:\n", num_args);
        for (int i = 0; i < num_args; i++) {
            scanf("%lf", &arguments[i]);
        }

        // Вызов функции с помощью указателя
        result = operations[choice - 1](num_args, arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]);

        printf("Результат: %.2lf\n", result);
    }

    return 0;
}