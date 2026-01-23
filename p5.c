#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    // voi citi prenume, varsta, medie student
    FILE *ft = fopen("p5_f.txt", "wt");
    if(ft == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    char prenume_student[50];
    unsigned int varsta_student, i, n;
    float medie_student;

    printf("Introduceti numarul de studenti de la tastatura : ");
    scanf("%u", &n);
    getchar();

    for(i = 0; i < n; i++)
    {
        printf("Nume : ");
        fgets(prenume_student, 50, stdin);
        prenume_student[strcspn(prenume_student, "\n")] = '\0';
        fputs(prenume_student, ft);
        fprintf(ft, "\t");
        
        printf("Varsta : ");
        scanf("%u", &varsta_student);
        fprintf(ft, "%u", varsta_student);
        fprintf(ft, "\t");
        getchar();

        printf("Medie : ");
        scanf("%f", &medie_student);
        fprintf(ft, "%.2f", medie_student);
        fprintf(ft, "\n");
        getchar();
        printf("\n");
    }
    fclose(ft);

    ft = fopen("p5_f.txt", "rt");
    if(ft == NULL)
    {
        perror("Eroare la deschidere");
        exit(2);
    }

    char linie[100];
    while(fgets(linie, 100, ft) != NULL)
    {
        puts(linie);
    }
    fclose(ft);
    return 0;
}