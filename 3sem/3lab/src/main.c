#include <fibheap.h>

int main()
{
	fibheap *root = make_fibheap();
	root = fibheap_insert(root, 5);
	root = fibheap_insert(root, 2);
	root = fibheap_insert(root, 3);
	root = fibheap_insert(root, 6);
	fibheap_print(root->min);

	printf("\n");

	fibheap *root2 = make_fibheap();
	root2 = fibheap_insert(root2, 1);
	root2 = fibheap_insert(root2, 4);
	root2 = fibheap_insert(root2, 7);
	root2 = fibheap_insert(root2, 0);
	fibheap_print(root2->min);

	printf("\n");

    fibheap *root3 = fibheap_union(root, root2);
	fibheap_print(root3->min);

    root3 = fibheap_consolidate(root3);
	fibheap_print(root3->min);

	return 0;
}