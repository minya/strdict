#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stream_reader.h"


static const size_t MIN_STR_BUFFER_LEN = 16;

struct stream_reader_t *stream_reader_create(FILE *source, size_t chunk_size)
{
    struct stream_reader_t *s =
        (struct stream_reader_t *) calloc(1, sizeof(struct stream_reader_t) + chunk_size);

    s->chunk_size = chunk_size;
    s->pos = chunk_size;
    s->stream = source;

    return s;
}

void stream_reader_free(struct stream_reader_t *s)
{
    free(s);
}

size_t realloc_buffer(char *buffer, size_t current_len, char **new_buffer);

char *read_line(struct stream_reader_t *s)
{
    size_t res_buffer_len = MIN_STR_BUFFER_LEN;
    char *response_buffer = (char *) calloc(1, res_buffer_len);
    size_t res_buffer_ptr = 0;
    int toBeRead = 0;
    do  {
        if (s->pos == s->chunk_size) {
            toBeRead = fread(s->buffer, 1, s->chunk_size, s->stream);

            if (0 == toBeRead) {
                return 0;
            }
            s->pos = 0;
        } else {
            toBeRead = s->chunk_size - s->pos;
        }

        if (toBeRead == 0) 
            break;

        char c = s->buffer[s->pos++];
        if (c == 10) {
            break;
        } else if (c == 13) {
            continue;
        }

        if (res_buffer_len == res_buffer_ptr) {
            char *new_buffer;
            res_buffer_len = realloc_buffer(response_buffer, res_buffer_len, &new_buffer);
            response_buffer = new_buffer;
        }

        response_buffer[res_buffer_ptr++] = c;

    } while(toBeRead > 0);

    if (res_buffer_len == res_buffer_ptr) {
        char *new_buffer;
        res_buffer_len = realloc_buffer(response_buffer, res_buffer_len, &new_buffer);
        response_buffer = new_buffer;
    }
    response_buffer[res_buffer_ptr++] = 0;
    return response_buffer;
}

size_t realloc_buffer(char *buffer, size_t current_len, char **new_buffer)
{
    *new_buffer = (char *) calloc(1, current_len * 2);
    memcpy(*new_buffer, buffer, current_len);
    free(buffer);
    return current_len * 2;
}
