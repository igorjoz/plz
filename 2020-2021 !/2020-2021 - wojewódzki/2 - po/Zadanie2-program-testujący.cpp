#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct pairs {
	char c;
	string code;
}; // można użyć mapy - #include <map>, map<char, int> x;
// założenie: w pliku kody są posortowane według długości rosnąco (na początku najkrótsze znaki, na końcu najdłuższe)

int main()
{
	fstream input, output;
	input.open("data.txt", ios::in);
	output.open("output.txt", ios::out);

	if (input.good() and output.good()) {
		string encoded, decoded = "";
		int n;
		input >> n;

		pairs* x = new pairs[n];

		for (int i = 0; i < n; i++) {
			input >> x[i].c >> x[i].code;
		}

		input >> encoded;

		cout << n << endl;
		for (int i = 0; i < n; i++) {
			cout << x[i].c << " " << x[i].code << endl;
		}
		cout << encoded << endl << endl;

		int length = encoded.length();

		for (int i = 0; i < length; i++) {
			int k = 2;
			int startIndex = i;
			for (int j = 0; j < n; j++) {
				//cout << encoded.substr(i, k) << "\t" << x[j].code << "\t" << i << " " << j << " " << k  << endl;
				if (encoded.substr(i, k) == x[j].code) {
					cout << x[j].c << endl;
					decoded += x[j].c;
					i = startIndex + k - 1;
					break;
				}
				else if (x[j + 1].code.length() != k) {
					k++;
				}
			}
		}

		cout << endl << decoded;
		output << decoded << endl;

		delete[] x;
	}
	else {
		cout << "file problem";
	}
}