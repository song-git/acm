/*
 ID: song chen
 LANG: C
 TASK: gift1
 */

#define MAX_NAME_LEN 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct info {
	char name[MAX_NAME_LEN];
	int money;
};

main () {
	FILE *fin  = fopen ("gift1.in", "r");
	FILE *fout = fopen ("gift1.out", "w");

	size_t num;
	fscanf(fin, "%u", &num);
	assert(num > 0 && num < 1024);

	struct info *p = (struct info *) calloc(num, sizeof(struct info));
	assert(p != NULL);
	
	size_t i; 
	for(i=0; i < num; i++) {
		fscanf(fin, "%s", p[i].name);
		p[i].money = 0;
	}

	char temp[MAX_NAME_LEN];
	int my=0,pp=0;
	for(i = 0; i < num; i++) {
		fscanf(fin, "%s", temp);
		fscanf(fin, "%d %d", &my, &pp);
		if(pp == 0) continue;
		int mm = my / pp;
		size_t k;

		for(k = 0; k < num; k ++) {
			if( strcmp(p[k].name, temp)  == 0 ) {
				p[k].money -= mm * pp;
				break;
			}
		}

		int j;
		for(j = 0; j < pp; j++) {
			fscanf(fin, "%s", temp);
			for(k=0; k < num; k++) {
				if( strcmp(p[k].name, temp)  == 0 ) {
					p[k].money += mm;
					break;
				}
			}
		}
	}

	for(i = 0; i < num; i++) {
		fprintf (fout, "%s %d\n", p[i].name, p[i].money);
	}


	free(p);
	exit (0);
}
