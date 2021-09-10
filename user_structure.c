/*
Color Codes for teminal ANSI
*/


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"


//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

#define reset "\e[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "header.h"



// void print_home_screen();
// void print_password_screen(char* , char*);


/*
This function is to auto increment userID for every new user created so that everyone has a unique ID.
Implementation?
Read the last user id from usercount file in admin directory and update it after
incrementing 1.
Return this new value to the create_user Function
*/

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
    time_t t;
    t = time(NULL);
    user* obj = malloc(sizeof(user));
    obj->user_id = calculate_user_id();
    strcpy(obj->username,usrnm);
    strcpy(obj->password, pswd); 
    obj-> code = t%100; //Try to generate these randomly using some sort of password encr.
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
        fprintf(fp1, "%d", obj->code);
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
        printf(ANSI_COLOR_MAGENTA "%s : %s" ANSI_COLOR_RESET, arr[f], nextline);
        f++;
        }
        char password[100];
        strcpy(password , nextline);
        fclose (fp1);
        printf(ANSI_COLOR_YELLOW "Enter Password: (or type 'exit' to go back to main menu)" ANSI_COLOR_RESET);
        char entered_password[100];
        scanf("%s", entered_password);
        print_password_screen(password, entered_password, location);
        // printf ("File exists");
    }
}

