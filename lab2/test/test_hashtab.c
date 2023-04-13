#include "../hashtab.h"

int main()
{
    listnode* KRlist[HASH_SIZE];
    listnode* Jlist[HASH_SIZE];
    
    hashtab_init(KRlist);
    hashtab_init(Jlist);

    printf("abc = %d\n", KRHash("abc"));
    printf("bcd = %d\n", KRHash("bcd"));
    printf("abc = %d\n", KRHash("abc"));
    printf("abc = %d\n", jenkins_hash("abc"));
    printf("bcd = %d\n", jenkins_hash("bcd"));
    printf("abc = %d\n", jenkins_hash("abc"));

    hashtab_add(KRlist, "abc", 1, KRHash);
    hashtab_add(KRlist, "bcd", 2, KRHash);
    hashtab_add(Jlist, "abc", 3, jenkins_hash);
    hashtab_add(Jlist, "bcd", 4, jenkins_hash);
    
    printf("%d\n", hashtab_lookup(KRlist, "abc", KRHash)->value);
    printf("%d\n", hashtab_lookup(KRlist, "bcd", KRHash)->value);
    printf("%d\n", hashtab_lookup(Jlist, "abc", jenkins_hash)->value);
    printf("%d\n", hashtab_lookup(Jlist, "bcd", jenkins_hash)->value);

    printf("%p\n", hashtab_lookup(Jlist, "abc", jenkins_hash));
    
    hashtab_delete(Jlist, "abc", jenkins_hash);

    printf("%p\n", hashtab_lookup(Jlist, "abc", jenkins_hash));
}