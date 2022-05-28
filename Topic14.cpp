#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main1(int argc, char** argv) {
	const char* fname = "test14_1.txt";
	fstream f(fname, fstream::in);

	if (!f) {
		cerr << "cannot open file " << fname << "!";
		return -1;
	}

	string buf;
	f >> buf;
	clog << "Buf=" << buf << ";\n";

	int sum_expr = 0;
	int num = 0;
	int prevSign = 0;
	for (size_t i = 0; i < buf.length(); i++) {
		if (isdigit(buf[i])) {
			num = 10 * num;
			num += (buf[i]-'0');
		}
		else if(buf[i] == '+'){
			if (prevSign = 0) {
				sum_expr += num;
			}
			else {
				sum_expr -= num;
			}
			num = 0;
			prevSign = 0;
		}
		else if(buf[i] == '-'){
			if (prevSign = 0) {
				sum_expr += num;
			}
			else {
				sum_expr -= num;
			}
			num = 0;
			prevSign = 1;
		}
		else if (buf[i] == '=') {
			if (prevSign = 0) {
				sum_expr += num;
			}
			else {
				sum_expr -= num;
			}
			break;
		}
		else{
			cerr << "Cannot read char";
		}
	}
	cout << sum_expr;
}

int main(int argc, char** argv) {
	const char* fname = "test14_2.txt";

	fstream f;
	f.open(fname, fstream::in);

	if (!f) {
		cerr << "cannot open file" << fname << "!";
		return -1;
	}

	string articles[] = { "der","das","die" };
	int num_articles = 3;

	string buf;
	bool isArticle = false;

	fstream g;
	g.open("tmpfile.txt", fstream::out);
	if (!g) {
		cerr << "cannot open file" << "tmpfile.txt" << "!";
		return -1;
	}
	int i = 0;
	while (!f.eof()) {
		f >> buf;//read word by word


		if (isArticle) {
			buf[i] = toupper(buf[i]);
		}
		g << buf << " ";
		isArticle = false;
		for (i = 0; i < num_articles; i++) {
			if (buf == articles[i]) {
				isArticle = true;
				break;
			}
		}
	}
	f.close();
	g.close();


}