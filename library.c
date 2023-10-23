/*
 * Copyright 2023 Alexandre Fernandez <alex@fernandezfamily.email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "library.h"
#include <string.h>

/*
 * Types
 */

struct zyalloc_s
{
    const zymalloc_t malloc;
    const zyrealloc_t realloc;
    const zyfree_t free;
};

/*
 * Functions
 */

int zyalloc_construct(zyalloc_t **alloc, const zymalloc_t malloc, const zyrealloc_t realloc, const zyfree_t free)
{
    *alloc = malloc(sizeof(zyalloc_t));
    if (*alloc != NULL)
    {
        const zyalloc_t alloc_init = {.malloc = malloc, .realloc = realloc, .free = free};
        memcpy((void *)*alloc, (const void *)&alloc_init, sizeof(zyalloc_t));
        return ZYALLOC_OK;
    }
    return ZYALLOC_ENOMEM;
}

void zyalloc_destruct(zyalloc_t **alloc)
{
    const zyfree_t free = (*alloc)->free;
    free((void *)*alloc);
    *alloc = NULL;
}

int zymalloc(const zyalloc_t *alloc, size_t size, void **ptr)
{
    *ptr = alloc->malloc(size);
    if (*ptr != NULL)
    {
        return ZYALLOC_OK;
    }
    return ZYALLOC_ENOMEM;
}

int zyrealloc(const zyalloc_t *alloc, size_t size, void **ptr)
{
    void *xptr = alloc->realloc(*ptr, size);
    if (xptr != NULL)
    {
        *ptr = xptr;
        return ZYALLOC_OK;
    }
    return ZYALLOC_ENOMEM;
}

void zyfree(const zyalloc_t *alloc, void **ptr)
{
    alloc->free(*ptr);
    *ptr = NULL;
}