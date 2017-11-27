#include<stdio.h>
#include<unistd.h>

int main(){
    
    char *arglist[4];
    size_t bufsize = 100;
    

    arglist[0] = "./f1ser";
    arglist[1] = "6553";
    arglist[3] = 0;
    

    printf("type the max people allowed in the room: ");
    getline(&arglist[2], &bufsize, stdin);
    execvp("./f1ser", arglist);
    printf("error occur\n"); 
    return 0;
}
