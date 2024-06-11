#include "menue.h"
#include <time.h>
int main()
{
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
}