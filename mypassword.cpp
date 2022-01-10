#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <shadow.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


int main(int argc, char *argv[]){
  	uid_t uid;
  	struct passwd *u;
  	struct spwd *spwd;
  	char password[256];
  	char newpass[256];
  	char *p, *encrypted, *newEncrypted, *np;
  	bool check;
   	uid = getuid();
 	u = getpwuid(uid);
 	
  	spwd = getspnam(u->pw_name);
  	printf("Enter your password: ");
  	scanf("%s", password);
  	u->pw_passwd = spwd->sp_pwdp;
  	// Ma hoa mat khau moi vua nhap
  	encrypted = crypt(password, spwd->sp_pwdp);
  	
  	//Kiem tra mat khau vua nhap bang mat khau cu 
  	check = strcmp(encrypted, spwd->sp_pwdp) == 0;
  	if(!check)
   		printf("Password is wrong! \n");
   	else{
    		printf("Correct password! \n");
    	
		printf("Enter new password: ");
		scanf("%s", newpass);
		FILE *file;
		file = fopen(SHADOW, "r+");
		
		//Ma hoa mat khau moi
		newEncrypted = crypt(newpass,spwd->sp_pwdp);
	  
	 	//Gan mat khau moi da ma hoa vao struct spwd 
	 	spwd->sp_pwdp = newEncrypted;
	 	
	 	//Ghi struct spwd sau khi doi passwd vao file Shadow
	 	putspent(spwd, file);
		fclose(file);
		
	 	printf("Change password successfully! \n");
	 }
}
