/*  employee database program       */

//whenever code starts make sure you change is loggedin for all users to 0
//and delete all otps

//verify is logged in on every req
//update user route. MUST.


#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

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

user* create_user(char usrnm[], char pswd[]) {
    user* obj = malloc(sizeof(user));
    obj->user_id = 1;
    strcpy(usrnm ,obj->username);
    strcpy(pswd, obj->password);
    obj-> code = 12; //Try to generate these randomly using some sort of password encr.
    obj-> code2 = 45;//Try to generate these randomly using some sort of password encr.
    return obj;   
}


int main(void)
{
    int i , choice;
    FILE *usrflptr,*otpflptr;
    char oname[100];
    user det;
    int recsize;
    char c;

    fp1 = fopen("record.dat" , "r+");
    if(fp1 == NULL)
    {
        fp1 = fopen("record.dat" , "w+");
        if(fp1 == NULL)
        {
            printf("error in opening file : \n");
            return -1;
        }
    }
    recsize = sizeof(det);

    fseek(fp1 , 0 ,SEEK_END);
    printf("Enter employee Name : ");
    scanf("%[^\n]" , det.name);
    printf("Enter roll number   : ");
    scanf("%d" , &det.roll);
    printf("Enter the salary    : ");
    scanf("%d" , &det.salary);
    scanf("%c" , &c);
    printf("Enter address   : ");
    scanf("%[^\n]" , det.address);
    printf("Enter joining year  : ");
    scanf("%d" , &det.join_year);
    fwrite(&det,recsize,1,fp1);
}