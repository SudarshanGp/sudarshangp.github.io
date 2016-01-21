typedef struct _metadata_entry_t {
    void *ptr;
    int size;
    int free;
    struct _metadata_entry_t *next;
} metadata_entry_t;

metadata_entry_t *metadata = NULL;

// TA simple solution. i) Complete the code. ii) Which placement algorithm does this use? iii) Does this implementation use explicit or implicit linked list? How would you change this to use a first-fit placement allocation? iv) Why does this code suffer from false fragmentation?
void *malloc(size_t size) {

    /* See if we have free space of enough size. */
    metadata_entry_t *p = metadata;
    metadata_entry_t *chosen = NULL;

    while (p != NULL) {
        if (p->free && _______________________) {
            if (chosen == NULL || (chosen && p->size < chosen->size)) {
                chosen = p;
            }
        }
        p = p->next;
    }

    if (chosen) {
        chosen->free = 0;
        return chosen->ptr;
    }

   /* Add our entry to the metadata */
    chosen = sbrk(0);
    sbrk(sizeof(metadata_entry_t));
    chosen->ptr = sbrk(0);
    if (sbrk(size) == (void*)-1) {
        return NULL;
    }
    chosen->size = size;
    chosen->free = 0;

    chosen->next = metadata;
    metadata = chosen;

    return chosen->ptr;
}
