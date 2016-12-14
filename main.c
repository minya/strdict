#include <stdlib.h>
#include <stdio.h>

#include "stream_reader.h"
#include "strset.h"

static const size_t DICT_SIZE = 4194304;

int main(int argc, char **argv)
{
    if (argc != 2) {
        exit(-1);
    }

    char *dic_file_name = argv[1];
    FILE *dic_file = fopen(dic_file_name, "r");
    if (!dic_file) {
        exit(-1);
    }

    struct stream_reader_t *sr = stream_reader_create(dic_file, 4096);
    struct strset_t *set = strset_create(DICT_SIZE);

    char *word = stream_reader_read_line(sr);
    while (0 != word) {
        strset_insert(set, word);
        word = stream_reader_read_line(sr);
    }
    fclose(dic_file);
    stream_reader_free(sr);

    struct stream_reader_t *in = stream_reader_create(stdin, 256);
    char *candidate = stream_reader_read_line(in);
    while (0 != candidate) {
        if (strset_contains(set, candidate)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        free(candidate);
        candidate = stream_reader_read_line(in);
    }

    stream_reader_free(in);
    /*printf("writes total: %zu, collision: %zu\n", \*/
            /*set->stat.write_total, set->stat.write_collision_total);*/
    strset_free(set);

    return 0;
}
