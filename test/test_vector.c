/*
 *  The implementation of vector test.
 *  Copyright (C)  2008 2009  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <stdio.h>
#include <float.h>
#include "cvector.h"
#include "test_vector.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
typedef struct _tagabc
{
    int    _n_first;
    double _d_second;
    char*  _pc_third;
}abc_t;

/** local function prototype section **/
static void _abc_init(const void* cpv_input, void* pv_output);
static void _abc_copy(const void* cpv_first, const void* cpv_second, void* pv_output);
static void _abc_less(const void* cpv_first, const void* cpv_second, void * pv_output);
static void _abc_destroy(const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_vector(void)
{
    /* c builtin type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_init_n() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 3);
            vector_destroy(pv_int);
        }
        /* vector_init_elem() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, 100);
            vector_destroy(pv_int);
        }
        /* vector_init_copy() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_src = create_vector(int);

            if(pv_int == NULL || pv_src == NULL)
            {
                return;
            }

            vector_init_elem(pv_src, 3, -39);
            vector_init_copy(pv_int, pv_src);
            vector_destroy(pv_src);
            vector_destroy(pv_int);
        }
        /* vector_init_copy_range() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_src = create_vector(int);

            if(pv_int == NULL || pv_src == NULL)
            {
                return;
            }

            vector_init_elem(pv_src, 3, -39);
            vector_init_copy_range(pv_int,
                vector_begin(pv_src), iterator_next(vector_begin(pv_src)));
            vector_destroy(pv_src);
            vector_destroy(pv_int);
        }
        /* vector_size() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 100);
            printf("size: %d\n", vector_size(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_capacity() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            printf("capacity: %d\n", vector_capacity(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_max_size() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 20);
            printf("max size: %d\n", vector_max_size(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_empty() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            printf("empty: %d\n", vector_empty(pv_int));
            vector_push_back(pv_int, 100);
            printf("empty: %d\n", vector_empty(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_reserve() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 33);
            printf("capacity: %d\n", vector_capacity(pv_int));
            vector_reserve(pv_int, 5);
            printf("capacity: %d\n", vector_capacity(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_assign() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 7, 33);
            vector_init_elem(pv_signed, 5, -200);
            vector_assign(pv_int, pv_signed);
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_assign_elem() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 7, 33);
            vector_assign_elem(pv_int, 3, -88888);
            vector_destroy(pv_int);
        }
        /* vector_assign_range() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 7, 33);
            vector_init_elem(pv_signed, 5, -200);
            vector_assign_range(pv_int,
                iterator_next(vector_begin(pv_signed)),
                iterator_prev_n(vector_end(pv_signed), 2));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed int);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 5, 100);
            vector_init_elem(pv_signed, 5, 100);
            printf("equal: %d\n", vector_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_not_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, 300);
            vector_init_elem(pv_signed, 3, 300);
            printf("not equal: %d\n", vector_not_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_less() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("less: %d\n", vector_less(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_less_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("less equal: %d\n", vector_less_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_great() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("great: %d\n", vector_great(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_great_equal() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 2, 200);
            vector_init_elem(pv_signed, 2, 200);
            printf("great equal: %d\n", vector_great_equal(pv_int, pv_signed));
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_swap() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_signed = create_vector(signed);
            if(pv_int == NULL || pv_signed == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 0, 200);
            vector_init_elem(pv_signed, 2, 200);
            vector_swap(pv_int, pv_signed);
            vector_destroy(pv_int);
            vector_destroy(pv_signed);
        }
        /* vector_at() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, -99999);
            if(vector_at(pv_int, 4) != NULL)
            {
                printf("%d\n", *(int*)vector_at(pv_int, 4));
            }
            vector_destroy(pv_int);
        }
        /* vector_front() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 4);
            if(vector_front(pv_int) != NULL)
            {
                printf("%d\n", *(int*)vector_front(pv_int));
            }
            vector_destroy(pv_int);
        }
        /* vector_back() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 4, -112);
            if(vector_back(pv_int) != NULL)
            {
                printf("%d\n", *(int*)vector_back(pv_int));
            }
            vector_destroy(pv_int);
        }
        /* vector_begin() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 10);
            vector_begin(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_end() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 10);
            vector_end(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_insert() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_insert(pv_int, vector_end(pv_int), 10);
            vector_destroy(pv_int);
        }
        /* vector_insert_n() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_n(pv_int, 3);
            vector_insert_n(pv_int, iterator_next(vector_begin(pv_int)), 5, 100);
            vector_destroy(pv_int);
        }
        /* vector_insert_range() */
        {
            vector_t* pv_int = create_vector(int);
            vector_t* pv_insert = create_vector(signed);
            if(pv_int == NULL || pv_insert == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, 12);
            vector_init_elem(pv_insert, 5, 100);
            vector_insert_range(pv_int, vector_end(pv_int),
                iterator_next(vector_begin(pv_insert)), iterator_prev(vector_end(pv_insert)));
            vector_destroy(pv_int);
            vector_destroy(pv_insert);
        }
        /* vector_push_back() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 3, -22);
            vector_push_back(pv_int, 100);
            vector_destroy(pv_int);
        }
        /* vector_pop_back() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_push_back(pv_int, 100);
            vector_push_back(pv_int, 200);
            vector_push_back(pv_int, 300);
            vector_pop_back(pv_int);
            vector_destroy(pv_int);
        }
        /* vector_erase() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init(pv_int);
            vector_push_back(pv_int, 100);
            vector_push_back(pv_int, 200);
            vector_push_back(pv_int, 300);
            vector_erase(pv_int, iterator_next(vector_begin(pv_int)));
            vector_destroy(pv_int);
        }
        /* vector_erase_range() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, 100);
            vector_erase_range(pv_int, vector_begin(pv_int),
                iterator_prev_n(vector_end(pv_int), 6));
            vector_destroy(pv_int);
        }
        /* vector_clear() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, 100);
            printf("%d\n", vector_empty(pv_int));
            vector_clear(pv_int);
            printf("%d\n", vector_empty(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_resize() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 100, 100);
            printf("%d\n", vector_size(pv_int));
            vector_resize(pv_int, 30);
            printf("%d\n", vector_size(pv_int));
            vector_resize(pv_int, 50);
            printf("%d\n", vector_size(pv_int));
            vector_destroy(pv_int);
        }
        /* vector_resize_elem() */
        {
            vector_t* pv_int = create_vector(int);
            if(pv_int == NULL)
            {
                return;
            }

            vector_init_elem(pv_int, 10, 100);
            printf("%d\n", vector_size(pv_int));
            vector_resize_elem(pv_int, 3, 200);
            printf("%d\n", vector_size(pv_int));
            vector_resize_elem(pv_int, 5, 300);
            printf("%d\n", vector_size(pv_int));
            vector_destroy(pv_int);
        }
    }
    /* user defined type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
            vector_t* pt_abc = NULL;

            type_register(abc_t, _abc_init, _abc_copy, _abc_less, _abc_destroy);
            pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }

            vector_init(pt_abc);
            vector_destroy(pt_abc);
        }
        /* vector_init_n() */
        {
            vector_t* pt_abc = NULL;
            type_duplicate(abc_t, struct _tagabc);
            type_debug();
            pt_abc = create_vector(struct _tagabc);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 2);
            vector_destroy(pt_abc);
        }
        /* vector_init_elem() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            abc_t t_abc;
            bool_t t_result = false;
            if(pt_abc == NULL)
            {
                return;
            }

            _abc_init(&t_abc, &t_result);
            t_abc._n_first = 100;
            t_abc._d_second = 32.98;
            memset(t_abc._pc_third, 0x33, sizeof(double));

            vector_init_elem(pt_abc, 3, &t_abc);
            vector_destroy(pt_abc);
        }
        /* vector_init_copy() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            bool_t t_result = false;
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            _abc_init(&t_abc, &t_result);
            t_abc._n_first = 12345;
            t_abc._d_second = 0.99;
            memset(t_abc._pc_third, 0x77, sizeof(double));

            vector_init_elem(pt_abcex, 3, &t_abc);
            vector_init_copy(pt_abc, pt_abcex);
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_init_copy_range() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            vector_t* pt_abcex = create_vector(struct _tagabc);
            abc_t t_abc;
            bool_t t_result = false;
            if(pt_abc == NULL || pt_abcex == NULL)
            {
                return;
            }
            _abc_init(&t_abc, &t_result);
            t_abc._n_first = 12345;
            t_abc._d_second = 0.99;
            memset(t_abc._pc_third, 0x77, sizeof(double));

            vector_init_elem(pt_abcex, 5, &t_abc);
            vector_init_copy_range(pt_abc,
                iterator_next(vector_begin(pt_abcex)),
                iterator_prev(vector_end(pt_abcex)));
            vector_destroy(pt_abc);
            vector_destroy(pt_abcex);
        }
        /* vector_size() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 10);
            printf("%d\n", vector_size(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_capacity() */
        {
            vector_t* pt_abc = create_vector(struct _tagabc);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 10);
            printf("%d\n", vector_capacity(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_max_size() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 3);
            printf("%d\n", vector_max_size(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_empty() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init(pt_abc);
            printf("%d\n", vector_empty(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_reserve() */
        {
            vector_t* pt_abc = create_vector(abc_t);
            if(pt_abc == NULL)
            {
                return;
            }
            vector_init_n(pt_abc, 2);
            printf("%d\n", vector_capacity(pt_abc));
            vector_reserve(pt_abc, 20);
            printf("%d\n", vector_capacity(pt_abc));
            vector_reserve(pt_abc, 2);
            printf("%d\n", vector_capacity(pt_abc));
            vector_destroy(pt_abc);
        }
        /* vector_assign() */
        {
        }
        /* vector_assign_elem() */
        {
        }
        /* vector_assign_range() */
        {
        }
        /* vector_equal() */
        {
        }
        /* vector_not_equal() */
        {
        }
        /* vector_less() */
        {
        }
        /* vector_less_equal() */
        {
        }
        /* vector_great() */
        {
        }
        /* vector_great_equal() */
        {
        }
        /* vector_swap() */
        {
        }
        /* vector_at() */
        {
        }
        /* vector_front() */
        {
        }
        /* vector_back() */
        {
        }
        /* vector_begin() */
        {
        }
        /* vector_end() */
        {
        }
        /* vector_insert() */
        {
        }
        /* vector_insert_n() */
        {
        }
        /* vector_insert_range() */
        {
        }
        /* vector_push_back() */
        {
        }
        /* vector_pop_back() */
        {
        }
        /* vector_erase() */
        {
        }
        /* vector_erase_range() */
        {
        }
        /* vector_clear() */
        {
        }
        /* vector_resize() */
        {
        }
        /* vector_resize_elem() */
        {
        }
    }
    /* libcstl builtin type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
        }
        /* vector_init_n() */
        {
        }
        /* vector_init_elem() */
        {
        }
        /* vector_init_copy() */
        {
        }
        /* vector_init_copy_range() */
        {
        }
        /* vector_size() */
        {
        }
        /* vector_capacity() */
        {
        }
        /* vector_max_size() */
        {
        }
        /* vector_empty() */
        {
        }
        /* vector_reserve() */
        {
        }
        /* vector_assign() */
        {
        }
        /* vector_assign_elem() */
        {
        }
        /* vector_assign_range() */
        {
        }
        /* vector_equal() */
        {
        }
        /* vector_not_equal() */
        {
        }
        /* vector_less() */
        {
        }
        /* vector_less_equal() */
        {
        }
        /* vector_great() */
        {
        }
        /* vector_great_equal() */
        {
        }
        /* vector_swap() */
        {
        }
        /* vector_at() */
        {
        }
        /* vector_front() */
        {
        }
        /* vector_back() */
        {
        }
        /* vector_begin() */
        {
        }
        /* vector_end() */
        {
        }
        /* vector_insert() */
        {
        }
        /* vector_insert_n() */
        {
        }
        /* vector_insert_range() */
        {
        }
        /* vector_push_back() */
        {
        }
        /* vector_pop_back() */
        {
        }
        /* vector_erase() */
        {
        }
        /* vector_erase_range() */
        {
        }
        /* vector_clear() */
        {
        }
        /* vector_resize() */
        {
        }
        /* vector_resize_elem() */
        {
        }
    }
    /* c-string type */
    {
        /* create_vector(), vector_init(), vector_destroy() */
        {
        }
        /* vector_init_n() */
        {
        }
        /* vector_init_elem() */
        {
        }
        /* vector_init_copy() */
        {
        }
        /* vector_init_copy_range() */
        {
        }
        /* vector_size() */
        {
        }
        /* vector_capacity() */
        {
        }
        /* vector_max_size() */
        {
        }
        /* vector_empty() */
        {
        }
        /* vector_reserve() */
        {
        }
        /* vector_assign() */
        {
        }
        /* vector_assign_elem() */
        {
        }
        /* vector_assign_range() */
        {
        }
        /* vector_equal() */
        {
        }
        /* vector_not_equal() */
        {
        }
        /* vector_less() */
        {
        }
        /* vector_less_equal() */
        {
        }
        /* vector_great() */
        {
        }
        /* vector_great_equal() */
        {
        }
        /* vector_swap() */
        {
        }
        /* vector_at() */
        {
        }
        /* vector_front() */
        {
        }
        /* vector_back() */
        {
        }
        /* vector_begin() */
        {
        }
        /* vector_end() */
        {
        }
        /* vector_insert() */
        {
        }
        /* vector_insert_n() */
        {
        }
        /* vector_insert_range() */
        {
        }
        /* vector_push_back() */
        {
        }
        /* vector_pop_back() */
        {
        }
        /* vector_erase() */
        {
        }
        /* vector_erase_range() */
        {
        }
        /* vector_clear() */
        {
        }
        /* vector_resize() */
        {
        }
        /* vector_resize_elem() */
        {
        }
    }
}

/** local function implementation section **/
static void _abc_init(const void* cpv_input, void* pv_output)
{
    abc_t* pt_input = (abc_t*)cpv_input;

    assert(cpv_input != NULL && pv_output != NULL);

    pt_input->_n_first = 0;
    pt_input->_d_second = 0.0;
    pt_input->_pc_third = (char*)malloc(sizeof(double));
    if(pt_input->_pc_third == NULL)
    {
        *(bool_t*)pv_output = false;
    }
    else
    {
        memset(pt_input->_pc_third, 0x00, sizeof(double));
        *(bool_t*)pv_output = true;
    }
}

static void _abc_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    abc_t* pt_first = (abc_t*)cpv_first;
    abc_t* pt_second = (abc_t*)cpv_second;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    pt_first->_n_first = pt_second->_n_first;
    pt_first->_d_second = pt_second->_d_second;
    memcpy(pt_first->_pc_third, pt_second->_pc_third, sizeof(double));
    *(bool_t*)pv_output = true;
}

static void _abc_less(const void* cpv_first, const void* cpv_second, void * pv_output)
{
    abc_t* pt_first = (abc_t*)cpv_first;
    abc_t* pt_second = (abc_t*)cpv_second;

    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    if(pt_first->_n_first < pt_second->_n_first &&
       pt_first->_d_second - pt_second->_d_second < DBL_EPSILON &&
       memcmp(pt_first->_pc_third, pt_second->_pc_third, sizeof(double)) < 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

static void _abc_destroy(const void* cpv_input, void* pv_output)
{
    abc_t* pt_input = (abc_t*)cpv_input;

    assert(cpv_input != NULL && pv_output != NULL);

    pt_input->_n_first = 0;
    pt_input->_d_second = 0.0;
    memset(pt_input->_pc_third, 0xcc, sizeof(double));
    free(pt_input->_pc_third);
    *(bool_t*)pv_output = true;
}

/** eof **/

