#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Функция для преобразования IP-адреса в целое число
unsigned int ip_to_int(const char *ip) {
  unsigned int a, b, c, d;
  sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
  return (a << 24) | (b << 16) | (c << 8) | d;
}

// Функция для преобразования целого числа в IP-адрес
void int_to_ip(unsigned int ip, char *ip_str) {
  sprintf(ip_str, "%u.%u.%u.%u", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

// Функция для проверки принадлежности IP-адреса к сети
int is_in_network(unsigned int ip_address, unsigned int network_address, unsigned int netmask) {
  return (ip_address & netmask) == (network_address & netmask);
}

int main() {
  char network_address_str[16];
  char netmask_str[16];
  int num_addresses;

  // Получение IP-адреса сети и маски сети от пользователя
  printf("Введите IP-адрес сети: ");
  scanf("%s", network_address_str);
  printf("Введите маску сети: ");
  scanf("%s", netmask_str);
  printf("Введите количество адресов для генерации: ");
  scanf("%d", &num_addresses);

  // Преобразование IP-адреса и маски сети в целые числа
  unsigned int network_address = ip_to_int(network_address_str);
  unsigned int netmask = ip_to_int(netmask_str);
  int amount;
  // Генерация случайных IP-адресов
  srand(time(NULL));
  for (int i = 0; i < num_addresses; i++) {
    unsigned int random_ip = rand() % 0xFFFFFFFF;

    // Преобразование целого числа в IP-адрес
    char ip_str[16];
    // Проверка принадлежности IP-адреса к сети
    if (is_in_network(random_ip, network_address, netmask)) {
     amount++;
    }
  }
    printf("Количество подходящих адресов: %d \n", amount);
    printf("Количество не подходящих адресов: %d \n", num_addresses-amount);
  return 0;
}