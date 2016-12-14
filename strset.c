#include <string.h>
#include "strset.h"
#include "hash.h"

struct strset_t *strset_create(size_t capacity)
{
    struct strset_t *s =
        (struct strset_t *) calloc(1, sizeof(struct strset_t) + sizeof(struct strset_node_t *) * capacity);
    s->hash_fn = FNV_hash;
    s->capacity = capacity;
    return s;
}

void strset_list_free(struct strset_node_t *first);

void strset_free(struct strset_t *s)
{
    for (size_t i = 0; i < s->capacity; ++i) {
        if (0 != s->buffer[i]) {
            strset_list_free(s->buffer[i]);
        }
    }

    free(s);
}

void strset_insert(struct strset_t *s, char *key)
{
    ++s->stat.write_total;
    int index = s->hash_fn(key) % s->capacity;
    if (0 == s->buffer[index]) {
        struct strset_node_t *new_node =
            (struct strset_node_t *) calloc(1, sizeof(struct strset_node_t));
        new_node->key = key;
        s->buffer[index] = new_node;
    } else {
        ++s->stat.write_collision_total;
        struct strset_node_t *current = s->buffer[index];
        while (0 != current->next) {
            current = current->next;
        }

        struct strset_node_t *new_node =
            (struct strset_node_t *) calloc(1, sizeof(struct strset_node_t));

        new_node->key = key;
        current->next = new_node;
    }
}

int strset_contains(struct strset_t *s, char *key)
{
    int index = s->hash_fn(key) % s->capacity;
    struct strset_node_t *run = s->buffer[index];
    size_t len = strlen(key);
    while (0 != run) {
        char *other_key = run->key;

        if (strlen(other_key) == len && 0 == strncmp(key, other_key, len)) {
            return 1;
        }
        run = run->next;
    }
    return 0;
}


void strset_list_free(struct strset_node_t *first)
{
    while (0 != first) {
        struct strset_node_t *tmp = first;
        first = first->next;
        free(tmp);
    }
}
