/*  employee database program       */

//whenever code starts make sure you change is loggedin for all users to 0
//and delete all otps

//verify is logged in on every req
//update user route. MUST..
//admin mode use directory functions to remove all users, delete all files etc.. and count number of files too
//to display number of current users.

//try to create login sessions using last login time, system time, isloggedin etc.

//auto increment in userid


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
        printf("USER ALREADY EXISTS");
    }
    else{
        fp1 = fopen(location , "w+");
        fprintf(fp1, "%d", obj->user_id);
        fputc('\n', fp1);
        fputs(obj->username, fp1);
        fputc('\n', fp1);
        fputs(obj->password, fp1);
        fputc('\n', fp1);
    }
    // enter_string_to_file(fp1, obj->username);
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
    char uname[100], pswd[100];
    scanf("%s",uname);
    scanf("%s",pswd);
    // printf("Hello%s\n",uname);
    // printf("HEllo%s",pswd);
    user* obj = create_user(uname,pswd);
    create_user_file(obj);
    printf("Hello%s\n",obj->username);
    printf("HEllo%s",obj->password);

    

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