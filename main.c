#include <stdlib.h>
#include <stdio.h>

#include "stream_reader.h"
#include "strset.h"

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
    struct strset_t *set = strset_create(4096);

    char *word = read_line(sr);
    while (0 != word) {
        printf("%s\n", word);
        strset_insert(set, word);
        word = read_line(sr);
    }
    fclose(dic_file);
    stream_reader_free(sr);

    return 0;
}
