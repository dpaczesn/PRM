/* lista.c - M. Niewinski for PROE 2017L */

#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR 80

struct ElementListy
   {
   int przykladowePoleElementu;
   struct ElementListy *nastepnyElementListy;
   };

typedef struct ElementListy * WskaznikNaElementListy;
typedef enum {FALSZ, PRAWDA} Bool;

/*funkcja dodaje nowy element na poczatek listy i jako wynik zwraca wskaznik do niego*/
WskaznikNaElementListy dodanieNowegoElementuListy(WskaznikNaElementListy pierwszyElementListy, int wartoscPola);
/*funcja usuwa pierwszy element dla ktorego przykladowePoleElementu==wartoscPola*/
WskaznikNaElementListy usuniecieElementuListy(WskaznikNaElementListy pierwszyElementListy, int wartoscPola);
WskaznikNaElementListy zwolnieniePamieciListy(WskaznikNaElementListy pierwszyElementListy);
void wyswietlenieElementowListy(WskaznikNaElementListy pierwszyElementListy);
Bool czyListaJestPusta(WskaznikNaElementListy pierwszyElementListy);
void wyswietlenieMenuUzytkownika(WskaznikNaElementListy pierwszyElementListy);
char odczytWyboruMenuUzytkownika(void);
Bool odczytDanychOdUzytkownika(char * tekstKomunikatu, int * wskaznikDoDanych);

int main(void)
	{
	WskaznikNaElementListy pierwszyElementListy = NULL;
	char wybranaOpcjaMenu;
	int tymczasowaWartosc;
	for(;;)
		{
		wyswietlenieMenuUzytkownika(pierwszyElementListy);
		wybranaOpcjaMenu=odczytWyboruMenuUzytkownika();
		switch(wybranaOpcjaMenu)
			 {
			 case 'd': /*dodawanie elementu*/
				if (odczytDanychOdUzytkownika("\nPodaj wartosc pola dana:", &tymczasowaWartosc ))
					 pierwszyElementListy=dodanieNowegoElementuListy(pierwszyElementListy,tymczasowaWartosc );
			    break;
			 case 'w': /*wyswietlanie elementow*/
			    wyswietlenieElementowListy(pierwszyElementListy);
			    break;
			 case 'u': /*usuwanie elementu o zadanej wartosci pola: przykladowePoleElementu*/
				if (odczytDanychOdUzytkownika("\nWprowadz wartosc pola elementu do usuniecia: ", &tymczasowaWartosc ))
					 pierwszyElementListy=usuniecieElementuListy(pierwszyElementListy,tymczasowaWartosc);
				break;
			 case 'q':
				pierwszyElementListy=zwolnieniePamieciListy(pierwszyElementListy);
			    exit(0);
			    break;
			 default:
			    puts("\nBledny wybor opcji menu!");
			 }
		}
	return 0;
	}

WskaznikNaElementListy dodanieNowegoElementuListy(WskaznikNaElementListy pierwszyElementListy, int wartoscPola)
   {
   WskaznikNaElementListy nowyElementListy= (WskaznikNaElementListy)malloc( sizeof(struct ElementListy) );
   if(nowyElementListy==NULL)
      {
      fputs("Blad alokacji pamieci",stderr);
      exit(1);
      }
   nowyElementListy->przykladowePoleElementu=wartoscPola;
   nowyElementListy->nastepnyElementListy = pierwszyElementListy;
   return nowyElementListy;
   }

void wyswietlenieElementowListy(WskaznikNaElementListy pierwszyElementListy)
   {
	WskaznikNaElementListy biezacyElementListy=pierwszyElementListy;
	unsigned licznikElementow=1;
	do
    	{
		printf("Element %d Dane: %d\n",licznikElementow++, biezacyElementListy->przykladowePoleElementu );
		biezacyElementListy = biezacyElementListy->nastepnyElementListy;
    	} while(biezacyElementListy != NULL);
   }

WskaznikNaElementListy usuniecieElementuListy(WskaznikNaElementListy pierwszyElementListy, int wartoscPola)
   {
	WskaznikNaElementListy biezacyElementListy=pierwszyElementListy, poprzedniElementListy=NULL;
	do
		{
        if( biezacyElementListy->przykladowePoleElementu==wartoscPola)
        	{
        	if(biezacyElementListy==pierwszyElementListy) pierwszyElementListy = biezacyElementListy->nastepnyElementListy;
        	else poprzedniElementListy->nastepnyElementListy = biezacyElementListy->nastepnyElementListy;
        	free(biezacyElementListy);
        	return pierwszyElementListy;
        	}
        poprzedniElementListy = biezacyElementListy;
        biezacyElementListy = biezacyElementListy->nastepnyElementListy;
		} while(biezacyElementListy != NULL);
	printf("Element z polem o zadanej wartosci nie znajduje sie na liscie\n");
	return pierwszyElementListy;
   }

WskaznikNaElementListy zwolnieniePamieciListy(WskaznikNaElementListy pierwszyElementListy)
   {
   WskaznikNaElementListy biezacyElementListy=pierwszyElementListy, tymczasowyWskaznik;
   do
      {
      tymczasowyWskaznik = biezacyElementListy;
      biezacyElementListy = biezacyElementListy->nastepnyElementListy;
      free(tymczasowyWskaznik);
      } while(biezacyElementListy != NULL);
   return NULL;
   }

Bool czyListaJestPusta(WskaznikNaElementListy pierwszyElementListy)
	{
	if (pierwszyElementListy == NULL) return PRAWDA;
	else return FALSZ;
	}

void wyswietlenieMenuUzytkownika(WskaznikNaElementListy pierwszyElementListy)
	{
	 printf("Prosze wybrać opcje:\n");
	 printf("\n\t'd'- dodanie nowego elementu do listy");
	 if (!czyListaJestPusta(pierwszyElementListy))
	 	 {
		 printf("\n\t'w'- wyswietlenie wszystkich elementow listy");
		 printf("\n\t'u'- usuniecie elementu z listy,");
		 }
     printf("\n\t'q'- wyjscie z programu");
     printf("\n\t >");
	}

char odczytWyboruMenuUzytkownika(void)
	{
	char znak, wybranaOpcja[2];
	fgets(wybranaOpcja,2,stdin);
	while((znak=getchar())!='\n');
	return wybranaOpcja[0];
	}

Bool odczytDanychOdUzytkownika(char * tekstKomunikatu, int * wskaznikDoDanych)
	{
	char buforDlaDanych[ROZMIAR];
	int wynikKonwersji;
	printf("%s",tekstKomunikatu);
	fgets(buforDlaDanych,ROZMIAR,stdin);
	wynikKonwersji=sscanf(buforDlaDanych,"%d",wskaznikDoDanych);
	if (wynikKonwersji==EOF) return FALSZ;
	else return PRAWDA;
	}
