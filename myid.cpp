#include <iostream>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <grp.h>

using namespace std;

struct group *groupStruct;
struct group *grp;
char *group_name;
char **p;

void getGroupMem(const char *group_name, const char *username) {
	grp = getgrnam(group_name);
	for (p = grp->gr_mem; *p != NULL; p++) {
           	if (strstr(*p, username)) {
           		printf("%s, ", group_name);
           	}
           }
}

int main() {
	char * lookingname;
	cout << "ENTER USERNAME:";
	cin  >> lookingname;
	errno = 0; 
	passwd* entry = getpwnam(lookingname);
	if (!entry) {
		std::cerr << "Not found user\n";
		return EXIT_FAILURE;
	}
	
	if (*(entry->pw_name) == * lookingname) {
		cout <<"Login name (username): " << string(entry->pw_name) << "\n";
		cout <<"Encrypted password: " << string(entry->pw_passwd) << "\n";
		cout <<"User ID: " << (entry->pw_uid) << "\n";
		cout <<"Group ID: " ;
		setgrent();
		while ( groupStruct=getgrent() ) {
			group_name = groupStruct->gr_name;
			getGroupMem(group_name, entry->pw_name);	
		}
		endgrent();
		
		cout <<"Initial working (home) directory: " << string(entry->pw_dir) << "\n";
		cout <<"Login shell: " << string(entry->pw_shell) << "\n";
	}

}