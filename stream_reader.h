#include <stdio.h>


struct stream_reader_t {
    FILE *stream;
    size_t chunk_size;
    size_t pos;
    char buffer[];
};


struct stream_reader_t *stream_reader_create(FILE *source, size_t chunk_size);

void stream_reader_free(struct stream_reader_t *s);

char *stream_reader_read_line(struct stream_reader_t *s);
