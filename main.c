#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>



#include "utils.h"
#include "memory.h"

struct {
	int fd;	
	int depth;
} *ed;

void setup() {
	note("\t\t###################################################");
	note("\t\t# 盲目人間はこの世界で色がありませんに思うか？    #");
	note("\t\t# この人は思うと道がありません。人間は思うるです。#");
	note("\t\t###################################################");
	note("\t\t				    Zedeleyici.1337");
	ed = mmap(NULL, 4096 * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ed == MAP_FAILED) die("inital map of setup");


	setup_memory_management();
}

void recursive(char *dirname) {
	struct dirent *de;
	struct stat statbuf;
	DIR *dr = opendir(dirname);
	char *res, path[300];
	
	if (!dr) { 
		return;
	}
	chdir(dirname);

	while ((de = readdir(dr)) != NULL) {
		lstat(de->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if (!memcmp(de->d_name, ".", 1) || !memcmp(de->d_name, "..", 2) ) continue;
			recursive(de->d_name);
		}
		else {
			int fd = open(de->d_name, O_RDONLY);
			if (fd > 2) {
				res = realpath(de->d_name, path);
				note("device : %s", path);
				close(fd);
			}
		}
	}
	chdir("..");
	closedir(dr);

}


int main() {
	in();
	setup();
	recursive("/dev/");
	out();
	return 0;
}
