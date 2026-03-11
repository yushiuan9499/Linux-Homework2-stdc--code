#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GAPS_HOLD 128

struct list_node {
	int val;
	struct list_node *next;
};

#ifdef METHOD_F_S_PTR
struct list_node *middle_node(struct list_node *head)
{
	struct list_node *slow, *fast;
	slow = fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
#else
#ifdef METHOD_COUNTING

struct list_node *middle_node(struct list_node *head)
{
	struct list_node *cur = head;
	int n = 0;
	while (cur) {
		++n;
		cur = cur->next;
	}
	int k = 0;
	cur = head;
	while (k < n / 2) {
		++k;
		cur = cur->next;
	}
	return cur;
}
#endif
#endif

void flush_cache()
{
	const int CHUNK_COUNT = 16;
	const int CHUNK_SIZE = 1024; // 1KB
	unsigned char *chunk[CHUNK_COUNT];
	for (int i = 0; i < CHUNK_COUNT; i++) {
		chunk[i] = malloc(CHUNK_SIZE);
		if (chunk[i]) {
			memset(chunk[i], 0,
			       CHUNK_SIZE); // Write to the chunk to ensure it's loaded into the cache
		}
	}
	for (int i = 0; i < CHUNK_COUNT; i++) {
		free(chunk[i]);
		chunk[i] = NULL;
	}
}

int main()
{
	srand(time(NULL));

	size_t N;
	printf("Enter the length of the linked list: ");
	scanf("%lu", &N);

	/* Allocate list_node and make sure that they are not contiguous in memory. */
	/* Here we use two strategies */
	/* - Between two mallocs, allocate a large block of memory to act as "gap" */
	/* - After allocating, shuffle the pointers */
	struct list_node **arr = malloc(N * sizeof(struct list_node *));
	if (arr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}

	void **gaps = malloc(GAPS_HOLD * sizeof(void *));
	if (gaps == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		free(arr);
		return 1;
	}
	bzero(gaps, GAPS_HOLD * sizeof(void *));

	/* Allocate with gaps */
	for (int i = 0; i < N; i++) {
		/* Allocate a large block of memory to create a gap */
		if (gaps[i % GAPS_HOLD] != NULL) {
			free(gaps[i % GAPS_HOLD]);
		}
		gaps[i % GAPS_HOLD] = malloc(
			(size_t)(rand() + 100)); // Greater than 100 bytes

		arr[i] = malloc(sizeof(struct list_node));
		arr[i]->val = i;
		arr[i]->next = NULL;
	}
	for (int i = 0; i < GAPS_HOLD; i++) {
		if (gaps[i] != NULL) {
			free(gaps[i]);
			gaps[i] = NULL;
		}
	}
	free(gaps);

	/* Shuffle the pointers and create the list*/
	struct list_node *head = NULL;
	struct list_node **current = &head;
	for (int i = N - 1; i >= 0; i--) {
		int idx = rand() % (i + 1);
		*current = arr[idx];
		arr[idx] = arr[i];
		arr[i] = NULL;
		current = &(*current)->next;
	}
	free(arr);

	flush_cache();
	struct list_node *mid_node;
	mid_node = middle_node(head);
	printf("Middle node value: %d\n", mid_node->val);
	for (struct list_node *cur = head; cur != NULL;) {
		struct list_node *next = cur->next;
		free(cur);
		cur = next;
	}
}
