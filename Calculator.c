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

typedef struct  
{
    const char *name;
    calculator_function func;

} operation;

operation calc[] =
{
    {"Сложение", add},
    {"Вычитание", subtract},
    {"Деление", divide}

};

#define NUM_OPERATIONS (sizeof(calc)/sizeof(operation))

int main() {
    int choice, num_args;
    double result;

    while (1) {
        printf("Выберите операцию:\n");
        for(int i = 0; i < NUM_OPERATIONS; i++)
        {
            printf("%d. %s \n", i+1, calc[i].name);
        }
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
        switch(num_args){
            case 1:
            {
            result = calc[choice - 1].func(num_args, arguments[0]);
            break;
            }
            case 2:
            {
            result = calc[choice - 1].func(num_args, arguments[0], arguments[1]);
            break;
            }
            case 3:
            {
            result = calc[choice - 1].func(num_args, arguments[0], arguments[1], arguments[2]);
            break;
            }
            case 4:
            {
            result = calc[choice - 1].func(num_args, arguments[0], arguments[1], arguments[2], arguments[3]);
            break;
            }
            case 5:
            {
            result = calc[choice - 1].func(num_args, arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]);
            break;
            }
        }

        printf("Результат: %.2lf\n", result);
    }

    return 0;
}