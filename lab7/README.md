# PRM, laboratorium 7, semestr letni 2016/2017

----------------------------------------------

*Zakres materiału*: Złożone struktury danych - lista jednokierunkowa. . (__5 pkt__)

----------------------------------------------

## __Zadanie 1.__ Złożone struktury danych - lista jednokierunkowa. .

1. W katalogu `prm7` stworzyć nowy projekt `zad1` i do głównego pliku projektu skopiować zawartość pliku źródłowego [zad1.c](zad1.c)
2. Przeanalizować kod źródłowy programu, w szczególności zapoznając się z funkcjami: `dodanieNowegoElementuListy`, `usuniecieElementuListy`, `usuniecieElementuListy` i `zwolnieniePamieciListy`.
3. Skompilować i uruchomić program a następnie przśledzić jego sposób działania.
4. Zmienić kod programu:
  1. dodając funkcję o sygnaturze `unsigned int liczbaElementówListy(WskaznikNaElementListy pierwszyElementListy)`, która w wyniku swego działania zwraca informację o liczbie elementów na liście,
  2. zmodyfikować funkję `wyswietlenieMenuUzytkownika` i `main` w taki sposób by można było sprawdzić poprawność implementacji funkcji `liczbaElementówListy`,
  3. zmodyfikiwać funkję `dodanieNowegoElementuListy` w taki sposób by nowy element listy był dodawany na jej końcu i sprawwdzić poprawność jej działania.
