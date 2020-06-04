#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define G 9.81
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019
double ro, s, c,m,l,v0;
void rhs_fun(int t, double* tab,double* prawa)
{
	prawa[0] = tab[1];
	//prawa[1] = 
}

int main()
{
	double danepocz[3], danekonc[3];
	printf("Podaj teraz warunki poczatkowe wahadla\n");
	printf("Masa ciezarka:  ");
	scanf("%lf", &m);
	printf("\nPowierzchnia (m^2): ");
	scanf("%lf", &s);
	printf("\nStala opornosci pow.: ");
	scanf("%lf", &c);
	printf("\nDlugosc sznurka:\t");
	scanf("%lf", &l);
	printf("\nV0 dmuchawy: ");
	scanf("%lf", &v0);

	return 0;
}