void print_password_screen(char* password, char* entered_password, char location[])
{
    // printf("%s%s", password, entered_password);
    // printf("%d", strcmp(password, entered_password));
        if(strcmp("exit", entered_password) != 0)
        {
            if((strcmp(password, strcat(entered_password,"\n")) == 0) || (strcmp(password, entered_password) == 0))
            {
                //Logged in interface
                printf("LOGGED IN SUCC");
                print_post_login_interface(location);
            }
            else
            {
                printf(ANSI_COLOR_YELLOW "Incorrect Password - Try Again or type 'exit' to go back to main menu: " ANSI_COLOR_RESET);
                scanf("%s", entered_password);
                print_password_screen(password, entered_password, location);
            }
        }
        else
        {
                print_home_screen();
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

void print_post_login_interface(char* location)
{
    char copy[100];
    strcpy(copy, location);
    system("clear");
     printf(ANSI_COLOR_CYAN "-----------------------------------------------\n");
                     printf("|   ----------Logged in with user-----------  |\n");
                     printf("|   ----------"ANSI_COLOR_RED " %s " ANSI_COLOR_CYAN"-----------  |\n", user_locationstr_to_user(copy+6));
                     printf("| Press 1 to change password                  |\n");
                     printf("| Press 2 to encrypt individual file          |\n");
                     printf("| Press 3 to encrypt multiple files           |\n");
                    //  printf("| Press 4 to encrypt all files in directory   |\n");
                     printf("| Press 5 to decrypt individual file          |\n");
                     printf("| Press 6 to decrypt multiple files           |\n");
                    //  printf("| Press 7 to decrypt all files in directory   |\n");
                     printf("| Press 8 to logout and return to main menu   |\n");
                     int input = 1;
                     printf(ANSI_COLOR_YELLOW "Choose an Option : " ANSI_COLOR_RESET);
                     scanf("%d", &input);
                     switch (input)
                     {
                        case 1:
                            print_edit_user_interface(location);
                            break;
                        case 2:
                            print_encryptfile_interface(location, 0);
                            break;    
                        case 5:
                            print_decryptfile_interface(location, 0);
                            break;                               
                        case 8:
                            print_home_screen();
                            break; 
                        // case 1:
                        //     print_new_user_interface();
                        //     return;
                        //     break;            
                        // case 2:
                        //     printf(ANSI_COLOR_YELLOW "Enter the name of the user\n" ANSI_COLOR_RESET);
                        //     char uname[100];
                        //     scanf("%s",uname);
                        //     read_user_file(uname);
                        //     return;
                        //     break;         
                        default:
                            printf(ANSI_COLOR_CYAN "Enter Valid Input : " ANSI_COLOR_RESET);
                            break;
                     }
}

void print_edit_user_interface(char* location)
{
        system("clear");
        printf(MAGB "Enter New Password\n" reset);
        char newpwd[100];
        scanf("%s", newpwd);
        strcat(newpwd, "\n");
        FILE* fp1 = fopen (location, "r+");
        FILE* fp2 = fopen ("Users/temp.txt", "w+");

        char nextline[10000];
        int f=0;
        while (fgets(nextline, sizeof(nextline), fp1)) {
        f++;
        if(f==3)
        {
            fputs(newpwd, fp2);
            continue;
        }
        fputs(nextline, fp2);
        }
        remove(location);
        rename("Users/temp.txt", location);

        fclose(fp1);
        fclose(fp2);

        printf(BGRN "Your Password Was Changed" reset);
        printf("\nPress any key to go back to user home \n");
        int newinput;
        scanf("%d",&newinput);
        switch (newinput)
        {
        default:
            print_post_login_interface(location);
        }
}

void print_encryptfile_interface(char* location, int errcode)
{
        system("clear");
        if(errcode == 1)
        {
        printf(REDB "No file found at provided location\n" reset); 
        }
        printf(BLUB "Enter path of file to be encrypted or 'exit' to go back to user home\n" reset);
        char filepath[1000];
        scanf("%s", filepath);
        if(strcmp("exit", filepath) == 0)
        {
            print_post_login_interface(location);
        }
        else if(!exists(filepath))
        {
            print_encryptfile_interface(location, 1);
        }
        else
        {
            FILE* fp1 = fopen (location, "r"); 
            char nextline[10000];
            int f=0;
            while (fgets(nextline, sizeof(nextline), fp1)  && f<3) {
            f++;
            }
            char codestr[100];
            strcpy(codestr , nextline);
            int code = atoi(codestr);
            fclose (fp1);
            encrypt1(location, filepath, code);
        }

        // printf("\nPress any key to go back to user home \n");
        // int newinput;
        // scanf("%d",&newinput);
        // switch (newinput)
        // {
        // default:
        //     print_post_login_interface(location);
        // }
}

void print_decryptfile_interface(char* location, int errcode)
{
        system("clear");
        if(errcode == 1)
        {
        printf(REDB "No file found at provided location\n" reset); 
        }
        printf(BLUB "Enter path of file to be decrypted or 'exit' to go back to user home\n" reset);
        char filepath[1000];
        scanf("%s", filepath);
        if(strcmp("exit", filepath) == 0)
        {
            print_post_login_interface(location);
        }
        else if(!exists(filepath))
        {
            print_decryptfile_interface(location, 1);
        }
        else
        {
            FILE* fp1 = fopen (location, "r"); 
            char nextline[10000];
            int f=0;
            while (fgets(nextline, sizeof(nextline), fp1)  && f<3) {
            f++;
            }
            char codestr[100];
            strcpy(codestr , nextline);
            int code = atoi(codestr);
            fclose (fp1);
            decrypt1(location, filepath, code);
        }

        // printf("\nPress any key to go back to user home \n");
        // int newinput;
        // scanf("%d",&newinput);
        // switch (newinput)
        // {
        // default:
        //     print_post_login_interface(location);
        // }
}

void encrypt1(char* location, char* filepath, int code)
{
    int belong_code = belongs_to(location, filepath);
    if(belong_code == 2)
    {
        //return
        printf(ANSI_COLOR_RED "This file belongs to some other user.\n" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_YELLOW "Press any key to go back to user home \n" ANSI_COLOR_RESET);
                int newinput;
                scanf("%d",&newinput);
                switch (newinput)
                {
                default:
                    print_post_login_interface(location);
                } 
    }
    else if(belong_code == 0 || belong_code == 1)
    {
        if(belong_code == 0)
        {
            //append
            write_to_user(location, filepath);
        }
                char ch;
                FILE *fps, *fpt;
                fps = fopen(filepath, "r");
                if(fps == NULL)
                printf("\nFile not found\n");
                fpt = fopen("tempfile.png", "w");
                if(fpt == NULL)
                    printf("\nCouldn't create temp file\n");
                else
                {
                    printf(BRED "Creating encrypted temp file..\n" reset);
                    ch = fgetc(fps);
                    while(ch != EOF)
                    {
                     ch = ch+code;
                     fputc(ch, fpt);
                     ch = fgetc(fps);
                     }
                fclose(fps);
                fclose(fpt);
                }

                remove(filepath);

                FILE* fps2,*fpt2;
                fps2 = fopen(filepath, "w");
                if(fps2 == NULL)
                printf("\nFile not found\n");
                fpt2 = fopen("tempfile.png", "r");
                if(fpt2 == NULL)
                printf("\nCouldn't read temp file\n");
                else
                {
                ch = fgetc(fpt2);
                while(ch != EOF)
                {
                    ch = fputc(ch, fps2);
                    ch = fgetc(fpt2);
                }
                fclose(fps2);
                fclose(fpt2);
                }
                remove("tempfile.png");
                printf(BRED "Removing temp file..\n" reset);
                printf(BRED "Finalising..\n" reset);

                printf(BRED "File Encrypted Successfully!\n" reset);
                printf(ANSI_COLOR_YELLOW "Press any key to go back to user home \n" ANSI_COLOR_RESET);
                int newinput;
                scanf("%d",&newinput);
                switch (newinput)
                {
                default:
                    print_post_login_interface(location);
                } 
        }
}

void decrypt1(char* location, char* filepath, int code)
{
    int belong_code = belongs_to(location, filepath);
    if(belong_code == 2 || belong_code == 0)
    {
        //return
        printf(ANSI_COLOR_RED "This file belongs to some other user.\n" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_YELLOW "Press any key to go back to user home \n" ANSI_COLOR_RESET);
                int newinput;
                scanf("%d",&newinput);
                switch (newinput)
                {
                default:
                    print_post_login_interface(location);
                } 
    }
    else
    {
    char ch;
    FILE *fps, *fpt;
    fps = fopen(filepath, "r");
    if(fps == NULL)
        printf("\nFile not found\n");
    fpt = fopen("tempfile.png", "w");
    if(fpt == NULL)
        printf("\nCouldn't create temp file\n");
    else
    {
        printf(BGRN "Creating decrypted temp file..\n" reset);
        ch = fgetc(fps);
        while(ch != EOF)
        {
            ch = ch-code;
            fputc(ch, fpt);
            ch = fgetc(fps);
        }
        fclose(fps);
        fclose(fpt);
    }
    remove(filepath);

    fps = fopen(filepath, "w");
    if(fps == NULL)
        printf("\nFile not found\n");
    fpt = fopen("tempfile.png", "r");
    if(fpt == NULL)
        printf("\nCouldn't read temp file\n");
    else
    {
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = fputc(ch, fps);
        ch = fgetc(fpt);
    }
    printf(BGRN "Removing temp file..\n" reset);
    fclose(fps);
    fclose(fpt);
    remove("tempfile.png");
    }
    printf(BGRN "Finalising..\n" reset);

    printf(BGRN "File Decrypted Successfully!\n" reset);
        printf(ANSI_COLOR_YELLOW "Press any key to go back to user home \n" ANSI_COLOR_RESET);
        int newinput;
        scanf("%d",&newinput);
        switch (newinput)
        {
        default:
            print_post_login_interface(location);
        }
    }
}

int belongs(char* location, char* filepath)
{
        char tempfilepath[100];
        strcpy(tempfilepath, filepath);
        strcat(tempfilepath, "\n");
        // printf("checking for user %s\n", location);
        FILE* fp1 = fopen (location, "r"); 
        char nextline[10000];
        int f=0;
        while (fgets(nextline, sizeof(nextline), fp1)  && f<4) {
        f++;
        }
        if(strcmp(nextline,"")!=0)
        {
            // printf("Nextline to be checked : %s\n with %s", nextline, tempfilepath);
            if(strcmp(tempfilepath, nextline) == 0)
            {   
                // printf("Returning 1");
                return 1;
            }
            else
            {
                while (fgets(nextline, sizeof(nextline), fp1))
                {
                    // printf("Nextline to be checked : %s\n with %s", nextline, tempfilepath);
                    if(strcmp(tempfilepath, nextline) == 0)
                    {
                        // printf("returning 1");
                        return 1;
                    }
                }
            }
            // printf("NOT FOUND\n");
            return 0;
        }
        return 0;
        fclose (fp1);
}

int belongs_to(char* location, char* filepath)
{
    DIR *d;
    struct dirent *dir;
    d = opendir("Users");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char temploc[100] = "Users/";
            strcat(temploc, dir->d_name);
            if(strcmp(location, temploc) == 0)
            {
                if(belongs(temploc, filepath))
                return 1;
            }
            else
            {
                if(belongs(temploc, filepath))
                return 2;
            }
        }
        closedir(d);
    }
    return 0;
}

void write_to_user(char* location, char* filepath)
{
    FILE *fa = fopen(location, "a");
	fputs(filepath, fa);
    fputc('\n', fa);
    fclose(fa);
}


void enter_string_to_file(FILE* fp1, char str[]) {
    int i=0;
    while(str[i]!='\0')
    {
        fputc(str[i],fp1);
        i++;
    }
}

char* user_locationstr_to_user(char* str)
{
    str[strlen(str)-4] = '\0';
    return str;
}



//WASTE UTILITY CODE

// int main(void)
// {
//     print_home_screen();
//     return 0;

// }    

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



// THINGS TO DO


//whenever code starts make sure you change is loggedin for all users to 0
//and delete all otps

//verify is logged in on every req
//update user route. MUST..
//admin mode use directory functions to remove all users, delete all files etc.. and count number of files too
//to display number of current users.

//try to create login sessions using last login time, system time, isloggedin etc.

//auto increment in userid