#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLIK_TXT "plik.txt"
#define PLIK_BIN "plik.bin"

#define ROZMIAR 20
#define TAB_ROZM 10

struct Obraz
{
    int rozmiar;
    float przezroczystosc;
    char nazwa[ROZMIAR];
};


/* Ta funkcja wyswietla nam biezaca pozycje w pliku */
void _pozycja(FILE* fp)
{
    printf("Biezaca pozycja w pliku: %ld\n", ftell(fp));
}

void wyswietlenie_zawartosci_pliku_szesnastkowo(char* nazwa_pliku)
{
    printf("Zawartosc pliku szesnastkowo:\n");
    // Zaimplementowac :)
}



/* ============================= OBSLUGA PLIKU TEKSTOWEGO =========================== */

void zapis_pliku_tekstowego(void)
{
    FILE* ft;
    int i=5;
    char napis[] = "Tekst z tablicy napis\n";

    if ((ft=fopen(PLIK_TXT, "w"))!=NULL)    // otwieram plik w trybie zapisu tekstowego; jesli plik istnieje, to jego zawartosc jest tracona. Ta operacja moze sie nie udac - kiedy?
    {
        printf("Utworzono plik tekstowy %s\n", PLIK_TXT);

        // Mozemy korzystac z odpowiednika znanej juz funkcji printf - dokladnie w taki sam sposob podajac jako pierwszy argument wskaznik na plik
        fprintf(stdout, "Druga linijka tekstu, zmienna i=%d\n", i++);           // Plikiem moze byc stabdardowe wyjscie (zazwyczaj ekran)
        fprintf(ft, "%d %f %c\n", i++, 3.12345, 'c');                           // Zapisywac mozemy wartosci roznych typow
        fprintf(ft, "Druga linijka tekstu, zmienna i=%d, nazwa pliku=%s\n", i++, PLIK_TXT);   // Plikiem moze byc otwarty wczesniej plik dyskowy

        fputs(napis, ft);           // Tak tez mozemy zapisac do pliku lancuch znakow
        fputc(napis[1], ft);        // Ta funkcja zapisuje jeden znak
        fputc('\n', ft);            // Znak mozna podac wprost

        for(i='a'; i<='z'; i++)     // Wypisujemy caly alfabet do pliku
            fputc(i, ft);
        fputc('\n', ft);            // Nowa linia

        fclose(ft);
    }
    else
    {
        printf("Plik nie zostal utworzony plik %s.\n", PLIK_TXT);
    }
}



void odczyt_pliku_tekstowego(void)
{
    FILE* fu;
    int i;
    float j;
    char c;
    char tablica[100];

    if ((fu=fopen(PLIK_TXT, "r"))!=NULL)    // Probuje otworzyc plik w trybie tekstowym do odczytu - ta operacja moze sie nie udac. Kiedy?
    {
        fprintf(stdout, "Otwarto plik %s w trybie odczytu tekstowego.\n", PLIK_TXT);  // W taki sposob rowniez mozna wyswietlac informacje w konsoli
        _pozycja(fu);

        fscanf(fu, "%d %f %c", &i, &j, &c);     // Za pomoca fscanf mozna wczytywac i od razu parsowac wartosci z pliku - analogicznie jak za pomoca funkcji scanf()
        printf("Wczytalem wartosci z pliku: i=%d j=%f c=%c\n", i, j, c);
        _pozycja(fu);

        c = fgetc(fu);      // Wczytuje z pliku jeden znak - Sprawdzic w debugerze, co to jest za znak!
        _pozycja(fu);

        fgets(tablica, sizeof(tablica), fu);    // Wczytanie z pliku pelnej linijki tekstu do wskazanej tablicy, ale nie wiecej niz podana liczba znakow
                                                // sizeof(tablica) - to nas zabezpiecza przed przekroczeniem tablicy
        printf("Wczytalem linijke z pliku: %s", tablica);   // Wczytany lancuch juz zawiera znak konca wiersza

        c = fgetc(fu);
        printf("Wczytalem znak z pliku: %c\n", c);

        // Sprawdzmy, na ktorej pozycji w pliku znajdujemy sie teraz:
        _pozycja(fu);
        rewind(fu);     // Przesuwamy wskaznik na poczatek pliku
        _pozycja(fu);

        fseek(fu, 0, SEEK_END);     // Przesuwam wskaznik na koniec pliku
        _pozycja(fu);               // Biezaca pozycja wskazuje nam przy okazji na rozmiar pliku w bajtach

        fseek(fu, -20, SEEK_END);   // Przesuwam wskaznik na 20 znak od konca pliku
        while(!feof(fu))            // Ta petla wyswietla wszystkie znaki od biezacej pozycji do konca pliku
            printf("%c", fgetc(fu));

        fclose(fu);
    }
    else
    {
        printf("Nie moge odczytac pliku %s!\n", PLIK_TXT);
    }
}



/* ============================= OBSLUGA PLIKU BINARNEGO =========================== */

