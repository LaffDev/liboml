#ifndef LIBOML_H_
#define LIBOML_H_

#include <stddef.h>

typedef struct {
    char *key;
    char **value;
} entry;

typedef struct {
    entry *entries;
} table;

table *oml_get(const char *filename);
entry *oml_bykey(table *data, const char *key);
size_t oml_params(entry *e);

#endif