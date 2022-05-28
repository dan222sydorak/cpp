// task 10.5
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define LEN_NAME 255
#define MAX_MAS 100

typedef struct {
	char name[LEN_NAME];
	int height;
}Mount;

int inputMount(Mount* x) {
	printf("Mount name:");
	scanf_s("%s", x->name);
	printf("Mount height:");
	scanf_s("%d", &x->height);
	return true;
}

void outputMount(const Mount* x) {
	printf("Mount %s of height %d", x->name, x->height);
}

const char* maxHeightName(const Mount* arr, size_t n) {
	if (n == 0) return "No mountains";

	int maxh = arr[0].height;
	int indexMax = 0;

	for (int i = 1; i < n; i++) {
		if (arr[i].height > maxh) {
			maxh = arr[i].height;
			indexMax = i;
		}
	}
	return arr[indexMax].name;
}

void heightByName(const Mount* arr, size_t n,const char* mount_name) {
	printf("%s", mount_name);
	bool isFound = false;
	for (int i = 1; i < n; i++) {
		if(strncmp(arr[i].name,mount_name,strlen(mount_name)-1)==0) {
			printf("Mount %s has height %d", mount_name, arr[i].height);
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		printf("There is no mointain %s!\n", mount_name);
	}
}

int main2() {
	/*Mount m;
	inputMount(&m);
	outputMount(&m);*/
	Mount test[MAX_MAS] = { {"K2",8676},{"Eversest",8878},{"Hill",1234} };
	printf("%s", maxHeightName(test, 3));
	heightByName(test, 3, "Goverla");
	heightByName(test, 3, "K2");
	heightByName(test, 3, "Hill");

	Mount mnt[MAX_MAS];
	size_t n;
	printf("Input n=");
	scanf_s("%zu", &n);
	for (size_t i = 0; i < n; i++) {
		inputMount(&mnt[i]);
	}
	printf("%s\n", maxHeightName(mnt, n));

	printf("name:");
	char mname[LEN_NAME];
	fgets(mname, LEN_NAME, stdin);
	heightByName(mnt, n, mname);
	return 0;
}