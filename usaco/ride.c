/*
 ID: song chen
 LANG: C
 TASK: ride
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

main () {

	FILE *fin  = fopen ("ride.in", "r");
	FILE *fout = fopen ("ride.out", "w");
	
	char str1[7] = {0};
	char str2[7] = {0};

	fscanf (fin, "%s", str1);
	fscanf (fin, "%s", str2);
	
	int n1 = 1, n2 = 1, idx;
	for(idx = 0; str1[idx] != 0; idx++)
		n1 *= str1[idx] - 'A' + 1;

	for(idx = 0; str2[idx] != 0; idx++)
		n2 *= str2[idx] - 'A' + 1;

	if(n1 % 47 == n2 % 47)
		fprintf (fout, "GO\n");
	else
		fprintf (fout, "STAY\n");

	exit (0);
}
