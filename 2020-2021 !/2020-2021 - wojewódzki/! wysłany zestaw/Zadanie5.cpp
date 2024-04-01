#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
fstream input, output;
vector<int> nums;
vector <bool> hasNwd;
vector<vector<int>> matchingNum;

int nwd(int a, int b) {
	while (a != b)
		if (a > b)
			a -= b;
		else
			b -= a;
	return a;
}

int main()
{

	input.open("ciagi.txt", ios::in);
	output.open("NWD3.txt", ios::out);

	input >> n;

	for (int i = 0; i < n; i++) {
		int temp;
		input >> temp;
		nums.push_back(temp);
	}

	for (int i = 0; i < n; i++) {
		int halfNum = (int)(nums[i] / 2);
		for (int a = 2; a < halfNum; a++) {
			for (int b = 2; b < halfNum; b++) {
				for (int c = 2; c < halfNum; c++) {
					if (a + b + c == nums[i] and nwd(nwd(a, b), c) > 1) {
						int nwdValue = nwd(nwd(a, b), c);
						//hasNwd[nwdValue] = true;
						//matchingNum[nwdValue].push_back(nums[i]);

						output << nwdValue << ": " << nums[i];
					}
				}
			}
		}
	}
}
