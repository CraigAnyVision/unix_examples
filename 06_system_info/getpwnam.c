#include <pwd.h>
#include <shadow.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct passwd *getpwnam(const char *name)
{
	// ensure that the files are rewound
	setpwent();

	struct passwd *ptr;

	// return the next entry in the password file
	while ((ptr = getpwent()) != NULL)
		if (strcmp(name, ptr->pw_name) == 0)
			break;

	// neither getpwent nor getpwuid should leave any of the files open
	endpwent();

	return ptr;
}

struct spwd *getspwnam(const char *name)
{
	// ensure that the files are rewound
	setspent();

	struct spwd *ptr;

	// return the next entry in the shadow file
	while ((ptr = getspent()) != NULL)
		if (strcmp(name, ptr->sp_namp) == 0)
			break;

	// getspent should not leave any of the files open
	endspent();

	return ptr;
}

int main(void)
{
	char *username = "craig";

	// get the password file entry for username
	struct passwd *pw = getpwnam(username);

	if (pw == NULL)
	{
		printf("Can't find a passwd entry for user %s\n", username);
		return 1;
	}

	printf("pw_name:  %s\n", pw->pw_name);
	printf("pw_uid:   %u\n", pw->pw_uid);
	printf("pw_gid:   %u\n", pw->pw_gid);
	printf("pw_dir:   %s\n", pw->pw_dir);
	printf("pw_shell: %s\n\n", pw->pw_shell);

	// get the shadow file entry for username
	struct spwd *spw = getspwnam(username);

	if (spw == NULL)
	{
		puts("Must be root for shadow file access");
		return 1;
	}

	printf("sp_namp:  %s\n", spw->sp_namp);

	// The shadow file password entry is split into fields separated by the $ symbol:
	// Field 1 is the hashing algorithm:
	//   1  MD5
	//   2  Blowfish
	//   2a eksblowfish
	//   5  SHA-256
	//   6  SHA-512
	// Field 2 is the salt
	// Field 3 is the hash of the salt & password
	// e.g. $6$xU4oRODR$S5MPRgqlnTH7Wix7OIX/lm/tZOi0summMwEdIaU3f0Ud5ZU3fnQ0cT.hiuJ7fy18N2S6M9e3VRU1G.NE9sAVa/
	// (check with: mkpasswd --method=sha-512 --salt=xU4oRODR password)
	printf("sp_pwdp:  %s\n", spw->sp_pwdp);
}