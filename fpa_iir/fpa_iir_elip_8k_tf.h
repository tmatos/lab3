/*
 * Com os coeficientes da funcao de tranferencia
 * para implementar na FD II
 * 
 * Filtro de ordem 7
 * 
 * Obtido dos coeficientes originais por meio de:
 * a = round(a * 1200)
 * b = round(b * 1200)
 * 
 */
 
 ///// NAO USE, INSTAVEL!!!!  //////
 
#define N 8

Int16 B[N] = { 581, -3940, 11573, -19087,
	           19087, -11573, 3940, -581 };

Int16 A[N] = { 1200, -6440, 15182, -20279,
	           16526, -8190, 2276, -271 };
