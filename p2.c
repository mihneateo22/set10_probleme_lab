#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    unsigned int flag, n, i, nr_caractere = 0;
    char s[256], linie[256], sep[] = " \n", *p;
    printf("Introduceti 1, 2, 3 sau 4 : # (subpunct a) = 1, subpunct b) = 2, ...) : ");
    scanf("%u", &flag);
    getchar();

    FILE *f_input = fopen("p2_f.txt", "wt");
    if(f_input == NULL)
    {
        perror("Eroare la citire");
        exit(1);
    }

    printf("\nIntroduceti numarul de propozitii de citit : ");
    scanf("%u", &n);
    getchar();
    for(i = 0; i < n; i++)
    {
        printf("propozitia %u : ", i + 1);
        fgets(s, 256, stdin);
        s[strcspn(s, "\n")] = '\0';
        fputs(s, f_input);
        fputs("\n", f_input);
    }
    fclose(f_input);

    f_input = fopen("p2_f.txt", "rt");
    if(f_input == NULL)
    {
        perror("Eroare la deschidere");
        exit(2);
    }

    switch(flag)
    {
        case 1 :
        {
            while(fgets(linie, sizeof(linie), f_input) != NULL)
                printf("%s", linie);
            fclose(f_input);
            break;
        }
        case 2 :
        {
            char cuvant[256];
            unsigned int numar_linie = 1, cnt;
            printf("Introduceti cuvantul de cautat : ");
            fgets(cuvant, 256, stdin);
            cuvant[strcspn(cuvant, "\n")] = '\0';

            while(fgets(linie, 256, f_input) != NULL)
            {
                cnt = 0;
                p = strtok(linie, sep);
                while(p != NULL)
                {
                    if(strcmp(cuvant, p) == 0 && cnt == 0)
                    {
                        cnt = 1;
                        printf("%d ", numar_linie);
                    }
                    p = strtok(NULL, sep);
                }
                numar_linie++;
            }
            printf("\n");
            fclose(f_input);
            break;
        }
        case 3 : 
        {
            int nr_cuv = 0;

            //numarul de cuvinte;
            while(fgets(linie, 256, f_input) != NULL)
            {
                nr_caractere += strlen(linie);
                p = strtok(linie, sep);
                while(p != NULL)
                {
                    nr_cuv++;
                    p = strtok(NULL, sep);
                }
            }
            printf("numarul de cuvinte din acest fisier este : %u\n", nr_cuv);
            printf("numarul de caractere din acest fisier : %u\n", nr_caractere);
            fclose(f_input);
            break;
        }
        case 4 : 
        {
            unsigned int maxi_carac_linie = 0, maxim[10];
            while(fgets(linie, 256, f_input) != NULL)
            {
                nr_caractere = strlen(linie);
                if(nr_caractere > maxi_carac_linie)
                {
                    maxi_carac_linie = nr_caractere;
                }
            }

            printf("\nliniile de lungime maxima : ");

            rewind(f_input); // te duce la inceputul fisierului
            i = 1;
            while(fgets(linie, 256, f_input) != NULL)
            {
                if(maxi_carac_linie == strlen(linie))
                    printf("%u ", i);
                i++;
            }
            fclose(f_input);
            break;
        }
        default :
            printf("Nu ai introdus o varianta valida!\n");
            fclose(f_input);
            break;
    }
    return 0;
}