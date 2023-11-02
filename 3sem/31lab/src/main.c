#include "fibheap.h"

int main()
{
	fibheap *root = make_fibheap();
	fibheap_insert(root, 1);
	fibheap_insert(root, 2);
	fibheap_insert(root, 3);
	fibheap_insert(root, 4);
	fibheap_insert(root, 5);
	fibheap_insert(root, 6);
	fibheap_insert(root, 7);
	fibheap_insert(root, 8);
	fibheap_insert(root, 9);
	fibheap_insert(root, 0);
	fibheap_insert(root, 10);
	fibheap_insert(root, 11);
	fibheap_print(root->min);
	fibheap_delete_min(root);
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
	// printf("%d\n", fibheap_delete_min(root)->key);
	// fibheap_print(root->min);

	return 0;
}