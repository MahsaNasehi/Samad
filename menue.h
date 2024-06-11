#include "functions.h"
#include <stdbool.h>
#include <conio.h>
int command_num, num_proved;
void menu()
{
    while (1)
    {
        if (user_identity == -1) // first page
        {
            printf("\nCommands:\n1.Register\n2.Login\n3.Change date time\n4.Logout\n"); // menu
            scanf("%d", &command_num);
            switch (command_num)
            {
            case 1: // regis
                get_info();
                regist(first_name, last_name, us_id, password, na_id, birthdate, gender, type, user_identity);
                break;
            case 2: // login
                printf("Enter your username:\n");
                scanf("%s", log_user);
                printf("password:\n");
                int p = 0;
                do
                {
                    password[p] = getch();
                    if (password[p] != '\r')
                    {
                        printf("*"); // ***********************************emtiazi**************************************
                    }
                    p++;
                } while (password[p - 1] != '\r');
                password[p - 1] = '\0';
                login(log_user, password);
                break;
            case 3:
                Time_Set();
                break;
            case 4:
                printf("\nEnter your username\n");
                char user_name[10];
                scanf("%s", user_name);
                printf("\n-------Not found--------\n");
                break;
            }
        }
        if (user_identity == 1 || user_identity == 2)
        {
            char id_self[15], self_name[15], self_location[15], self_capacity[15], self_gender[10], meal[15], id_food[15], food_name[15], kind_food[15], self_id[15], food_id[15], typeu[15], user_name[15];
            int lunch_time_1, lunch_time_2, dinner_time_1, dinner_time_2, cost, count, Year, Month, Day, amount;
            printf("\n----------------\nCommands:\n1.Register\n2.Approve\n3.Login\n4.Logout\n5.Change Pass\n6.Change Student_Pass\n7.Remove student\n8.Deactivate stu\n9.Define self\n10.Define food\n11.Define meal plan\n12.Charge student account\n16.Add news\n17.Add poll\n18.Change date time\n19.Reservation datas\nPLZ enter your choice_num:\n"); // menu
            scanf("%d", &command_num);
            switch (command_num)
            {
            case 1: // regis
                get_info();
                regist(first_name, last_name, us_id, password, na_id, birthdate, gender, type, user_identity);
                break;
            case 2: // approve
                num_proved = show_wait_list();
                if (num_proved)
                {
                    approve(num_proved);
                }
                else
                    printf("\nThere is no one to be registered yet.\n\n");

                break;
            case 3:
                printf("\nYou are already logged in!\n\n");
                break;
            case 4:
                logout();
                break;
            case 5:
                change_admin_pass();
                break;
            case 6:
                change_stu_pass(); //**************************emtiazi*****************************
                break;
            case 7:
                if (user_identity == 1 || user_identity == 2)
                {
                    remove_stu();
                }
                break;
            case 8:
                if (user_identity == 1 || user_identity == 2)
                {
                    deactivate_stu();
                }
                break;
            case 9:
                printf("\nplz enter the details:\n");
                scanf("%s %s %s %s %s %s %4d%4d%4d%4d", id_self, self_name, self_location, self_capacity, self_gender, meal, &lunch_time_1, &lunch_time_2, &dinner_time_1, &dinner_time_2);
                head_self = define_self(id_self, self_name, self_location, self_capacity, self_gender, meal, lunch_time_1, lunch_time_2, dinner_time_1, dinner_time_2);
                break;
            case 10:
                printf("\nEnter id_food, food_name, kind_food, cost\n");
                scanf("%s %s %s %d", id_food, food_name, kind_food, &cost);
                if (define_food(id_food, food_name, kind_food, cost))
                {
                    printf("\n++++++++++++++++ Done +++++++++++++++++\n");
                }
                else
                    printf("\n++++++++++++++++ Error accured +++++++++++++++++\n");
                break;
            case 11:
                printf("\nplz enter the id of the self:\n");
                scanf("%s", self_id);
                printf("\nplz enter the id of the meal:\n");
                scanf("%s", food_id);
                printf("\nplz enter the date:year-month-date\n");
                scanf("%d-%d-%d", &Year, &Month, &Day);
                printf("\nplz enter the meal_type :\n");
                scanf("%s", type);
                printf("\nplz enter the count of food:\n");
                scanf("%d", &count);
                array_of_self = check_self_id_newnode(self_id);
                if (array_of_self != NULL  &&  check_food_id(food_id))
                {
                    define_meal_plan(array_of_self, self_id, food_id, Year, Month, Day, typeu, count);
                }
                else
                {
                    printf("\n--------- Error ----------\n");
                }
                break;
            case 12:
                printf("\nEnter username and amount of money:\n");
                scanf("%s %d", user_name, &amount);
                charge_stu_account(user_name, amount);
                break;
            case 16:
                add_news();
                break;
            case 17:
                add_poll();
                break;
            case 18:
                Time_Set();
                break;
            case 19:
                reservation_data_for_admin();
                break;
            }
        }
        if (user_identity == 3)
        {
            char id_self[15], id_food[15], id_self2[15], friend_username[15], meal[15];
            int Year, Month, Day;
            printf("\n----------------------\nCommands:\n1.Logout\n2.Change Pass\n3.Reserve food\n4.Take food\n5.Charge account\n6.Send charge\n7.Change date time\n8.Reservation report\n9.Cancel reservation\n10.Check news\n11.Vote\n12.Daily reserve\nPLZ enter your choice_num:\n"); // menu
            scanf("%d", &command_num);
            switch (command_num)
            {
            case 1:
                logout();
                break;
            case 2:
                change_pass();
                break;
            case 3:
                show_File_of_food_selves();
                printf("\nplz enter id_self & id_food:\n");
                scanf("%s %s", id_self2, id_food);
                reserve(id_self2, id_food); 
                break;
            case 4:
                printf("\nplz enter id_self & date:\n");
                scanf("%s %4d%2d%2d", id_self, &Year, &Month, &Day);
                take_food(id_self2, Year, Month, Day);
                break;
            case 5:
                charge_account();
                break;
            case 6:
                printf("\nplz enter your friend's username:\n");
                scanf("%s", friend_username);
                send_charge(friend_username);
                break;
            case 7:
                Time_Set();
                break;
            case 8:
                report_financial();
                break;
            case 9:
                printf("\nplz enter the date and the meal you want to cancel:\n");
                scanf("%d-%d-%d %s", &Year, &Month, &Day, meal);
                cancel_rezervation(Year, Month, Day, meal);
                break;
            case 10:
                check_news();
                break;
            case 11:
                vote();
                break;
            case 12:
                show_File_of_food_selves();
                printf("\nplz enter id_self & id_food:\n");
                scanf("%s %s", id_self2, id_food);
                daily_reserve(id_self2, id_food);
                break;    
            }
        }
    }
}