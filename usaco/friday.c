/*
 ID: song chen 
 LANG: C
 TASK: friday 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int days_per_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

inline int leap_year(int year) {
	if(year % 100 == 0) {
		return ( ( year % 400 == 0 ) ? 1 : 0 );
	} else {
		return ( ( year % 4 == 0 ) ? 1 : 0 );
	}
}

inline int dom(int y, int m) 
{
	if( m == 1 )
		return days_per_month[m] + leap_year(y);
	else
		return days_per_month[m];
}

main () {
	FILE *fin  = fopen ("friday.in", "r");
	FILE *fout = fopen ("friday.out", "w");
	
	// sat sun mon tue ... fri
	unsigned days[7] = {0,0,0,0,0,0,0};
	
	unsigned n;
	fscanf(fin, "%u", &n);
	assert(n <= 400);

	int dow = ( 12 % 7 + 2 ) % 7;

	unsigned i = 0, j = 0;
	for(i = 0; i < n; i++) { // n years
		for(j = 0; j < 12; j++) { // each month for n years
			days[dow] ++;
			dow = (dow + dom(1900 + i, j)) % 7;
		}

	}

	for(i = 0; i < 7; i++) {
		if( i>0 ) fprintf (fout, " ");
		fprintf (fout, "%u", days[i]);
	}

	fprintf(fout, "\n");
	exit (0);
}

