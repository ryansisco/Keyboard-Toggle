#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define KEYBOARDNAME "AT Translated Set 2 keyboard"

void inputcheck(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Error: Usage ->     keyboard [option]\n");
		exit(1);
	}
	if ((strcmp(argv[1], "on") == 0) || (strcmp(argv[1], "ON") == 0)){
		strcpy(argv[1], "1");
	}
	if ((strcmp(argv[1], "off") == 0) || (strcmp(argv[1], "OFF") == 0)){
		strcpy(argv[1], "0");
	}
	if ((strcmp(argv[1], "-help") == 0) || (strcmp(argv[1], "help") == 0)) {
		printf("Usage ->	keyboard [option]\n");
		printf("Options: 0, 1, on, off\n");
		system("xinput -list");
		printf("Searched for this keyboard name: %s\n",KEYBOARDNAME);
		printf("Change this by using -change\n");
		exit(0);
	}
	if (strcmp(argv[1], "-change") == 0) {
		char data[2000];
		strcpy(data, "./userdevchange ");
		strcat(data, KEYBOARDNAME);
		system(data);
		exit(0);
	}
}

void commandexecute(char data[2000], char keyboard_id[4], char* argv[]) {
	strcpy(data, "xinput set-int-prop ");
	strcat(data, keyboard_id);
	strcat(data, " \"Device Enabled\" ");
	strcat(data, "8 ");
	strcat(data, argv[1]);
	system(data);
	if (strcmp(argv[1], "0") == 0) {
		printf("Keyboard: \e[1;31m[OFF]\e[0m\n");
	}
	else {
		printf("Keyboard: \e[1;32m[ON]\e[0m\n");
	}
}

int main(int argc, char* argv[]) {
	inputcheck(argc, argv);
	char data[2000];
	char keyboard_id[4];
	FILE *fp;
	int i;
	int exists;
	fp = popen("xinput -list", "r");
	while (fgets(data, 2000, fp) != NULL) {
		if (strstr(data, KEYBOARDNAME)) {
			exists = 1;
			for (i = 0; i < strlen(data); i++) {
				if (data[i] == '=') {
					i++;
					int j = 0;
					while ((data[i] > 47) && (data[i] < 58)) {
						keyboard_id[j] = data[i];
						i++;
						j++;
					}
					keyboard_id[j] = '\0';
				}

			}
		}
	}
	if (exists != 1) {
		printf("Keyboard not found!\n");
			system("./keyboard -help");
			exit(1);
	}
	pclose(fp);
	commandexecute(data, keyboard_id, argv);
	return 0;	
}
