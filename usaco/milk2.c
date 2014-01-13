/*
ID: song chen
LANG: C
TASK: milk2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct space {
	int min;
	int max;

	struct space *prev;
	struct space *next;
};

inline int space_cross(struct space s1, struct space s2) 
{
	if( (   s1.min >= s2.min && s1.min <= s2.max) || 
			(s1.max >= s2.min && s1.max <= s2.max) ||
			(s2.min >= s1.min && s2.min <= s1.max ) ||
			(s2.max >= s1.min && s2.max <= s1.max )
	  ) {
		return 1;
	} else {
		return 0;
	}
}

inline int merge_space(struct space *s1, struct space *s2) 
{
	if( space_cross(*s1, *s2) ) {
		s1->min = s1->min < s2->min ? s1->min : s2->min;
		s1->max = s1->max > s2->max ? s1->max : s2->max;
		return 1;
	} else {
		return 0;
	}
}

/* 
 * 将s2添加到s1的前面
 */
inline void add_before(struct space *s1, struct space *s2)
{
	assert(s1 != NULL);

	if(s2 == NULL) 
		assert(s1->prev == NULL);

	struct space *temp = s1->prev;

	s1->prev = s2;

	if(s2) {
		s2->next = s1;
		s2->prev = temp;
	}

	if(temp) {
		temp->next = s2;
	}
}

/*
 * 将s2添加到s1的后面
 */
inline void add_after(struct space *s1, struct space *s2) 
{
	assert(s1 != NULL);

	if(s2 == NULL)
		assert(s1->next == NULL); // 防止断裂

	struct space *temp = s1->next;

	s1->next = s2;

	if(s2) {
		s2->prev = s1;
		s2->next = temp;
	}

	if(temp) {
		temp->prev = s2;
	}
}


/* 将item合并到plist中，空间重合则进行合并，空间完全不重合则添加
 * 合并后要重新与前后节点进行合并
 */
void merge(struct space **plist, struct space *item)
{
	if(plist == NULL || item == NULL) return;

	if(*plist == NULL) {
	   	*plist = item;
		return;
	} else {
		struct space *ptr = NULL;
		struct space *temp = NULL;
		for(ptr = *plist; ptr != NULL;) {
			if( merge_space(ptr, item) ) {

				struct space *tt = ptr;
				while( tt != NULL ) {
					if( tt->prev != NULL && merge_space(tt, tt->prev) ) {
						temp = tt->prev;
						tt->prev = temp->prev;

						if(temp->prev != NULL) temp->prev->next = tt;

						free(temp);
					} else {
						break;
					}
				}

				tt = ptr;
				while( tt != NULL ) {

					if( tt->next != NULL && merge_space(tt, tt->next) ) {
						temp = tt->next;
						tt->next = temp->next;

						if(temp->next != NULL) temp->next->prev = tt;

						free(temp);
					} else {
						break;
					}
				}

				free(item);
				return;
			} else {
				ptr = ptr->next;
			}
		}

		// 没有合并上 插入
		for(ptr = *plist; ptr != NULL; ptr = ptr->next) {
			if( item->max <= ptr->min ) {
				if( ptr->prev == NULL || ptr->prev->max <= item->min ) {
					// insert
					temp = ptr->prev;
					ptr->prev = item;
					item->next = ptr;
					item->prev = temp;
					if(temp != NULL) {
						temp->next = item;
					}

					*plist = item;
					return;
				} else {
					continue;
				}
			} else if(item->min >= ptr->max) {
				if( ptr->next == NULL || ptr->next->min >= item->max ) {
					// insert
					temp = ptr->next;
					ptr->next = item;
					item->prev = ptr;
					item->next = temp;
					if(temp != NULL) {
						temp->prev = item;
					}
					return;
				} else {
					continue;
				}
			} else {
				assert(0);
			}	

		}

		assert(0);
	}
}

int main()
{
	FILE *fin, *fout;
	fin = fopen("milk2.in", "r");
	fout = fopen("milk2.out", "w");
	assert(fin != NULL && fout != NULL);

	int farmers;
	fscanf(fin, "%d", &farmers);

	assert(farmers >= 1 && farmers <= 5000);

	struct space *p_milking = NULL;
	
	int i;
	for(i = 0; i < farmers; i ++) {
		struct space *temp = calloc(1, sizeof(struct space));

		fscanf(fin, "%d %d", &(temp->min), &(temp->max));
		assert(temp->max >= temp->min);

		merge(&p_milking, temp);
	}

	int max_m = 0, max_i = 0;
	struct space *ptr;
	for( ptr = p_milking; ptr != NULL; ptr = ptr->next ) {
		int idle = 0; 
		if(ptr->prev != NULL) {
			idle = (ptr->min - ptr->prev->max);
		} 

		if(max_i < idle) 
			max_i = idle;
		
		if(max_m < (ptr->max - ptr->min) )
			max_m = (ptr->max - ptr->min);
	}

	fprintf(fout, "%d %d\n", max_m, max_i);

	exit(0);
}
