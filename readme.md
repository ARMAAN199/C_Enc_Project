# **Project Description**
___
This project is for **securing** certain **files** in a user's system with passcodes that the users creates. 

Files that are encrypted by one user can only be decrypted by that user themselves once they log in. Other users can't even encrypt the file once the primary user has decrypted it. 



# Goals
> Targets to achieve
___
* Implement Caeser-Cipher Encryption on files
* Achieve secure user Authentication
* Add other layers of security on files like:
  * Move locked files to another location. So that they are not visible at the original location and even if someone reaches the new location. They won't be able to access the content as the file would be encrypted.
  * Auto logout all users on program startup. (Only if sessions are added)


# Specifications
> What each file does
___
* Users folder contains the data of all users.
* header.c has definations of the functions and structs
* main.c calls the default home screen
* Makefile contains the gcc command to build the program. 
* connection.c contains experimental function to connect it with database (Not implemented yet)
* post_login_interface.c defines the terminal colors.
* user_strcture.c contains all the logic behind the program.
* **TO RUN :  make -B**



# Design
> Logic behind stuff
___
* Used Caeser-Cipher algorithm to encrypt files.
* Used file methods in C to store user data.
<!-- Blockquote -->


___
___
___
<!-- Images -->
<!-- ![Markdown Logo](https://markdown-here.com/img/icon256.png) -->

<!-- Github Markdown -->

### Tasks to implement
* [x] Create User
* [x] Implement Encryption
* [x] Update User
* [ ] Relocate Files
* [ ] Backup Functions for intermediate exit



|Other Intended Features|
| ---------------- |
___
Other Intended (not sure if I'll be able to implement though) features include:-
* *Email based OTP* verification for unlocking files.
* Multi-user Support. (Implemented now!)

___
___
[Armaan Jain](https://armaanjain.tech "Armaan Jain")