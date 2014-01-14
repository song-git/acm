/*
 ID: song chen 
 LANG: C
 TASK: beads 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct info {
	char color;
	int count;
};

/* 从p中的序号为idx处开始，计算连续元素颜色相同(含'w')的最大长度
 * p 指向struct info数组首元素的指针
 * n 数组的个数
 * idx 从idx开始计算,函数返回后，idx处存放统计过元素的下一个位置，
 *     这个位置是新的颜色开始位置
 */
int sum(struct info *p, int n, int *idx) 
{
	int i;

	char color = p[*idx].color;
	int sum = 0;
	for(i = *idx; ; i++) {
		if(color == 'w' && p[i%n].color != 'w')
			color = p[i%n].color;

		if( p[i%n].color == color || p[i%n].color == 'w' )
			sum += p[i%n].count;
		else
			break;
	}

	*idx = i--;
	return sum;
}

main () {
	FILE *fin  = fopen ("beads.in", "r");
	FILE *fout = fopen ("beads.out", "w");

	int ret;
	int total;
	char *str = NULL;
	struct info *p = NULL;
	int n = 0;

	fscanf( fin, "%d", &total );
	assert(total > 0);

	str = calloc(1, total);
	assert(str != NULL);

	p = (struct info *) calloc(total, sizeof(struct info));
	assert(p != NULL);

	fscanf(fin, "%s", str);

	int i;
	struct info *ptr = p;
	ptr->color = str[0];
	ptr->count = 1;
	for(i = 1; i < total; i++) {
		if(str[i] == str[i-1] ) {
			ptr->count++;
		} else {
			ptr++;
			ptr->color = str[i];
			ptr->count = 1;
		}
	}

	n = ptr - p + 1;

	if(n <= 2) {
		ret = 0;
		for(i = 0; i < n; i++)
			ret += p[i].count;
	} else {
		ret = 0;
		int temp; 
		for(i = 0; i < n; i++) {
			int idx = i;
			temp = sum(p, n, &idx);
			temp += sum(p, n, &idx);
			if(temp > ret) ret = temp;
		}
	}
	fprintf (fout, "%d\n", ret);

	free(str);
	free(p);
	exit (0);
}
