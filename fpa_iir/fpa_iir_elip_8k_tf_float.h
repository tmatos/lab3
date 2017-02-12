/*
 * Com os coeficientes da funcao de tranferencia
 * para implementar na FD II
 * 
 * Filtro de ordem 7
 * 
 */
 
#define N 8

double B[N] = { 0.4843, -3.2835, 9.6445, -15.9059, 15.9059, -9.6445, 3.2835, -0.4843 };

double A[N] = { 0.0000, -5.3666, 12.6514, -16.8995, 13.7713, -6.8246, 1.8970, -0.2262 };
