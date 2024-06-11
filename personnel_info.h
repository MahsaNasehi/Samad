#ifndef Y
#define Y
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ad
{
    char First_Name[15];
    char Last_Name[15];
    char username[15]; // username نام کاربری
    char passwrd[15];
    char national_id[15];
    char Birtdate[18];
    char Gender[8];
    char typee[15]; // admin || student
    int flag;       // 0 : not  approved  1: deactivated  3 : removed   4 : approved
    int price;
    int token_food_cnt;
    struct ad *next;
} proved_user;

proved_user *head_approved;
char admin[5] = "admin"; // this is the head of staff.
proved_user *head_of_admins()
{
    head_approved = (proved_user *)malloc(sizeof(proved_user));
    strcpy(head_approved->username, admin);
    strcpy(head_approved->passwrd, admin);
    strcpy(head_approved->typee, admin);
    head_approved->flag = 4;
    head_approved->next = NULL;
    return head_approved;
}

typedef struct meal_plan
{
    char self_id[15];
    char food_id[15];
    int year;
    int month;
    int day;
    char food_type[10];
    int food_cnt;
    struct meal_plan *next_meal;
} Meal_plan;

typedef struct self_info
{
    char id_self[15];
    char self_name[15];
    char self_location[15];
    char self_capacity[15];
    char self_gender[10];
    char meal[15];
    int lunch_hour_lim;
    int lunch_min_lim;
    int dinner_hour_lim;
    int dinner_min_lim;
    int komaki;
    Meal_plan *plan;
    struct self_info *next;
} selfs;

selfs *head_self;
selfs *array_of_self;

typedef struct food
{
    char id_food[15];
    char food_name[15];
    char food_kind[15];
    int food_price;
    struct food *next_food;
} Food;

Food *head_food_plan;

typedef struct time
{
    int t_year;
    int t_month;
    int t_day;
    int hour;
    int minute;
    int second;
} Time;

Time now;

#endif