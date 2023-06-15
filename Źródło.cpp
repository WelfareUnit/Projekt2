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
	double h = 0.001;					//Większa dokładność,przydatna szczególnie w niestandardowych zestawach danych ale moze troche przesadzilem
	int n = 2;							//liczba zmiennych (u nas alfa i omega wiec 2)
	double t = 0;						//czas poczatkowy to 0s
	double tk = 6;						//czas koncowy to 6s
	double a0 = 0, w0 = 0;				//zmienne na kąt i prędkość kątową początkowe
	double danepocz[2], danekonc[2];	//tabela na kąt i prędkość kątową przed i po obliczeniach
	FILE* f = fopen("wyniki.txt", "w");
	printf("Proszę, podaj  wahadla\n");
	printf("Masa kulki [kg]: ");
	scanf("%lf", &m);
	printf("\nDlugosc sznurka[m]: ");
	scanf("%lf", &l);
	printf("\nPodaj wychylenie początkowe:(deg) ");
	scanf("%lf",&a0);
	a0 *= 3.1415/180.0;					//zamiana kątów na radiany
	printf("\nPodaj poczatkowa predkosc katowa:(deg/s) ");
	scanf("%lf",&w0);
	w0 *= 3.1415 / 180.0;
	danepocz[0] = a0;
	danepocz[1] = w0;
	fprintf(f, "t\tKąt\tPrędkość kątowa\tEnergia całkowita\n");		//naglowek pliku
	while (t < tk)
	{
		fprintf(f, "%lf\t", t + h);
		vrk4(t, danepocz, h, n, rhs_fun, danekonc);												//liczenie prawej strony rownania rozniczkowego metodą Rungego-Kutty
		fprintf(f, "%lf\t%lf\t", danekonc[0]*180.0 / 3.1415,danekonc[1]*180.0 / 3.1415);		//zapisywanie do pliku, dane kątowe przeliczone na stopnie
		fprintf(f, "%lf\n", energia(danekonc[0], danekonc[1]));
		for (int i = 0; i < n; i++)																// wyniki jednego kroku calkowania staja sie danymi wejsciowymi nastepnego
			danepocz[i] = danekonc[i];
		t += h;
	}
	fclose(f);
	return 0;
}