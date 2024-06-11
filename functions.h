#include "personnel_info.h"
#include <stdlib.h>
#ifndef X
#define X
char log_user[15], password[15];
int user_identity = -1; // if     (user_identity == 1 -> admin)     (user_identity == 2 -> other personnels)     (user_identity == 3 -> student)
Time now;
void Time_Set()
{
    printf("\nEnter the year-month-day hour minute second: in two chars**\n");
    scanf("%d-%d-%d%2d%2d", &now.t_year, &now.t_month, &now.t_day, &now.hour, &now.minute);
    if ((now.t_month == 0 && now.t_day == 0 && now.hour == 0 && now.minute == 0 && now.second == 0) || (now.minute < 0))
    {
        printf("\nInvalid\n");
    }
    else
        printf("\n ------------Success-------------- \n");
    // printf("%d  %d  %d  %d  %d  %d", now.t_year, now.t_month, now.t_day, now.hour, now.minute, now.second);
}

proved_user *new_node(char first_name[], char last_name[], char us_id[], char password[], char na_id[], char birthdate[], char gender[], char type[], int komaki)
{
    proved_user *newNode = (proved_user *)malloc(sizeof(proved_user));
    strcpy(newNode->First_Name, first_name);
    strcpy(newNode->Last_Name, last_name);
    strcpy(newNode->username, us_id);
    strcpy(newNode->passwrd, password);
    strcpy(newNode->national_id, na_id);
    strcpy(newNode->Birtdate, birthdate);
    strcpy(newNode->Gender, gender);
    strcpy(newNode->typee, type);
    newNode->price = 0;
    if (komaki == 1)
    {
        newNode->flag = 4;
    }
    else
    {
        newNode->flag = 0;
    }
    newNode->token_food_cnt = 0;
    newNode->next = NULL;
    return newNode;
}
void add_node_to_approved(proved_user *newNode)
{
    proved_user *temp = head_approved;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

// proved_user *new_node_for_approved(char name[15], char password[15], char tp[], char F_Name[], char L_Name[])
// {
//     proved_user *newNode = (proved_user *)malloc(sizeof(proved_user));
//     strcpy(newNode->First_Name, F_Name);
//     strcpy(newNode->Last_Name, L_Name);
//     strcpy(newNode->username, name);
//     strcpy(newNode->passwrd, password);
//     strcpy(newNode->typee, tp);
//     newNode->price = 0;
//     newNode->flag = 0; // approved
//     newNode->token_food_cnt = 0;
//     newNode->next = NULL;
//     return newNode;
// }

selfs *new_node_self(char shenase[15], char name[15], char location[], char capacity[], char type[], char meal[], int L_H, int L_M, int D_H, int D_M)
{
    selfs *newNode = (selfs *)malloc(sizeof(selfs));
    strcpy(newNode->id_self, shenase);
    strcpy(newNode->self_name, name);
    strcpy(newNode->self_location, location);
    strcpy(newNode->self_capacity, capacity);
    strcpy(newNode->self_gender, type);
    strcpy(newNode->meal, meal);
    newNode->lunch_hour_lim = L_H;
    newNode->lunch_min_lim = L_M;
    newNode->dinner_hour_lim = D_H;
    newNode->dinner_min_lim = D_M;
    newNode->komaki = 0;
    newNode->plan = NULL;
    newNode->next = NULL;
    return newNode;
}

void add_node_self(selfs *head, selfs *newNode)
{
    selfs *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

Food *new_node_for_food(char id_food[15], char food_name[15], char type[15], int price)
{
    Food *newNode = (Food *)malloc(sizeof(Food));
    strcpy(newNode->id_food, id_food);
    strcpy(newNode->food_name, food_name);
    strcpy(newNode->food_kind, type);
    newNode->food_price = price;
    newNode->next_food = NULL;
    return newNode;
}

void add_food_node(Food *head, Food *newNode)
{
    Food *temp = head;
    while (temp->next_food != NULL)
        temp = temp->next_food;

    temp->next_food = newNode;
}

char user[20], first_name[15], last_name[15], us_id[15], password[15], na_id[15], birthdate[18], gender[8], type[8];
void get_info()
{
    printf("Enter your first_name:\n");
    scanf("%s", first_name);
    printf("Enter your last_name:\n");
    scanf("%s", last_name);
    printf("your user_id:\n");
    scanf("%s", us_id);
    printf("your password:\n");
    scanf("%s", password);
    printf("your national-id-code:\n");
    scanf("%s", na_id);
    printf("your birthdate: year-month-day\n");
    scanf("%s", birthdate);
    printf("your gender:\n");
    scanf("%s", gender);
    printf("your type:\n");
    scanf("%s", type);
}

int check_if_not_registered(char us_id[], char password[])
{
    proved_user *curr;
    for (curr = head_approved; curr != NULL; curr = curr->next)
    {
        if (strcmp(curr->passwrd, password) == 0 && strcmp(curr->username, us_id) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void regist(char first_name[], char last_name[], char us_id[], char password[], char na_id[], char birthdate[], char gender[], char type[], int user_identity)
{

    if (check_if_not_registered(us_id, password))
    {
        printf("\n---------------------------Registered before!-------------------------\n");
        return;
    }
    if (user_identity == 1 || user_identity == 2)
    {
        add_node_to_approved(new_node(first_name, last_name, us_id, password, na_id, birthdate, gender, type, 1));
        print_to_file(); // if the person is registered by admin, it doesn't need to be approved.
        printf("\n-------------------success-------------------\n");
    }
    else
    {
        add_node_to_approved(new_node(first_name, last_name, us_id, password, na_id, birthdate, gender, type, 0));
        printf("\n-------------------success-------------------\n");
    }
}
int show_wait_list()
{
    proved_user *curr;
    int i;
    int success = 0;
    for (i = 1, curr = head_approved->next; curr != NULL; curr = curr->next)
    {
        if (curr->flag != 4)
        {
            printf("%d . %s %s %s %s %s %s %s %s\n", i, curr->First_Name, curr->Last_Name, curr->username, curr->passwrd, curr->national_id, curr->Birtdate, curr->Gender, curr->typee);
            success = 1;
            i++;
        }
    }
    if (success == 1)
    {
        int num_to_be_proved;
        scanf("%d", &num_to_be_proved);
        if (num_to_be_proved > i)
        {
            printf("\n---Incorrect input---\n");
            return 0;
        }
        return num_to_be_proved;
    }
    else
        return 0;
}

void print_to_file()
{
    FILE *approved_data = fopen("approveds.txt", "w");
    if (approved_data == NULL)
    {
        exit(0);
    }
    proved_user *curr;
    for (curr = head_approved; curr != NULL; curr = curr->next)
    {
        if (curr->flag == 4)
        {
            char pass[15], USER_name[15], TYPE[15];
            strcpy(USER_name, curr->username);
            strcpy(pass, curr->passwrd);
            strcpy(TYPE, curr->typee);
            fprintf(approved_data, "%s %s %s\n", USER_name, pass, TYPE);
        }
    }
    fclose(approved_data);
}

void find_node(int index) // find the node for approvement
{
    int i;
    proved_user *curr = head_approved->next;
    for (i = 0; i < index - 1; curr = curr->next)
    {
        if (curr->flag != 4)
        {
            i++;
        }
    }
    while (curr->flag == 4) // curr->flag == 4 : approved
    {
        curr = curr->next;
    }
    if (curr->flag != 4)
    {
        curr->flag = 4;
    }
    print_to_file();
}

void approve(int indx_of_stu_to_be_proved)
{
    if (user_identity == 1 || user_identity == 2)
    {
        find_node(indx_of_stu_to_be_proved);
        printf("\nSuccess\n");
    }
    else if (user_identity == 3)
    {
        printf("permission denied");
        /*permission denied*/
    }
}

void login(char user_name[], char pasw[])
{
    char temp[50], stud[] = "student";
    int komaki = 0;
    char admin[6] = "admin";
    FILE *approved_data = fopen("approveds.txt", "r");
    while (fgets(temp, 49, approved_data) != NULL)
    {
        if (strstr(temp, user_name) != NULL && strstr(temp, pasw) != NULL)
        {
            if (strstr(temp, admin)) // Admin
            {
                user_identity = 2;
            }
            else if (strstr(temp, stud) != NULL) // Student
            {
                user_identity = 3;
            }
            komaki = 0;
            printf("\n#################### Welcome ######################\n\n");
            break;
        }
        else if (strstr(temp, user_name) != NULL && strstr(temp, pasw) == NULL)
        {
            komaki = 1;
            break;
        }
        else
            komaki = 2;
    }
    if (komaki == 1)
    {
        printf("\n-------------------Incorrect pass---------------------\n");
    }
    else if (komaki == 2)
    {
        printf("\nAccount not found, plz signup or maybe you are deactivated or removed!!:)\n");
    }
}

void logout()
{
    printf("\nEnter your username\n");
    char user_name[10];
    scanf("%s", user_name);
    if (strcmp(log_user, user_name) == 0)
    {
        user_identity = -1;
    }
    else
        printf("\n-------Not found--------\n");
}

void change_pass_of_node(proved_user *head_ref, char prev_pass[], char New_pass[], int komaki)
{
    proved_user *curr;
    int i = 0;
    for (curr = head_ref; curr != NULL; curr = curr->next)
    {
        if (komaki == 1)
        {
            if (strcmp(curr->username, prev_pass) == 0 && strcmp(curr->typee, admin) != 0) // chaging the student's pass by admin
            {
                strcpy(curr->passwrd, New_pass);
                i = 1; // bayad print to file shavad
                break;
            }
        }
        else if (komaki == 2)
        {
            if (strcmp(curr->passwrd, prev_pass) == 0 && strcmp(curr->typee, admin) != 0) // chaging the stu's pass by him/herself
            {
                strcpy(curr->passwrd, New_pass);
                i = 1; // bayad print to file shavad
                break;
            }
        }
        else if (komaki == 3)
        {
            if (strcmp(curr->passwrd, prev_pass) == 0) // chaging the admin's pass by him/herself
            {
                strcpy(curr->passwrd, New_pass);
                i = 1; // bayad print to file shavad
                break;
            }
        }
    }

    if (i == 1)
    {
        print_to_file();
        printf("success");
    }
    else
        printf("Not found / that user maybe an admin and you can't change the pass\n");
    return;
}

void change_admin_pass()
{
    char entering_pass[15];
    printf("\nEnter your prev_password:\n");
    int p = 0;
    do
    {
        entering_pass[p] = getch();
        if (entering_pass[p] != '\r')
        {
            printf("*"); // **********************emtiazi*************************
        }
        p++;
    } while (entering_pass[p - 1] != '\r');
    entering_pass[p - 1] = '\0';

    if (strcmp(entering_pass, password) == 0)
    {
        printf("\nEnter the new password:\n");
        p = 0;
        char new_pass[15];
        do
        {
            new_pass[p] = getch();
            if (new_pass[p] != '\r')
            {
                printf("*"); // **********************emtiazi*************************
            }
            p++;
        } while (new_pass[p - 1] != '\r');

        printf("\nIf you want your new password to be shown, enter 1, else enter 0:\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\n You have entered as password:");
            printf("%s\n", new_pass);
        }
        change_pass_of_node(head_approved, entering_pass, new_pass, 3);
    }
    else
    {
        printf("\nIncorrect password\n");
    }
}

void change_pass()
{
    char entering_pass[15];
    printf("\nEnter your prev_password:\n");
    int p = 0;
    do
    {
        entering_pass[p] = getch();
        if (entering_pass[p] != '\r')
        {
            printf("*"); // **********************emtiazi*************************
        }
        p++;
    } while (entering_pass[p - 1] != '\r');
    entering_pass[p - 1] = '\0';

    if (strcmp(entering_pass, password) == 0)
    {
        printf("\nEnter the new password:\n");
        p = 0;
        char new_pass[15];
        do
        {
            new_pass[p] = getch();
            if (new_pass[p] != '\r')
            {
                printf("*"); // ***********************emtiazi*************************
            }
            p++;
        } while (new_pass[p - 1] != '\r');

        printf("\nIf you want your new password to be shown, enter 1, else enter 0:\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nYou have entered as password:");
            printf("%s\n", new_pass);
        }
        change_pass_of_node(head_approved, entering_pass, new_pass, 2);
    }
    else
    {
        printf("\nIncorrect password\n");
    }
}

void change_stu_pass()
{
    char new_pass[15], user_name[15];
    printf("Enter the username of the student:\n");
    scanf("%s", user_name);
    printf("Enter the new password that you've chosen for the student:\n");
    int p = 0;
    do
    {
        new_pass[p] = getch();
        if (new_pass[p] != '\r')
        {
            printf("*"); // **********************emtiazi*************************
        }
        p++;
    } while (new_pass[p - 1] != '\r');
    printf("\nIf you want your new password to be shown, enter 1, else enter 0:\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("\nYou have entered as password:");
        printf("%s\n", new_pass);
    }
    change_pass_of_node(head_approved, user_name, new_pass, 1);
}

void delete_or_deactivate_node(char username[], int recg_remove_or_deactivate)
{
    proved_user *temp = head_approved->next;
    proved_user *prev = head_approved;
    if (recg_remove_or_deactivate != 0) // deactivation
    {
        while (temp != NULL)
        {
            if (strcmp(temp->username, username) == 0)
            {
                temp->flag = 1;
                break;
            }
            temp = temp->next;
        }
    }
    else
    { // removing
        while (temp != NULL)
        {
            if (strcmp(temp->username, username) == 0)
            {
                temp->flag = 3; // removed
                break;
            }
            temp = temp->next;
        }
    }
    print_to_file();
}

void remove_stu()
{
    char remo_stu_id[15];
    printf("Enter the user_name of student:\n");
    scanf("%s", remo_stu_id);
    delete_or_deactivate_node(remo_stu_id, 0); // remove
    print_to_file();
}

void deactivate_stu()
{
    char remo_stu_id[15];
    printf("Enter the user_name of student:\n");
    scanf("%s", remo_stu_id);
    delete_or_deactivate_node(remo_stu_id, 1); // deactivate //no need to print to file again, check the flag
    print_to_file();                           /// shak daram, check shavad
}

selfs *define_self(char id_self[15], char self_name[15], char self_location[15], char self_capacity[15], char self_gender[10], char meal[15], int L_H, int L_M, int D_H, int D_M)
{
    static int i = 0;
    if (i == 0)
    {
        head_self = new_node_self(id_self, self_name, self_location, self_capacity, self_gender, meal, L_H, L_M, D_H, D_M);
    }
    else
    {
        add_node_self(head_self, new_node_self(id_self, self_name, self_location, self_capacity, self_gender, meal, L_H, L_M, D_H, D_M));
    }
    i++;
    return head_self;
}

selfs *check_self_id_newnode(char shenase[15])
{
    for (selfs *curr_self = head_self; curr_self != NULL; curr_self = curr_self->next)
    {
        if (strcmp(shenase, curr_self->id_self) == 0)
        {
            printf("\n--------Done---------\n");
            return curr_self;
        }
    }
    printf("\nInvalid input\n");
    return NULL;
}

int check_food_id(char shenase[])
{
    Food *curr = head_food_plan;
    for (; curr != NULL; curr = curr->next_food)
    {
        if (strcmp(shenase, curr->id_food) == 0)
        {
            printf("\n--------That Food is found---------\n");
            return 1;
        }
    }
    printf("\nInvalid input/ That food isn't found\n");
    return 0;
}

void create_meal_node(selfs *curr_self, char shenase[15], char food_id[15], int Year, int Month, int Day, char type[15], int count)
{
    if (curr_self->komaki == 0)
    {
        curr_self->plan = (Meal_plan *)malloc(sizeof(Meal_plan));
        strcpy(curr_self->plan->self_id, shenase);
        strcpy(curr_self->plan->food_id, food_id);
        curr_self->plan->year = Year;
        curr_self->plan->month = Month;
        curr_self->plan->day = Day;
        strcpy(curr_self->plan->food_type, type);
        curr_self->plan->food_cnt = 0;
        curr_self->plan->food_cnt += count;
        curr_self->plan->next_meal = NULL;
        curr_self->komaki = 1;
    }
    else
    {
        while (curr_self->plan->next_meal != NULL)
        {
            curr_self->plan = curr_self->plan->next_meal;
        }
        curr_self->plan->next_meal = (Meal_plan *)malloc(sizeof(Meal_plan));
        strcpy(curr_self->plan->next_meal->self_id, shenase);
        strcpy(curr_self->plan->next_meal->food_id, food_id);
        curr_self->plan->next_meal->year = Year;
        curr_self->plan->next_meal->month = Month;
        curr_self->plan->next_meal->day = Day;
        strcpy(curr_self->plan->next_meal->food_type, type);
        curr_self->plan->next_meal->food_cnt = 0;
        curr_self->plan->next_meal->food_cnt += count;
        curr_self->plan->next_meal->next_meal = NULL;
    }
}

void print_food_name(char shenase_food[15])
{
    for (Food *curr = head_food_plan; curr != NULL; curr = curr->next_food)
    {
        if (strcmp(shenase_food, curr->id_food) == 0)
        {
            printf(" %s ", curr->food_name);
        }
    }
}

int Type_recg(char username[]) // checking if the type of the self is the same with stu's gender
{
    proved_user *curr = head_approved;
    char gender1[9] = "female", gender2[9] = "male";
    for (; curr != NULL; curr = curr->next)
    {
        if (strcmp(curr->username, username) == 0)
        {
            if (strcmp(curr->Gender, gender1) == 0)
            {
                return 1;
            }
            else if (strcmp(curr->Gender, gender2) == 0)
            {
                return 2;
            }
        }
    }
}

int check_id(char shenase_food[15], char shenase_self[15])
{
    char self_gender1[9] = "girlish", self_gender2[9] = "boyish", gender1[9] = "female", gender2[9] = "male";
    for (selfs *curr = head_self; curr != NULL; curr = curr->next)
    {
        if (strcmp(shenase_self, curr->id_self) == 0 && strcmp(shenase_food, curr->plan->food_id) == 0)
        {
            if (strcmp(curr->self_gender, self_gender1) == 0 && Type_recg(log_user) == 1)
            {
                return 1;
            }
            else if (strcmp(curr->self_gender, self_gender2) == 0 && Type_recg(log_user) == 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int define_food(char id_food[], char food_name[], char kind_food[], int cost)
{
    static int i = 0;
    if (i == 0)
    {
        head_food_plan = new_node_for_food(id_food, food_name, kind_food, cost);
        i++;
        return 1;
    }
    else
    {
        add_food_node(head_food_plan, new_node_for_food(id_food, food_name, kind_food, cost));
        return 1;
    }
    return 0;
}

void define_meal_plan(selfs *curr_self, char self_id[15], char food_id[15], int year, int month, int day, char type[15], int count)
{
    create_meal_node(array_of_self, self_id, food_id, year, month, day, type, count);
}

void ATM()
{
    printf("\nplz enter your info of bank account:\n");
    char bank_account[12], account_pass[6];
    scanf("%s %s", bank_account, account_pass);
}

int search_price_in_foodtable(char food_id[])
{
    for (Food *curr = head_food_plan; curr != NULL; curr = curr->next_food)
    {
        if (strcmp(curr->id_food, food_id) == 0)
        {
            return curr->food_price;
        }
    }
    return 0;
}

int search_in_approved_by_username(char username[], int price, int addprice_or_checkprice)
{
    for (proved_user *curr = head_approved->next; curr != NULL; curr = curr->next)
    {
        if (addprice_or_checkprice == 0)
        {
            if (strcmp(username, curr->username) == 0) // charging the account
            {
                ATM();
                curr->price += price;
                printf("\n------------Charged------------\n");
                return 1;
            }
            else
                printf("\n------Incorrect Input--------\n");
        }
        else if (addprice_or_checkprice == 1) // check if there is enough money in stu's account
        {
            if (strcmp(username, curr->username) == 0)
            {
                if (curr->price > 0)
                {
                    return 1;
                }
                return 0;
            }
        }
        else if (addprice_or_checkprice == 2) // reduce the bought_food frime stu's accounr
        {
            if (strcmp(username, curr->username) == 0) // charging the account
            {
                curr->price -= price;
            }
        }
        else if (addprice_or_checkprice == 3) // add to token food
        {

            if (strcmp(username, curr->username) == 0) // charging the account
            {
                curr->token_food_cnt += 1;
            }
        }
        else if (addprice_or_checkprice == 4)
        {
            if (strcmp(username, curr->username) == 0) // charging the account
            {
                printf("\n%s %s\n", curr->First_Name, curr->Last_Name);
            }
        }
        else if (addprice_or_checkprice == 5)
        {
            if (strcmp(username, curr->username) == 0) // charging the account
            {
                curr->price += price;
                return 1;
            }
        }
        else if (addprice_or_checkprice == 6)
        {
            if (strcmp(username, curr->username) == 0) // charging the account
            {
                if (curr->price - price > 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void charge_stu_account(char user_name[15], long amount)
{
    search_in_approved_by_username(user_name, amount, 0);
}

// check time
int year_cmp(Time t1, int Year, int Month, int Day)
{
    if (t1.t_year < Year)
        return 1;
    else if (t1.t_year > Year)
        return 0;
    else if (t1.t_month < Month)
        return 1;
    else if (t1.t_month > Month)
        return 0;
    else if (t1.t_day < Day)
        return 1;
    else if (t1.t_day > Day)
        return 0;
    else
        return 0;
}

// add news
void add_news()
{
    char subject[30];
    char matn[1000];
    char date[10];
    printf("\nEnter subject, date(year-month-day), and the body:\n");
    getchar();
    gets(subject);
    gets(date);
    gets(matn);
    FILE *news;
    news = fopen("news.txt", "a");
    fprintf(news, "%s\n%s\n %s\n", subject, date, matn);
    fclose(news);
}

// for add poll
void add_poll()
{
    FILE *poll;
    poll = fopen("poll.txt", "a");
    if (user_identity == 2 || user_identity == 1) // manager or student?
    {
        char str[100], str1[50], date[11];
        printf("\nand what's the expiration date?\n");
        getchar();
        gets(date);
        fprintf(poll, "%s\n", date);
        printf("\nplz enter the question:\n");
        gets(str); // soal chi hast
        fprintf(poll, "%s\n", str);
        int i = 0; // n baraye tedad gozineha
        printf("\nplz enter the options:\n");
        for (i = 1; i < 5; i++)
        {
            printf("%d.", i);
            gets(str1);
            fprintf(poll, "%s\n", str1);
        }
        fclose(poll);
    }
    else
        printf("you can not add poll");
}

void vote()
{
    FILE *poll;
    poll = fopen("poll.txt", "r");
    char temp[200];
    int Year, Month, Day;
    while (fgets(temp, 100, poll) != NULL)
    {
        sscanf(temp, "%d-%d-%d", &Year, &Month, &Day);
        if (year_cmp(now, Year, Month, Day))
            puts(temp);
        {
            while (fgets(temp, 100, poll) != NULL)
            {
                sscanf(temp, "%d-%d-%d", &Year, &Month, &Day);
                if (year_cmp(now, Year, Month, Day))
                {
                    puts(temp);
                }
            }
        }
    }
    fclose(poll);
    printf("\nYour choice? 1 - 2 - 3 - 4:\n");
    int choice;
    scanf("%d", &choice);
    if (choice > 4 || choice < 1)
    {
        printf("\nInvalid Input\n");
    }
}

void show_File_of_food_selves()
{
    selfs *curr;
    printf("\nself_name   self_gender   id_self   food_name   food_id   food_count\n");
    for (curr = head_self; curr != NULL; curr = curr->next)
    {
        if (curr->plan != NULL)
        {
            printf("%s %s %s ", curr->self_name, curr->self_gender, curr->id_self);
            print_food_name(curr->plan->food_id);
            printf("%s %d\n", curr->plan->food_id, curr->plan->food_cnt);
            while (curr->plan->next_meal != NULL)
            {
                printf("%s %s %s ", curr->self_name, curr->self_gender, curr->id_self);
                print_food_name(curr->plan->next_meal->food_id);
                printf("%s %d\n", curr->plan->next_meal->food_id, curr->plan->next_meal->food_cnt);
                curr->plan = curr->plan->next_meal;
            }
        }
    }
}

void reserve(char self_id[], char food_id[]) /// adam mojavez jens mokhalef
{
    FILE *fp = fopen("reservations.txt", "a");
    FILE *fp1 = fopen("reservations_for_admin.txt", "a");
    int decreased_price = 0;
    if (check_id(food_id, self_id))
    {
        if (search_in_approved_by_username(log_user, 0, 1)) // if there is enough money in the account
        {
            for (selfs *curr_self = head_self; curr_self != NULL; curr_self = curr_self->next)
            {
                if (strcmp(self_id, curr_self->id_self) == 0)
                {
                    curr_self->plan->food_cnt -= 1;
                }
                decreased_price = search_price_in_foodtable(food_id);
                search_in_approved_by_username(log_user, decreased_price, 2);
                printf("\n--------------reserved----------------\n");
                char str[] = "reservation";
                fprintf(fp, "%s %s %d %s %s\n", log_user, str, decreased_price, food_id, self_id);
                fprintf(fp1, "%s %s %d %s %s\n", log_user, str, decreased_price, food_id, self_id);
            }
        }
        else
        {
            printf("\nCharge your account:\n");
            printf("\nEnter the amount of money, else if you want your account to be charged as much as the cost of food, enter zero:\n");
            int amount;
            scanf("%d", &amount);
            if (amount == 0)
            {
                amount = decreased_price;
            }
            search_in_approved_by_username(log_user, amount, 0);
            reserve(self_id, food_id);
        }
    }
    else
    {
        printf("\nInvalid input or the gender of the self isn't the same with yours\n");
    }
    fclose(fp);
}

void cancel_rezervation(int Year, int Month, int Day, char meal[15])
{
    FILE *fp = fopen("reservations.txt", "r+");
    char temp[100];
    int amount;
    if (year_cmp(now, Year, Month, Day) && Day >= now.t_day + 2)
    {
        while (fscanf(fp, "%s", temp) > 0)
        {
            if (strstr(temp, log_user) != NULL)
            {
                sscanf(temp, "%d", &amount);
                search_in_approved_by_username(log_user, amount, 5); // givig back the amoney
                printf("\n----------------Canceled-----------------\n");
                char temp2[] = "Cancelation";
                fprintf(fp, "%s %s %d", temp2, meal, amount);
            }
        }
    }
}

void reservation_data_for_admin()
{
    FILE *fp = fopen("reservations_for_admin.txt", "r+");
    char temp[100];
    while (fscanf(fp, "%s", temp) > 0)
    {
        printf("%s\n", temp);
    }
    printf("\nafter serving\n");
}

void report_financial()
{
    FILE *fp1 = fopen("reservations.txt", "r");
    FILE *fp2 = fopen("charge.txt", "r");
    FILE *fp3 = fopen("Send_charge.txt", "r");
    char temp[100];
    while (fscanf(fp1, "%s", temp) > 0)
    {
        if (strstr(temp, log_user) != NULL)
        {
            printf("%s", temp);
        }
    }
    while (fscanf(fp2, "%s", temp) > 0)
    {
        if (strstr(temp, log_user) != NULL)
        {
            printf("%s", temp);
        }
    }
    while (fscanf(fp3, "%s", temp) > 0)
    {
        if (strstr(temp, log_user) != NULL)
        {
            printf("%s", temp);
        }
    }
}

void stu_report_for_admin()
{
    printf("\nplz enter the student's username:\n");
    char use_name[15];
    scanf("%s", use_name);
    FILE *fp1 = fopen("reservations.txt", "r");
    FILE *fp2 = fopen("charge.txt", "r");
    FILE *fp3 = fopen("Send_charge.txt", "r");
    FILE *fp4 = fopen("token_food.txt", "r");
    char temp[100];
    while (fscanf(fp1, "%s", temp) > 0)
    {
        if (strstr(temp, use_name) != NULL)
        {
            printf("%s", temp);
        }
    }
    while (fscanf(fp2, "%s", temp) > 0)
    {
        if (strstr(temp, use_name) != NULL)
        {
            printf("%s", temp);
        }
    }
    while (fscanf(fp3, "%s", temp) > 0)
    {
        if (strstr(temp, use_name) != NULL)
        {
            printf("%s", temp);
        }
    }
    while (fscanf(fp4, "%s", temp) > 0)
    {
        if (strstr(temp, use_name) != NULL)
        {
            printf("%s", temp);
        }
    }
}

// for check_news
void check_news()
{
    int Year, Month, Day;
    FILE *nptr;
    nptr = fopen("news.txt", "r");
    char temp[100];
    while (fgets(temp, 100, nptr) != NULL)
    {
        sscanf(temp, "%d-%d-%d", &Year, &Month, &Day);
        if (year_cmp(now, Year, Month, Day))
            puts(temp);
        {
            while (fgets(temp, 100, nptr) != NULL)
            {
                sscanf(temp, "%d-%d-%d", &Year, &Month, &Day);
                if (year_cmp(now, Year, Month, Day))
                {
                    puts(temp);
                }
            }
        }
    }
    fclose(nptr);
}

void take_food(char id_self[15], int Year, int Month, int Day)
{
    FILE *fp1 = fopen("token_food.txt", "a");
    if (user_identity == 3)
    {
        if (year_cmp(now, Year, Month, Day))
        {
            search_in_approved_by_username(log_user, 0, 3);
            printf("\nsuccess\n");
            fprintf(fp1, "%s %d %d %d", id_self, Year, Month, Day);
            return;
        }
        else
            printf("\n-----------Wrong day----------\n");
    }
    else
        printf("\nplz login\n");
}

void charge_account()
{
    FILE *fp = fopen("charge.txt", "a");
    char charge_account[] = "Charge your own account";
    if (user_identity == 3)
    {
        printf("\nEnter the amount of money:\n");
        int amount;
        scanf("%d", &amount);
        search_in_approved_by_username(log_user, amount, 0);
        fprintf(fp, "%s %s %d", charge_account, log_user, amount);
        return;
    }
    printf("\nplz login\n");
}

void send_charge(char classmate_username[])
{
    FILE *fp = fopen("Send_charge.txt", "a");
    char charge_account[] = "Send charge";
    search_in_approved_by_username(classmate_username, 0, 4);
    printf("\nAre you sure to continue the operation:\n yep ? enter 1, else enter 0\n");
    int continue_or_not;
    scanf("%d", &continue_or_not);
    if (continue_or_not == 1)
    {
        printf("\nEnter the amount of money, else if you want your account to be charged as much as the cost of food, enter zero:\n");
        int amount;
        scanf("%d", &amount);
        ;
        if (search_in_approved_by_username(log_user, amount, 6))
        {
            search_in_approved_by_username(log_user, amount, 0);
            fprintf(fp, "%s %s %d", charge_account, log_user, amount);
        }
        else
        {
            printf("\nNot enough money\n");
        }
    }
}

void daily_reserve(char self_id[], char food_id[])
{
    FILE *fp = fopen("reservations.txt", "a");
    FILE *fp1 = fopen("reservations_for_admin.txt", "a");
    int decreased_price = 0;
    if (check_id(food_id, self_id))
    {
        if (search_in_approved_by_username(log_user, 0, 1)) // if there is enough money in the account
        {
            for (selfs *curr_self = head_self; curr_self != NULL; curr_self = curr_self->next)
            {
                if (strcmp(self_id, curr_self->id_self) == 0)
                {
                    curr_self->plan->food_cnt -= 1;
                }
                decreased_price = search_price_in_foodtable(food_id);
                search_in_approved_by_username(log_user, 2 * decreased_price, 2); // (2 * decreased_price) : the daily reserve costs twice.
                printf("\n--------------reserved----------------\n");
                char str[] = "reservation";
                fprintf(fp, "%s %s %d %s %s\n", log_user, str, decreased_price, food_id, self_id);
                fprintf(fp1, "%s %s %d %s %s\n", log_user, str, decreased_price, food_id, self_id);
            }
        }
        else
        {
            printf("\nCharge your account:\n");
            printf("\nEnter the amount of money, else if you want your account to be charged as much as the cost of food, enter zero:\n");
            int amount;
            scanf("%d", &amount);
            if (amount == 0)
            {
                amount = decreased_price;
            }
            search_in_approved_by_username(log_user, amount, 0);
            reserve(self_id, food_id);
        }
    }
    else
    {
        printf("\nInvalid input or the gender of the self isn't the same with yours\n");
    }
    fclose(fp);
}

#endif