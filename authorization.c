#include "authorization.h"
int main() {
    char entered_password[128];
    bool success = store_password("my_password");
    if (success)
    printf("\npassword stored successfully");
    else
    printf("\nfailed to store password");
    
    printf("\nenter password : ");
    
    
    fgets(entered_password,128,stdin);

    entered_password[strcspn(entered_password, "\n")] = '\0';

    if(verify_password(entered_password))
    printf("\nUser authenticated");

    else
    printf("\npassword incorrect");

    return 0;
}