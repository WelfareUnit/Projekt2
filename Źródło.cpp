#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"
#define G 9.81
#define C 0.33
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019
double ro=1.1, s=2,m=50,l=3,v0=10;
void rhs_fun(double t, double* tab,double* prawa)//funkcja obliczajaca prawą stronę równania różniczkowego
{
	long double Vox, Voy;
	Vox = tab[1] * l * cos(tab[0]);
	Voy= tab[1] * l * sin(tab[0]);
	long double VoD2 = powl(-Vox + v0 * sin(t), 2.) + powl(Voy, 2.);		//Kwadrat prędkości wzgl. powietrza
	long double VodprY2 = powl(v0 * sin(t) * sin(tab[0]), 2.);				//kwadrat składowej ↑ stycznej  do toru ruchu
	prawa[0] = tab[1];
	prawa[1] = (ro/2*(VoD2-VodprY2)*s*C-m*G*sin(tab[0])) / (m * l);
	printf("");
}
double energia(double a, double w)		//obliczanie energii
{
	double wyn;
	wyn = (0.5 * m * powl(l, 2.)) * powl(w, 2.) + (m * G * l * (1 - cos(a)));
	return wyn;
}
int main()
{
	double h = 0.0001;					//Większa dokładność,przydatna szczególnie w niestandardowych zestawach danych
	int n = 2;
	double t = 0;
	double tk = 9;
	double danepocz[2], danekonc[2];
	FILE* f = fopen("wyniki.txt", "w");
	printf("Podaj teraz warunki poczatkowe wahadla\n");
	printf("Masa ciezarka[kg]:  ");
	scanf("%lf", &m);
	printf("\nPowierzchnia [m^2]: ");
	scanf("%lf", &s);
	printf("\nDlugosc sznurka[m]:\t");
	scanf("%lf", &l);
	printf("\nV0 dmuchawy[m/s]: ");
	scanf("%lf", &v0);
	
	
	danepocz[0] = 0;
	danepocz[1] = 0;
	fprintf(f, "t\tAlfa\tomega\tenergia\n");
	while (t < tk)
	{
		fprintf(f, "%lf\t", t + h);
		
		vrk4(t, danepocz, h, n, rhs_fun, danekonc);		//liczenie metodą Rungego-Kutty
		fprintf(f, "%lf\t%lf\t", danekonc[0],danekonc[1]);		//zapisywanie do pliku
		fprintf(f, "%lf\n", energia(danekonc[0], danekonc[1]));
		for (int i = 0; i < n; i++)			// wyniki jednego kroku staja sie danymi wejsciowymi nastepnego
		{
			danepocz[i] = danekonc[i];
		}

		t += h;
		
	}
	fclose(f);
	return 0;
}