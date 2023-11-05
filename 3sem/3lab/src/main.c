#include "fibheap.h"

int main()
{
	fibheap *heap1 = make_fibheap();
	fibheap_insert(heap1, 5);
	fibheap_insert(heap1, 20);
	fibheap_insert(heap1, 10);
	fibheap_insert(heap1, 30);
	fibheap_insert(heap1, 15);

	printf("First ");
	fibheap_print(heap1);

	fibheap *heap2 = make_fibheap();
	fibheap_insert(heap2, 6);
	fibheap_insert(heap2, 21);
	fibheap_insert(heap2, 11);
	fibheap_insert(heap2, 31);
	fibheap_insert(heap2, 16);

	printf("Second ");
	fibheap_print(heap2);

	fibheap* heap3 = fibheap_union(heap1, heap2);

	printf("Third after union first and second ");
	fibheap_print(heap3);

	fibheap_delete_min(heap3);

	printf("Third after delete min ");
	fibheap_print(heap3);

	fibheap_delete(heap3, heap3->min->child->right);

	printf("Third after delete node with key 11 ");
	fibheap_print(heap3);

	fibheap_decrease_key(heap3, heap3->min->child->right, 1);

	printf("Third after decrease node with key 21 to 1 ");
	fibheap_print(heap3);

	return 0;
}