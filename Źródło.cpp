#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"
#define G 9.81
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019
double l=3, m=1;
void rhs_fun(double t, double* tab,double* prawa) //funkcja obliczajaca prawą stronę równania różniczkowego
{
	prawa[0]=tab[1];
	prawa[1]=-G/l*sin(tab[0]);
}
double energia(double a, double w)		//obliczanie energii
{
	double wyn;
	wyn = (0.5 * m * powl(l, 2.)) * powl(w, 2.) + (m * G * l * (1 - cos(a)));
	return wyn;
}
int main()
{
	double h = 0.01;					//Większa dokładność przy mniejszym kroku rożniczkowania
	int n = 2;							//liczba zmiennych (u nas alfa i omega wiec 2)
	double t = 0;						//czas poczatkowy to 0s
	double tk = 6;						//czas koncowy to 6s
	double a0 = 0, w0 = 0;				//zmienne na kąt i prędkość kątową początkowe
	double tabpocz[2], tabkonc[2];	//tabela na kąt i prędkość kątową przed i po obliczeniach
	
	printf("Prosze, podaj warunki poczatkowe wahadla\n");
	printf("Masa kulki [kg]: ");
	scanf("%lf", &m);
	printf("\nDlugosc sznurka[m]: ");
	scanf("%lf", &l);
	while (a0 == 0)						//sprawdzenie warunkow poczatkowych
	{
		printf("\nPodaj wychylenie poczatkowe:(deg, =/= 0!)  ");
		scanf("%lf", &a0);
	}
	
	a0 *= 3.1415/180.0;					//zamiana kątów na radiany
	while (w0 == 0)
	{
		printf("\nPodaj poczatkowa predkosc katowa:(deg/s, =/=0!) ");
		scanf("%lf", &w0);
	}
	
	w0 *= 3.1415 / 180.0;
	tabpocz[0] = a0;
	tabpocz[1] = w0;
	FILE* f = fopen("wyniki.txt", "w");										//otwarcie pliku do zapisu

	fprintf(f, "t\tKat\tPredkosc katowa\tEnergia calkowita\n");				//naglowek pliku z danymi 
	fprintf(f, "%lf\t", t);
	fprintf(f, "%lf\t%lf\t", a0 * 180.0 / 3.1415, w0 * 180.0 / 3.1415);		//zapisywanie do pliku danych początkowych, dane kątowe przeliczone na stopnie dla ułatwienia 
	fprintf(f, "%lf\n", energia(a0, w0));
	while (t < tk)
	{
		vrk4(t, tabpocz, h, n, rhs_fun, tabkonc);												//liczenie prawej strony rownania rozniczkowego metodą Rungego-Kutty
		fprintf(f, "%lf\t", t + h);
		fprintf(f, "%lf\t%lf\t", tabkonc[0]*180.0 / 3.1415,tabkonc[1]*180.0 / 3.1415);		//zapisywanie do pliku poszczególnych wyników 
		fprintf(f, "%lf\n", energia(tabkonc[0], tabkonc[1]));
		for (int i = 0; i < n; i++)																// wyniki jednego kroku różniczkowania staja sie danymi wejsciowymi nastepnego
			tabpocz[i] = tabkonc[i];
		t += h;
	}
	fclose(f);
	return 0;
}