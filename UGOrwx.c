#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// Функция для изменения прав файла
int change_file_permissions(const char *file_path, mode_t mode) {
    if (chmod(file_path, mode) == -1) {
        perror("Ошибка при изменении прав доступа");
        return -1;
    }
    return 0;
}

// Функция для получения текущих прав файла
mode_t get_file_permissions(const char *file_path) {
    struct stat st;
    if (stat(file_path, &st) == -1) {
        perror("Ошибка при получении текущих прав доступа");
        exit(EXIT_FAILURE);
    }
    return st.st_mode;
}

int main() {
    char file_path[256];
    char action[16];
    char permissions_str[16];
    mode_t permissions;

    printf("Введите путь к файлу: ");
    scanf("%s", file_path);

    printf("Введите действие (add/remove/set): ");
    scanf("%s", action);

    printf("Введите права доступа (например, 755): ");
    scanf("%s", permissions_str);

    // Преобразование строки прав в режим (mode_t)
    permissions = strtol(permissions_str, NULL, 8);

    // Получение текущих прав файла
    mode_t current_permissions = get_file_permissions(file_path);

    printf("Текущие права: %04o", current_permissions);

    // Выполнение действия над правами доступа
    if (strcmp(action, "add") == 0) {
        permissions |= current_permissions;
    } else if (strcmp(action, "remove") == 0) {
        permissions = current_permissions & ~permissions;
    } else if (strcmp(action, "set") == 0) {
        // Нет необходимости изменять permissions, так как оно уже установлено
    } else {
        fprintf(stderr, "Некорректное действие\n");
        exit(EXIT_FAILURE);
    }

    // Изменение прав доступа к файлу
    if (change_file_permissions(file_path, permissions) == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Права доступа изменены успешно\n");
    return 0;
}
