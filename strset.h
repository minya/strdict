#include <stdlib.h>


struct strset_node_t {
    char *key;
    struct strset_node_t *next;
};

struct strset_t {
    size_t capacity;
    uint32_t (*hash_fn)(char *);
    struct strset_node_t *buffer[];
};


struct strset_t *strset_create(size_t capacity);

void strset_free(struct strset_t *s);

void strset_insert(struct strset_t *s, char *key);

int strset_contains(struct strset_t *s, char *key);
