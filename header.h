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

int calculate_user_id();
user* create_user(char [], char []);
int exists(char *);
void create_user_file(user*);
void read_user_file(char *);
void print_password_screen(char* , char* );
void print_new_user_interface();
void print_home_screen();
void enter_string_to_file(FILE* , char[]);