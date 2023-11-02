// Operations on a Fibonacci heap in C

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct fibheap_fibheap_node {
    int key;
    int degree;
    struct fibheap_fibheap_node* left;
    struct fibheap_fibheap_node* right;
    struct fibheap_fibheap_node* parent;
    struct fibheap_fibheap_node* child;
    bool mark;
    bool visited;
} fibheap_node;

typedef struct fibheap {
    int n;
    fibheap_node* min;
    int phi;
    int degree;
} fibheap;

fibheap* make_fibheap();
void fibheap_insert(fibheap* H, fibheap_node* node, int val);
fibheap_node* fibheap_delete_min(fibheap* H);
void fibheap_consolidate(fibheap* H);
void fibheap_link(fibheap* H, fibheap_node* y, fibheap_node* x);
fibheap_node* fibheap_min(fibheap* H);
void fibheap_decrease_key(fibheap* H, fibheap_node* fibheap_node, int key);
void fibheap_cut(fibheap* H, fibheap_node* fibheap_node_to_be_decrease, fibheap_node* parentfibheap_fibheap_node);
void fibheap_cascading_cut(fibheap* H, fibheap_node* parentfibheap_fibheap_node);
void Deletefibheap_fibheap_node(fibheap* H, int dec_key);

fibheap* make_fibheap()
{
    fibheap* H;
    H = (fibheap*)malloc(sizeof(fibheap));
    H->n = 0;
    H->min = NULL;
    H->phi = 0;
    H->degree = 0;
    return H;
}

// Printing the heap
void print_heap(fibheap_node* n)
{
    fibheap_node* x;
    for (x = n;; x = x->right) {
        if (x->child == NULL) {
            printf("fibheap_node with no child (%d) \n", x->key);
        } else {
            printf("fibheap_node(%d) with child (%d)\n", x->key, x->child->key);
            print_heap(x->child);
        }
        if (x->right == n) {
            break;
        }
    }
}

// Inserting fibheap_nodes
void fibheap_insert(fibheap* H, fibheap_node* node, int val)
{
    node = (fibheap_node*)malloc(sizeof(fibheap_node));
    node->key = val;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->visited = false;
    node->left = node;
    node->right = node;
    if (H->min == NULL) {
        H->min = node;
    } else {
        H->min->left->right = node;
        node->right = H->min;
        node->left = H->min->left;
        H->min->left = node;
        if (node->key < H->min->key) {
            H->min = node;
        }
    }
    (H->n)++;
}

// Find min fibheap_node
fibheap_node* fibheap_min(fibheap* H)
{
    if (H == NULL) {
        printf(" \n Fibonacci heap not yet created \n");
        return NULL;
    } else
        return H->min;
}

// Union operation
fibheap* fibheap_union(fibheap* heap1, fibheap* heap2)
{
    fibheap* heap;
    heap = make_fibheap();
    heap->min = heap1->min;

    fibheap_node *temp1, *temp2;
    temp1 = heap->min->right;
    temp2 = heap2->min->left;

    heap->min->right->left = heap2->min->left;
    heap->min->right = heap2->min;
    heap2->min->left = heap->min;
    temp2->right = temp1;

    if ((heap1->min == NULL) || (heap2->min != NULL && heap2->min->key < heap1->min->key))
        heap->min = heap2->min;
    heap->n = heap1->n + heap2->n;
    return heap;
}

// Calculate the degree
int D(int n)
{
    int count = 0;
    while (n > 0) {
        n = n / 2;
        count++;
    }
    return count;
}

