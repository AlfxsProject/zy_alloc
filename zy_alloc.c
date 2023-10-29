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
#include "zy_alloc.h"
#include <string.h>

/*
 * Types
 */

struct zy_alloc_s
{
    const zy_malloc_t malloc;
    const zy_realloc_t realloc;
    const zy_free_t free;
};

/*
 * Functions
 */

int zy_alloc_construct(zy_alloc_t **alloc, zy_malloc_t malloc, zy_realloc_t realloc, zy_free_t free)
{
    *alloc = malloc(sizeof(zy_alloc_t));
    if (*alloc != NULL)
    {
        const zy_alloc_t alloc_init = {.malloc = malloc, .realloc = realloc, .free = free};
        memcpy((void *)*alloc, (const void *)&alloc_init, sizeof(zy_alloc_t));
        return ZY_OK;
    }
    return ZY_ENOMEM;
}

void zy_alloc_destruct(zy_alloc_t **alloc)
{
    const zy_free_t free = (*alloc)->free;
    free((void *)*alloc);
    *alloc = NULL;
}

int zy_malloc(const zy_alloc_t *alloc, size_t size, void **ptr)
{
    *ptr = alloc->malloc(size);
    if (*ptr != NULL)
    {
        return ZY_OK;
    }
    return ZY_ENOMEM;
}

int zy_realloc(const zy_alloc_t *alloc, size_t size, void **ptr)
{
    void *x_ptr = alloc->realloc(*ptr, size);
    if (x_ptr != NULL)
    {
        *ptr = x_ptr;
        return ZY_OK;
    }
    return ZY_ENOMEM;
}

void zy_free(const zy_alloc_t *alloc, void **ptr)
{
    alloc->free(*ptr);
    *ptr = NULL;
}