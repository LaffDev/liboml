#include "liboml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

table *oml_get(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    table *t = malloc(sizeof(table));
    t->entries = malloc(101 * sizeof(entry));

    int count = 0;
    char line[256];
    while (count < 100 && fgets(line, sizeof line, f)) {
        char key[100];
        int pos = 0;

        if (sscanf(line, " %99[^= ] =%n", key, &pos) != 1 || pos == 0)
            continue;

        char **vals = malloc(11 * sizeof(char *));
        int n = 0;
        char *p = line + pos;

        while (n < 10) {
            char *start = strchr(p, '"');
            if (!start) break;
            char *end = strchr(start + 1, '"');
            if (!end) break;

            *end = '\0';
            vals[n++] = strdup(start + 1);
            p = end + 1;
        }
        vals[n] = NULL;

        if (n == 0) {
            free(vals);
            continue;
        }

        t->entries[count].key = strdup(key);
        t->entries[count].value = vals;
        count++;
    }

    t->entries[count].key = NULL;
    t->entries[count].value = NULL;

    fclose(f);
    return t;
}

entry *oml_bykey(table *data, const char *key)
{
    if (!data || !key) return NULL;

    for (int i = 0; data->entries[i].key; i++) {

        if (strcmp(data->entries[i].key, key) == 0)
            return &data->entries[i];

    }

    return NULL;
}

size_t oml_params(entry *e)
{
    if (!e || !e->value) return 0;

    size_t n = 0;
    while (e->value[n])
        n++;

    return n;
}