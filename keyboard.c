#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("Error: Usage ->     keyboard [option]\n");
		exit(1);
	}
	if ((strcmp(argv[1], "on") == 0) || (strcmp(argv[1], "ON") == 0)){
		strcpy(argv[1], "1");
	}
	if ((strcmp(argv[1], "off") == 0) || (strcmp(argv[1], "OFF") == 0)){
		strcpy(argv[1], "0");
	}
	char data[2000];
	char keyboard_id[4];
	FILE *fp;
	int i;
	fp = popen("xinput -list", "r");
	while (fgets(data, 2000, fp) != NULL) {
		if (strstr(data, "AT Translated Set 2 keyboard")) {
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
	pclose(fp);
	strcpy(data, "xinput set-int-prop ");
	strcat(data, keyboard_id);
	strcat(data, " \"Device Enabled\" ");
	strcat(data, "8 ");
	strcat(data, argv[1]);
	system(data);
	return 0;	
}