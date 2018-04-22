#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void editkeyboard(char change[2000]) {
	char choice[2000];
	char data[2000];
	printf("New device will be: %s", change);
	printf("Are you sure??? (y/n): ");
	fgets(choice, 2000, stdin);
	if ((choice[0] != 'y') && (choice[0] != 'Y')) {
		printf("Cancelling...\n");
		exit(0);
	}
	char swap[2000] = "#define KEYBOARDNAME \""; 
	strcat(swap, change);
	swap[strlen(swap)-1] = '\"';
	FILE *fp;
	FILE *fp2;
	fp = fopen("keyboard.c", "r");
	fp2 = fopen("tempfile.c", "w+");
	while (fgets(data, 2000, fp) != NULL) {
		if (strstr(data, "#define")) {
			fprintf(fp2, "%s\n", swap);
		}
		else {
			fprintf(fp2, "%s", data);
		}
	}
	fclose(fp);
	fclose(fp2);
	sleep(1);
	system("mv tempfile.c keyboard.c");
	sleep(1);
	system("gcc keyboard.c -o keyboard");
	printf("Changed!\n");
}

int main(int argc, char* argv[]) {
	int i = 1;
	char choice[2000];
	char change[2000];
	system("xinput -list");
	printf("The current saved device is: ");
	while (argv[i]) {
		printf("%s ", argv[i]);
		i++;
	}
	printf("\nIs this correct? (y/n): ");
	fgets(choice, 2000, stdin);
	if ((choice[0] == 'y') || (choice[0] == 'Y')) {
		exit(0);
	}
	if ((choice[0] == 'n') || (choice[0] == 'N')) {
		printf("New Device Name: ");
		fgets(change, 2000, stdin);
	}
	else {
		printf("Bad input, exiting...\n");
		exit(1);
	}
	editkeyboard(change);
	return 0;
}