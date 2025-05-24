#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_LOCATION_LEN 50
#define FILENAME "enterprises.dat"

typedef struct {
    char name[MAX_NAME_LEN];
    char location[MAX_LOCATION_LEN];
    double fund_value;
} Enterprise;

void input_enterprises(Enterprise *enterprises, int count) 
{
    for (int i = 0; i < count; i += 1) 
    {
        printf("\nПідприємство #%d:\n", i+1);
        printf("Назва: ");
        scanf("%s", enterprises[i].name);
        printf("Місцезнаходження: ");
        scanf("%s", enterprises[i].location);
        printf("Вартість фондів: ");
        scanf("%lf", &enterprises[i].fund_value);
    }
}

void write_to_file(Enterprise *enterprises, int count) 
{
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) 
    {
        printf("Помилка відкриття файлу для запису!\n");
        exit(1);
    }
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(enterprises, sizeof(Enterprise), count, file);
    fclose(file);
}

void read_from_file(Enterprise **enterprises, int *count) 
{
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) 
    {
        printf("Помилка відкриття файлу для читання!\n");
        exit(1);
    }
    
    fread(count, sizeof(int), 1, file);
    *enterprises = malloc(*count * sizeof(Enterprise));
    fread(*enterprises, sizeof(Enterprise), *count, file);
    fclose(file);
}

void update_funds(Enterprise *enterprises, int count) 
{
    printf("\nОновлення вартості фондів:\n");
    for (int i = 0; i < count; i += 1) 
    {
        printf("Підприємство '%s' (поточна вартість: %.2lf): ", 
               enterprises[i].name, enterprises[i].fund_value);
        scanf("%lf", &enterprises[i].fund_value);
    }
}

void print_enterprises(Enterprise *enterprises, int count) 
{
    printf("\nСписок підприємств:\n");
    for (int i = 0; i < count; i += 1) 
    {
        printf("%d. %s, %s, %.2lf\n", 
               i+1, enterprises[i].name, 
               enterprises[i].location, enterprises[i].fund_value);
    }
}

int main() 
{
    system("chcp 65001");
    int count;
    Enterprise *enterprises = NULL;

    printf("Введіть кількість підприємств: ");
    scanf("%d", &count);
    
    enterprises = malloc(count * sizeof(Enterprise));
    input_enterprises(enterprises, count);

    write_to_file(enterprises, count);
    printf("\nДані збережено у файл %s\n", FILENAME);
    
    free(enterprises);
    read_from_file(&enterprises, &count);

    print_enterprises(enterprises, count);
    update_funds(enterprises, count);
    
    write_to_file(enterprises, count);
    printf("\nОновлені дані збережено у файл %s\n", FILENAME);
    
    free(enterprises);
    return 0;
}