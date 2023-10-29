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

typedef struct zy_alloc_s zy_alloc_t;

typedef void *(*zy_malloc_t)(size_t size);

typedef void *(*zy_realloc_t)(void *ptr, size_t size);

typedef void (*zy_free_t)(void *ptr);

/*
 * Constants
 */

#define ZY_OK (0)
#define ZY_ENOMEM (-1)

/*
 * Functions
 */

#ifdef __cplusplus
extern "C"
{
#endif

    __attribute__((nonnull)) int zy_alloc_construct(zy_alloc_t **alloc, zy_malloc_t malloc, zy_realloc_t realloc,
                                                    zy_free_t free);

    __attribute__((nonnull)) void zy_alloc_destruct(zy_alloc_t **alloc);

    __attribute__((nonnull)) int zy_malloc(const zy_alloc_t *alloc, size_t size, void **ptr);

    __attribute__((nonnull)) int zy_realloc(const zy_alloc_t *alloc, size_t size, void **ptr);

    __attribute__((nonnull)) void zy_free(const zy_alloc_t *alloc, void **ptr);

#ifdef __cplusplus
}
#endif