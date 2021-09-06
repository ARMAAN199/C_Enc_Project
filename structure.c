/*  employee database program       */

//whenever code starts make sure you change is loggedin for all users to 0
//and delete all otps

//verify is logged in on every req
//update user route. MUST..
//admin mode use directory functions to remove all users, delete all files etc.. and count number of files too
//to display number of current users.

//try to create login sessions using last login time, system time, isloggedin etc.

//auto increment in userid


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct files
{
    int user_id;
    char original_location[1000];
    char final_location[1000];
}files;

typedef struct user
{
    int user_id;
    char username[100];
    char password[100];
    int code;
    int code2;
    int isloggedin;
    files storage[10000];
}user;

typedef struct otp
{
    int user_id[100];
    int value;
    int hh;
    int mm;
    int ss;
}otp;

void print_home_screen();
void print_password_screen(char* , char*);

int calculate_user_id()
    {
        FILE *fp2;
        fp2 = fopen("Admin/usercount", "r+");
        int count;
        fscanf (fp2, "%d", &count);
        fp2=freopen(NULL,"w",fp2);
        fprintf(fp2, "%d", count+1);
        fclose(fp2);
        return count+1;
    }

user* create_user(char usrnm[], char pswd[]) {
    user* obj = malloc(sizeof(user));
    obj->user_id = calculate_user_id();
    strcpy(obj->username,usrnm);
    strcpy(obj->password, pswd); 
    obj-> code = 12; //Try to generate these randomly using some sort of password encr.
    obj-> code2 = 45;//Try to generate these randomly using some sort of password encr.
    obj-> isloggedin = 0;
    return obj;   
}

int exists(char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void create_user_file(user* obj)
{
    FILE *fp1,*fp2;
    char location[100] = "Users/";
    strcat(location, obj->username);
    strcat(location, ".txt");
    if(exists(location))
    {
        printf(ANSI_COLOR_RED "USER ALREADY EXISTS" ANSI_COLOR_BLUE "\nPress any key to go back to home screen\n");
    }
    else{
        fp1 = fopen(location , "w+");
        fprintf(fp1, "%d", obj->user_id);
        fputc('\n', fp1);
        fputs(obj->username, fp1);
        fputc('\n', fp1);
        fputs(obj->password, fp1);
        fputc('\n', fp1);
        
        
        fclose (fp1);
        printf("USER CREATED SUCCESSFULY\nPress any key to go back to home screen" ANSI_COLOR_RESET "\n");
        // fwrite (obj, sizeof(user), 1, fp1);
    }
        int newinput;
        scanf("%d",&newinput);
        switch (newinput)
        {
        default:
            print_home_screen();
        }

    // enter_string_to_file(fp1, obj->username);
}

void read_user_file(char *username)
{
    char* arr[] = {"User_id", "Username", "Password"};
    FILE *fp1,*fp2;
    char location[100] = "Users/";
    strcat(location, username);
    strcat(location, ".txt");
    if(!exists(location))
    {
        printf("USER DOES NOT EXIST");
        printf("\nPress any key to go back to home screen" ANSI_COLOR_RESET "\n");
        int newinput;
        scanf("%d",&newinput);
        switch (newinput)
        {
        default:
            print_home_screen();
        }
    }
    else{
        fp1 = fopen (location, "r"); 
        char nextline[10000];
        int f=0;
        while (fgets(nextline, sizeof(nextline), fp1)  && f<2) {
        printf(ANSI_COLOR_MAGENTA "%s : %s " ANSI_COLOR_RESET "\n", arr[f], nextline);
        f++;
        }
        char password[100];
        strcpy(password , nextline);
        fclose (fp1);
        printf(ANSI_COLOR_YELLOW "Enter Password: " ANSI_COLOR_RESET);
        char entered_password[100];
        scanf("%s", entered_password);
        print_password_screen(password, entered_password);
        // printf ("File exists");
    }
}

void print_password_screen(char* password, char* entered_password)
{
        if(strcmp("exit", entered_password))
        {
            scanf("%s", entered_password);
            if(strcmp(password, entered_password))
            {
                //Logged in interface
            }
            else
            {
                printf(ANSI_COLOR_YELLOW "Incorrect Password Try Again or type 'exit' to go back to main menu: " ANSI_COLOR_RESET);
                scanf("%s", entered_password)
            }
        }
}

void print_new_user_interface()
{
    system("clear");
    char uname[100], pswd[100];
    printf(ANSI_COLOR_GREEN "-----------------------------------------------\n");
                     printf("| Enter Username : ");
                     scanf("%s",uname);
                     printf("| Enter Password : ");
                     scanf("%s",pswd);
                     printf("|\n" ANSI_COLOR_BLUE);
    user* obj = create_user(uname,pswd);  
    create_user_file(obj);

}

void print_home_screen()
{
    system("clear");
    printf(ANSI_COLOR_GREEN "-----------------------------------------------\n");
                     printf("| Press 1 to create a new user                |\n");
                     printf("| Press 2 to login                            |\n");
                     printf("| Press 0 to exit                             |\n\n\n");
                     int input = 1;
                     printf("Choose an Option  ");
                    while(input !=0)
                    {
                    scanf("%d", &input);
                    switch (input)
                    {
                        case 0:
                            return;
                            break;
                        case 1:
                            print_new_user_interface();
                            return;
                            break;            
                        case 2:
                            printf(ANSI_COLOR_YELLOW "Enter the name of the user\n" ANSI_COLOR_RESET);
                            char uname[100];
                            scanf("%s",uname);
                            read_user_file(uname);
                            return;
                            break;         
                        default:
                            printf(ANSI_COLOR_CYAN "Enter Valid Input : " ANSI_COLOR_RESET);
                            break;
                    }
                    }
}

// void enter_string_to_file(FILE* fp1, char str[]) {
//     int i=0;
//     while(str[i]!='\0')
//     {
//         fputc(str[i],fp1);
//         i++;
//     }
// }


int main(void)
{
    print_home_screen();

    return 0;    

    // int i , choice;
    // FILE *fp1,*otpflptr;
    // char oname[100];
    // user det;
    // int recsize;
    // char c;
    
    // if(fp1 == NULL)
    // {
    //     fp1 = fopen("record.dat" , "w+");
    //     if(fp1 == NULL)
    //     {
    //         printf("error in opening file : \n");
    //         return -1;
    //     }
    // }
    // recsize = sizeof(det);

    // fseek(fp1 , 0 ,SEEK_END);
    // printf("Enter employee Name : ");
    // scanf("%[^\n]" , det.name);
    // printf("Enter roll number   : ");
    // scanf("%d" , &det.roll);
    // printf("Enter the salary    : ");
    // scanf("%d" , &det.salary);
    // scanf("%c" , &c);
    // printf("Enter address   : ");
    // scanf("%[^\n]" , det.address);
    // printf("Enter joining year  : ");
    // scanf("%d" , &det.join_year);
    // fwrite(&det,recsize,1,fp1);
}