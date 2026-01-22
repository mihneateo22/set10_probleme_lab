#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *f_input;
    char s[256], sep[] = " ", *p, cs[256];
    int flag, c, i, first = 0;
    f_input = fopen("p1_f.txt", "wt");
    if(f_input == NULL)
    {
        perror("Nu s-a putut deschide fisierul!\n");
        exit(1);
    }
    printf("Un sir de caractere : ");
    fgets(s, 256, stdin);
    s[strcspn(s, "\n")] = '\0';

    printf("Introdu cifra 1, 2, 3 sau 4. # (1 este pentru scriere directa, 2 pentru scriere caracter cu caracter, 3 pentru cuvant cu cuvant pe o singura linie, iar 4 pentru cuvant cu cuvant pe linii diferite, cate un cuvant pe fiecare linie) : ");
    scanf("%d", &flag);    
    switch(flag)
    {
        case 1 :
            printf("\nAceasta este scrierea dintr-o bucata!\n\n");
            fputs(s, f_input);
            break;
        case 2 :
            printf("\nAceasta este scrierea caracter cu caracter!\n\n");
            i = 0;
            while(s[i] != '\0')
            {
                fputc(s[i], f_input);
                i++;
            }
            break;
        case 3 :
            printf("\nAceasta este scrierea cuvant cuvant, pe o singura linie!\n\n");
            strcpy(cs, s);
            p = strtok(cs, sep);
            fputs(p, f_input);
            p = strtok(NULL, sep);
            while(p != NULL)
            {
                fputs(" ", f_input);
                fputs(p, f_input);
                p = strtok(NULL, sep);
            }
            break;
        case 4 :
            printf("\nAceasta este scrierea cuvant cu cuvant, cate un cuvant pe linie\n\n");
            strcpy(cs, s);
            p = strtok(cs, sep);
            fputs(p, f_input);
            p = strtok(NULL, sep);
            while(p != NULL)
            {
                fputs("\n", f_input);
                fputs(p, f_input);
                p = strtok(NULL, sep);
            }
            break;
        default :
            printf("Nu ati tastat o varianta valida!");
            break;
    }
    fclose(f_input);
    return 0;
}