// fibheap_Consolidate function
void fibheap_consolidate(fibheap* H)
{
    int degree, i, d;
    degree = D(H->n);
    fibheap_node *A[degree], *x, *y;
    for (i = 0; i <= degree; i++) {
        A[i] = NULL;
    }
    x = H->min;
    do {
        d = x->degree;
        while (A[d] != NULL) {
            y = A[d];
            if (x->key > y->key) {
                fibheap_node* exchange_help;
                exchange_help = x;
                x = y;
                y = exchange_help;
            }
            if (y == H->min)
                H->min = x;
            fibheap_link(H, y, x);
            if (y->right == x)
                H->min = x;
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        x = x->right;
    } while (x != H->min);

    H->min = NULL;
    for (i = 0; i < degree; i++) {
        if (A[i] != NULL) {
            A[i]->left = A[i];
            A[i]->right = A[i];
            if (H->min == NULL) {
                H->min = A[i];
            } else {
                H->min->left->right = A[i];
                A[i]->right = H->min;
                A[i]->left = H->min->left;
                H->min->left = A[i];
                if (A[i]->key < H->min->key) {
                    H->min = A[i];
                }
            }
            if (H->min == NULL) {
                H->min = A[i];
            } else if (A[i]->key < H->min->key) {
                H->min = A[i];
            }
        }
    }
}

// Linking
void fibheap_link(fibheap* H, fibheap_node* y, fibheap_node* x)
{
    y->right->left = y->left;
    y->left->right = y->right;

    if (x->right == x)
        H->min = x;

    y->left = y;
    y->right = y;
    y->parent = x;

    if (x->child == NULL) {
        x->child = y;
    }
    y->right = x->child;
    y->left = x->child->left;
    x->child->left->right = y;
    x->child->left = y;
    if ((y->key) < (x->child->key))
        x->child = y;

    (x->degree)++;
}

// Extract min
fibheap_node* fibheap_delete_min(fibheap* H)
{
    if (H->min == NULL)
        printf("\n The heap is empty");
    else {
        fibheap_node* z = H->min;
        fibheap_node* w;
        w = z;
        fibheap_node* x = NULL;
        if (z->child != NULL) {
            x = z->child;
            do {
                w = x->right;
                (H->min->left)->right = x;
                x->right = H->min;
                x->left = H->min->left;
                H->min->left = x;
                if (x->key < H->min->key)
                    H->min = x;
                x->parent = NULL;
                x = w;
            } while (w != z->child);
        }

        (z->left)->right = z->right;
        (z->right)->left = z->left;
        H->min = z->right;

        if (z == z->right && z->child == NULL)
            H->min = NULL;
        else {
            H->min = z->right;
            fibheap_consolidate(H);
        }
        H->n = H->n - 1;
        return z;
    }
    return H->min;
}

void fibheap_cut(fibheap* H, fibheap_node* fibheap_node_to_be_decrease, fibheap_node* parentfibheap_fibheap_node)
{
    if (fibheap_node_to_be_decrease == fibheap_node_to_be_decrease->right)
        parentfibheap_fibheap_node->child = NULL;

    fibheap_node_to_be_decrease->left->right
            = fibheap_node_to_be_decrease->right;
    fibheap_node_to_be_decrease->right->left
            = fibheap_node_to_be_decrease->left;
    if (fibheap_node_to_be_decrease == parentfibheap_fibheap_node->child)
        parentfibheap_fibheap_node->child = fibheap_node_to_be_decrease->right;
    (parentfibheap_fibheap_node->degree)--;

    fibheap_node_to_be_decrease->left = fibheap_node_to_be_decrease;
    fibheap_node_to_be_decrease->right = fibheap_node_to_be_decrease;
    H->min->left->right = fibheap_node_to_be_decrease;
    fibheap_node_to_be_decrease->right = H->min;
    fibheap_node_to_be_decrease->left = H->min->left;
    H->min->left = fibheap_node_to_be_decrease;

    fibheap_node_to_be_decrease->parent = NULL;
    fibheap_node_to_be_decrease->mark = false;
}

void fibheap_cascading_cut(fibheap* H, fibheap_node* parentfibheap_fibheap_node)
{
    fibheap_node* aux;
    aux = parentfibheap_fibheap_node->parent;
    if (aux != NULL) {
        if (parentfibheap_fibheap_node->mark == false) {
            parentfibheap_fibheap_node->mark = true;
        } else {
            fibheap_cut(H, parentfibheap_fibheap_node, aux);
            fibheap_cascading_cut(H, aux);
        }
    }
}

void fibheap_decrease_key(fibheap* H, fibheap_node* fibheap_node_to_be_decrease, int node_key)
{
    fibheap_node* parentfibheap_fibheap_node;
    if (H == NULL) {
        printf("\n FIbonacci heap not created ");
        return;
    }
    if (fibheap_node_to_be_decrease == NULL) {
        printf("fibheap_node is not in the heap");
    }

    else {
        if (fibheap_node_to_be_decrease->key < node_key) {
            printf("\n Invalid node key for decrease key operation \n ");
        } else {
            fibheap_node_to_be_decrease->key = node_key;
            parentfibheap_fibheap_node = fibheap_node_to_be_decrease->parent;
            if ((parentfibheap_fibheap_node != NULL)
                && (fibheap_node_to_be_decrease->key < parentfibheap_fibheap_node->key)) {
                printf("\n fibheap_cut called");
                fibheap_cut(H, fibheap_node_to_be_decrease, parentfibheap_fibheap_node);
                printf("\n cascading fibheap_cut called");
                fibheap_cascading_cut(H, parentfibheap_fibheap_node);
            }
            if (fibheap_node_to_be_decrease->key < H->min->key) {
                H->min = fibheap_node_to_be_decrease;
            }
        }
    }
}

void findfibheap_fibheap_node(fibheap* H, fibheap_node* n, int key, int node_key)
{
    fibheap_node* find_use = n;
    fibheap_node* f = NULL;
    find_use->visited = true;
    if (find_use->key == key) {
        find_use->visited = false;
        f = find_use;
        fibheap_decrease_key(H, f, node_key);
    }
    if (find_use->child != NULL) {
        findfibheap_fibheap_node(H, find_use->child, key, node_key);
    }
    if ((find_use->right->visited != true)) {
        findfibheap_fibheap_node(H, find_use->right, key, node_key);
    }

    find_use->visited = false;
}

fibheap* fibheap_insert_procedure()
{
    fibheap* temp;
    int no_offibheap_fibheap_nodes, ele, i;
    fibheap_node* nodefibheap_fibheap_node = NULL;
    temp = (fibheap*)malloc(sizeof(fibheap));
    temp = NULL;
    if (temp == NULL) {
        temp = make_fibheap();
    }
    printf(" \n enter number of fibheap_nodes to be insert = ");
    scanf("%d", &no_offibheap_fibheap_nodes);
    for (i = 1; i <= no_offibheap_fibheap_nodes; i++) {
        printf("\n fibheap_node %d and its key value = ", i);
        scanf("%d", &ele);
        fibheap_insert(temp, nodefibheap_fibheap_node, ele);
    }
    return temp;
}
void Deletefibheap_fibheap_node(fibheap* H, int dec_key)
{
    fibheap_node* p = NULL;
    findfibheap_fibheap_node(H, H->min, dec_key, -5000);
    p = fibheap_delete_min(H);
    if (p != NULL)
        printf("\n fibheap_node deleted");
    else
        printf("\n fibheap_node not deleted:some error");
}

int main()
{
    fibheap_node *nodefibheap_fibheap_node = NULL, *minfibheap_fibheap_node, *extracted_min, *find_use;
    fibheap *heap, *heap1;
    int operation_no, node_key, dec_key, ele, i, no_offibheap_fibheap_nodes;
    heap = (fibheap*)malloc(sizeof(fibheap));
    heap = NULL;
    while (1) {
        printf(" \n Operations \n 1. Create Fibonacci heap \n 2. Insert fibheap_nodes "
               "into fibonacci heap \n 3. Find min \n 4. Union \n 5. Extract "
               "min \n 6. Decrease key \n 7.Delete fibheap_node \n 8. print heap \n 9. "
               "exit \n enter operation_no = ");
        scanf("%d", &operation_no);

        switch (operation_no) {
        case 1:
            heap = make_fibheap();
            break;

        case 2:
            if (heap == NULL) {
                heap = make_fibheap();
            }
            printf(" enter number of fibheap_nodes to be insert = ");
            scanf("%d", &no_offibheap_fibheap_nodes);
            for (i = 1; i <= no_offibheap_fibheap_nodes; i++) {
                printf("\n fibheap_node %d and its key value = ", i);
                scanf("%d", &ele);
                fibheap_insert(heap, nodefibheap_fibheap_node, ele);
            }
            break;

        case 3:
            minfibheap_fibheap_node = fibheap_min(heap);
            if (minfibheap_fibheap_node == NULL)
                printf("No minimum value");
            else
                printf("\n min value = %d", minfibheap_fibheap_node->key);
            break;

        case 4:
            if (heap == NULL) {
                printf("\n no FIbonacci heap created \n ");
                break;
            }
            heap1 = fibheap_insert_procedure();
            heap = fibheap_union(heap, heap1);
            printf("Unified Heap:\n");
            print_heap(heap->min);
            break;

        case 5:
            if (heap == NULL)
                printf("Empty Fibonacci heap");
            else {
                extracted_min = fibheap_delete_min(heap);
                printf("\n min value = %d", extracted_min->key);
                printf("\n Updated heap: \n");
                print_heap(heap->min);
            }
            break;

        case 6:
            if (heap == NULL)
                printf("Fibonacci heap is empty");
            else {
                printf(" \n fibheap_node to be decreased = ");
                scanf("%d", &dec_key);
                printf(" \n enter the node key = ");
                scanf("%d", &node_key);
                find_use = heap->min;
                findfibheap_fibheap_node(heap, find_use, dec_key, node_key);
                printf("\n Key decreased- Corresponding heap:\n");
                print_heap(heap->min);
            }
            break;
        case 7:
            if (heap == NULL) {
                printf("Fibonacci heap is empty");
                break;
            } else {
                printf(" \n Enter fibheap_node key to be deleted = ");
                scanf("%d", &dec_key);
                Deletefibheap_fibheap_node(heap, dec_key);
                printf("\n fibheap_node Deleted- Corresponding heap:\n");
                print_heap(heap->min);
                break;
            }
        case 8:
            print_heap(heap->min);
            break;

        case 9:
            free(nodefibheap_fibheap_node);
            free(heap);
            exit(0);

        default:
            printf("Invalid choice ");
        }
    }
}