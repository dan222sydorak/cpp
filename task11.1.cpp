#include <stdio.h>
#include <Stdlib.h>

int write_array_to_file(float* arr, int n, const char* fname) {
	FILE* fp = fopen(fname, "wb");
	if (fp == NULL) {
		fprintf(stderr,"Error in open file %s for writing", fname);
		return -1;
	}
	int res = fwrite(arr, sizeof(*arr), n, fp);
	fclose(fp);
	return res;
}
int read_array_from_file(const char* fname) {
	FILE* fp = fopen(fname, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error in open file %s for reading", fname);
		return -1;
	}
	printf("Reading file:");
	float x;
	int count = 0;
	while (!feof(fp)) {
		fread(&x, sizeof(float), 1, fp);
		count++;
		printf("%f", x);
	}
	fclose(fp);
	return count;	
}

int main() {
	float* mas;
	printf("n=");
	int n;
	scanf_s("%d", &n);
	mas = (float*)malloc(n * sizeof(float)); // mas = new float[n]
	for (int i = 0; i < n; i++) {
		printf("a[%d]=", i);
		scanf_s("%f", &mas[i]);
	}
	char fname[20];
	printf("file:");
	scanf_s("%s", fname);
	write_array_to_file(mas, n, fname);
	read_array_from_file(fname);
}
