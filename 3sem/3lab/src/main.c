#include "fibheap.h"

int main()
{
	fibheap *root = make_fibheap();
	root = fibheap_insert(root, 1);
	root = fibheap_insert(root, 2);
	root = fibheap_insert(root, 3);
	root = fibheap_insert(root, 4);
	root = fibheap_insert(root, 5);
	root = fibheap_insert(root, 6);
	root = fibheap_insert(root, 7);
	root = fibheap_insert(root, 8);
	root = fibheap_insert(root, 9);
	root = fibheap_insert(root, 0);
	root = fibheap_insert(root, 10);
	root = fibheap_insert(root, 11);
	fibheap_print(root->min);

	printf("%d\n", fibheap_delete_min(root)->key);
	fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);

	return 0;
}