void zapis_pliku_binarnego(void)
{
    char c='a';
    int i=5;
    float f=3.12345;
    FILE* fb;
    struct Obraz obr;
    struct Obraz tablica[] = {
        { -5, 1.0, "samolot.jpg"},
        { 0, 0.4, "kot.jpg"},
        { 2, 0.7, "pilka.jpg"},
        { 64, 0.123456, "kanapka.jpg"},
        { 123, 0.0, "browar.jpg"},
    };

    if ((fb=fopen(PLIK_BIN, "wb"))!=NULL)
    {
        printf("Utworzono plik binarny %s\n", PLIK_BIN);

        // W pliku binarnym mozna przechowywac wartosci dowolnych typow, w dowolnej kolejnosci - wazne, aby pozniej podczas wczytywac dane dokladnie w tej samej kolejnosci!

        fputc(c, fb);   // Zapis jednego bajta do pliku
        fputc(97, fb);  // To robimy to samo, ale wartosc bajta podana jest "na sztywno"
        fwrite(&c, sizeof(c), 1, fb);   // Zapisuje do pliku fb spod adresu &c jeden element o rozmiarze sizeof(c) - czyli jeden bajt

        fwrite(&i, sizeof(i), 1, fb);   // Zapisuje do pliku fb zawartosc zmiennej i
        //UWAGA: funkcja fwrite() zapisuje binarna reprezentacje danych a nie lancuch znakow

        fwrite(&f, sizeof(f), 1, fb);   // Zapisuje do pliku fb zawartosc zmiennej f

        // Plik binarny bardzo dobrze nadaje sie do przechowywania danych umieszczonych w strukturach
        strcpy(obr.nazwa, "pierwszy.jpg");
        obr.przezroczystosc = 1.0;
        obr.rozmiar = 512;
        fwrite(&obr, sizeof(obr), 1, fb);

        //fwrite(tablica, sizeof(tablica), 1, fb);          // Tak zapisujemy zawartosci calej tablicy struktur do pliku
        fwrite(tablica, sizeof(struct Obraz), sizeof(tablica)/sizeof(struct Obraz), fb);    // Tak tez zapisujemy zawartosc calej tablicy, ale elegancko :)

        fclose(fb);     // Nalezy zamknac plik po zakonczonej pracy
    }
    else
    {
        printf("Nie moge zapisac pliku %s\n", PLIK_BIN);
    }
}



void odczyt_pliku_binarnego()
{
    unsigned char c;
    int i, j;
    float f;
    FILE* fc;
    struct Obraz tablica[TAB_ROZM];

    if ((fc=fopen(PLIK_BIN, "rb"))!=NULL)
    {
        printf("Otwarto plik %s w trybie odczytu binarnego.\n", PLIK_BIN);
        _pozycja(fc);

        c=fgetc(fc);    // Wczytuje jeden bajt z pliku
        printf("Wczytalem 1 bajt, dziesietnie=%d szesnastkowo=%02x znak=%c", c, c, c);

        c='x';  // kasuje poprzednia wartosc - dla jasnosci sytuacji
        fread(&c, sizeof(char), 1, fc);     // Wczytuje z pliku jeden bajt
        printf("Wczytalem znak: %c\n",c);
        _pozycja(fc);

        fseek(fc, 3, SEEK_SET);     // Ustawiam wskaznik na trzeci bajt w pliku - ten, od ktorego zaczyna sie liczba integer
        _pozycja(fc);

        fread(&i, sizeof(int), 1, fc);      // Wczytuje liczbe calkowita. Sprawdzic, co sie stanie, jesli miejscami zamieniona zostanie linijka ta z nastepna
        fread(&f, sizeof(float), 1, fc);
        printf("Wczytalem wartosci: i=%d, f=%f\n", i, f);
        _pozycja(fc);

        // Struktury wczytuje sie bardzo latwo
        i=0;
        while(!feof(fc) && i<TAB_ROZM)      // wczyujemy po jednej strukturze z pliku do tablicy az do: konca pliku LUB konca miejsca w tablicy (w zaleznosci od tego, co wystapi wczesniej)
            fread(&tablica[i++], sizeof(struct Obraz), 1, fc);
        _pozycja(fc);

        // Wyswietlam zawartosc tablicy
        i--;
        while(i-->0)
            printf("[%d] %s rozmiar=%d przezr=%f\n", i, tablica[i].nazwa, tablica[i].rozmiar, tablica[i].przezroczystosc);
    }
    else
    {
        printf("Nie moge otworzyc pliku %s\n", PLIK_BIN);
    }
}



int main()
{
    printf("---------- PLIK TEKSTOWY ----------\n");

    zapis_pliku_tekstowego();
    odczyt_pliku_tekstowego();

    printf("---------- PLIK BINARNY -----------\n");

    zapis_pliku_binarnego();
    odczyt_pliku_binarnego();

    wyswietlenie_zawartosci_pliku_szesnastkowo(PLIK_TXT);
    wyswietlenie_zawartosci_pliku_szesnastkowo(PLIK_BIN);

    return 0;
}
