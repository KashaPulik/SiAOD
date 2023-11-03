#include "fibheap.h"

int main()
{
	fibheap *heap1 = make_fibheap();
	fibheap_insert(heap1, 5);
	fibheap_insert(heap1, 20);
	fibheap_insert(heap1, 10);
	fibheap_insert(heap1, 30);
	fibheap_insert(heap1, 15);

	fibheap *heap2 = make_fibheap();
	fibheap_insert(heap2, 6);
	fibheap_insert(heap2, 21);
	fibheap_insert(heap2, 11);
	fibheap_insert(heap2, 31);
	fibheap_insert(heap2, 16);

	fibheap* heap3 = fibheap_union(heap1, heap2);

	fibheap_print(heap3);

	fibheap_delete_min(heap3);

	fibheap_print(heap3);

	fibheap_delete(heap3, heap3->min->child->right);

	fibheap_print(heap3);

	return 0;
}