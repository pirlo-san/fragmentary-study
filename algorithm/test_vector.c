#include "test_api.h"
#include "vector.h"

typedef struct
{
    int  no;
    char name[100];
}player_t;

int compare_player(const void *p1, const void *p2)
{
    const player_t *player1 = (const player_t *)*(const int *)p1;
    const player_t *player2 = (const player_t *)*(const int *)p2;

    return player1->no - player2->no;
}

static void vector_test_case01(void)
{
    int vid = -1;
    ASSERT_EQUAL_INT(e_vector_success, vector_alloc(compare_player, &vid));

    player_t p[5] = 
    {
        {3, "maldini"},
        {22, "kaka"},
        {10, "seedorf"},
        {21, "pirlo"},
        {13, "nesta"}
    };
    ASSERT_EQUAL_INT(e_vector_success, vector_push_back(vid, &p[0]));
    ASSERT_EQUAL_INT(e_vector_success, vector_push_back(vid, &p[1]));
    ASSERT_EQUAL_INT(e_vector_success, vector_push_back(vid, &p[2]));    
    ASSERT_EQUAL_INT(e_vector_success, vector_push_back(vid, &p[3]));  
    ASSERT_EQUAL_INT(e_vector_success, vector_push_back(vid, &p[4]));  

    ASSERT_EQUAL_INT(5, vector_size(vid));
    ASSERT_EQUAL_PTR(&p[0], vector_at(vid, 0));
    ASSERT_EQUAL_PTR(&p[1], vector_at(vid, 1));
    ASSERT_EQUAL_PTR(&p[2], vector_at(vid, 2));
    ASSERT_EQUAL_PTR(&p[3], vector_at(vid, 3));
    ASSERT_EQUAL_PTR(&p[4], vector_at(vid, 4));

    ASSERT_EQUAL_INT(e_vector_success, vector_sort(vid, compare_player));
    ASSERT_EQUAL_INT(5, vector_size(vid));
    ASSERT_EQUAL_PTR(&p[0], vector_at(vid, 0));
    ASSERT_EQUAL_PTR(&p[2], vector_at(vid, 1));
    ASSERT_EQUAL_PTR(&p[4], vector_at(vid, 2));
    ASSERT_EQUAL_PTR(&p[3], vector_at(vid, 3));
    ASSERT_EQUAL_PTR(&p[1], vector_at(vid, 4));    

    ASSERT_EQUAL_INT(e_vector_success, vector_free(vid));
}

void vector_test_cases(void)
{
    vector_test_case01();
}

