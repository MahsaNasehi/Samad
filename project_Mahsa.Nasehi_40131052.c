#include "menue.h"
#include <time.h>
int main()
{
    // char inname[20];
    // scanf("%s", inname);
    // FILE *file1 = fopen(inname,"r");
    // if (file1 == NULL) {
    //     exit(1);
    // }
    head_approved = head_of_admins();
    print_to_file();
    FILE *news;
    news = fopen("news.txt", "w");
    fclose(news);
    FILE *poll;
    poll = fopen("poll.txt", "w");
    fclose(news);
    FILE *fp = fopen("reservations.txt", "w");
    FILE *fp1 = fopen("reservations_for_admin.txt", "w");
    FILE *fp2 = fopen("charge.txt", "w");
    FILE *fp3 = fopen("Send_charge.txt", "w");
    FILE *fp4 = fopen("token_food.txt", "w");
    fclose(fp4);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    int choice;
    printf("\n1)menu\n2)test case\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        menu();
    }
    else
    {
        printf("\nThere is no test case in my project unfortunately!\n");
    }

    // while ((fscanf ( file1, "%d#%s#", &command_code, command_name ) > 0))
    // {
    //     switch (command_name[])
    //     {
    //     case "register":
    //         fscanf( file1, "name:%s|family:%s|user-id:%d|password:%d|national-id-code:%d|birthdate:%d-%d-%d|gender:%s|type:%s", first_name, last_name, &us_id, &password, &na_id, &year, &month, &date, gender, type);
    //         regist(first_name, last_name, us_id, password, na_id, year, month, date, gender, type, user_identity);
    //         break;
    //     case "approve":
    //         char *approvement = (char *)malloc(15*sizeof(char));
    //         int approve_user[10], index = 0;
    //         char c;
    //         do
    //         {
    //             c = fgetc(file1);
    //             if (c = ':')
    //             {
    //                 fscanf(file1, "%d", &approve[index]);
    //                 index++;
    //             }
    //         } while (c != EOF);
    //         approve(&approve_user, index - 1, user_identity);
    //         break;
    //     case "login":
    //         fscanf( file1, "user:%s|password:%d", user, &password );
    //         login(user, password);
    //         break;

    //     default:
    //         break;
    //     }
    // }
    }

// void approve(int *user_identifi, int cnt_of_stu_to_be_proved, int us_iden){
//     int count = 0;
//     if (us_iden == 1  || us_iden == 2)
//     {
//         for (int i = 0; i < cnt_of_stu_to_be_proved; i++)
//         {
//             for (std_info *curr = head; curr != NULL; curr = curr -> next)
//             {
//                 if (*(user_identifi + i) == (curr -> user_id))
//                 {
//                     count++;
//                 }

//             }

//         }
//         if (count == cnt_of_stu_to_be_proved)
//         {
//             /*success*/
//         }
//         else if (count < cnt_of_stu_to_be_proved)
//         {
//             /* not-found */
//         }
//     }
//     else if (us_iden == 3)
//     {
//         printf("permission denied");
//         /*permission denied*/
//     }

// }