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

/*
 * Types
 */

struct zy_alloc_s
{
    zy_malloc_t malloc;
    zy_realloc_t realloc;
    zy_free_t free;
};

/*
 * Functions
 */

int zy_alloc_construct(zy_alloc_t **alloc, zy_malloc_t malloc, zy_realloc_t realloc, zy_free_t free)
{
    *alloc = malloc(sizeof(zy_alloc_t));
    if (*alloc != nullptr)
    {
        (*alloc)->malloc = malloc;
        (*alloc)->realloc = realloc;
        (*alloc)->free = free;
        return ZY_OK;
    }
    return ZY_E_NOMEM;
}

void zy_alloc_destruct(zy_alloc_t **alloc)
{
    if (*alloc != nullptr)
    {
        const zy_free_t free = (*alloc)->free;
        free((void *)*alloc);
        *alloc = nullptr;
    }
}

int zy_malloc(const zy_alloc_t *alloc, size_t size, void **ptr)
{
    *ptr = alloc->malloc(size);
    if (*ptr != nullptr)
    {
        return ZY_OK;
    }
    return ZY_E_NOMEM;
}

int zy_realloc(const zy_alloc_t *alloc, size_t size, void **ptr)
{
    void *x_ptr = alloc->realloc(*ptr, size);
    if (x_ptr != nullptr)
    {
        *ptr = x_ptr;
        return ZY_OK;
    }
    return ZY_E_NOMEM;
}

void zy_free(const zy_alloc_t *alloc, void **ptr)
{
    alloc->free(*ptr);
    *ptr = nullptr;
}