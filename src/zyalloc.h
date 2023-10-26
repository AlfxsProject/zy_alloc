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
#pragma once

#include <stddef.h>

/*
 * Types
 */

typedef struct zyalloc_s zyalloc_t;

typedef void *(*zymalloc_t)(size_t size);

typedef void *(*zyrealloc_t)(void *ptr, size_t size);

typedef void (*zyfree_t)(void *ptr);

/*
 * Constants
 */

#define ZYALLOC_OK (0)
#define ZYALLOC_ENOMEM (-1)

/*
 * Functions
 */

#ifdef __cplusplus
extern "C"
{
#endif

    int zyalloc_construct(zyalloc_t **alloc, zymalloc_t malloc, zyrealloc_t realloc, zyfree_t free)
        __attribute__((nonnull));

    void zyalloc_destruct(zyalloc_t **alloc) __attribute__((nonnull));

    int zymalloc(const zyalloc_t *alloc, size_t size, void **ptr) __attribute__((nonnull));

    int zyrealloc(const zyalloc_t *alloc, size_t size, void **ptr) __attribute__((nonnull));

    void zyfree(const zyalloc_t *alloc, void **ptr) __attribute__((nonnull));

#ifdef __cplusplus
}
#endif