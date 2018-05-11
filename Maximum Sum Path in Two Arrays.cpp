/*
Given two sorted arrays such the arrays may have some common elements.
Find the sum of the maximum sum path to reach from beginning of any array to end of any of the two arrays. We can start from any array and switch from one array to another array only at common elements.

Input:
The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows.
The first line of each test case contains two integers M and N denoting the size of two arrays.
Then two lines follow, first containing M space-separated integers A1, A2, ..., AM denoting the elements of the array and
second containing N space-separated integers A1, A2, ..., AN denoting the elements of the array.

Output:
Print the maximum sum.

Constraints:
1 <= T <= 100
1 <= N <= 100
0 <=A[i]<=100

Example:

Input:
2
8 8
2 3 7 10 12 15 30 34
1 5 7 8 10 15 16 19
3 4
1 2 3
1 1 2 4

Output:
122
8
Explanation:
For sample test case 2, the path will be 1 1 2 4 as we can switch between arrays at common elements .In this case we'll start from first array and then move
to second array to get the maximum sum path.
*/
#include <iostream>
using namespace std;

int max(int x1, int x2) {
	int max = 0;
	(x1 > x2) ? max = x1 : max = x2;
	return max;
}

int find_max_sum_path(int * ar1, int n1, int * ar2, int n2) {
	int sum = 0;
	int i = 0, j = 0;
	int sum1 = 0, sum2 = 0;
	while (i < n1 && j < n2) {
		if (*(ar1 + i) < *(ar2 + j)) {
			sum1 += *(ar1 + i++);
		}

		else if (*(ar1 + i) > *(ar2 + j)) {
			sum2 += *(ar2 + j++);
		}

		else if (*(ar1 + i) == *(ar2 + j)) {
			sum += max(sum1, sum2);
			sum += *(ar1 + i);

			sum1 = sum2 = 0;
			i++;
			j++;
		}
	}
	while (i < n1)
		sum1 += *(ar1 + i++);

	while (j < n2)
		sum2 += *(ar2 + j++);

	sum += max(sum1, sum2);
	return sum;
}

int main() {
	int T = 0;
	cin >> T;
	while (T > 0) {
		int n1 = 0, n2 = 0;
		cin >> n1;
		cin >> n2;

		int * ar1 = new int[n1];
		int * ar2 = new int[n2];

		int i = 0;
		while (i < n1) {
			cin >> *(ar1 + i++);
		}
		i = 0;
		while (i < n2) {
			cin >> *(ar2 + i++);
		}

		i = 0;
		while (i < n1) {
			cout << *(ar1 + i++);
		}
		cout << endl;
		i = 0;
		while (i < n2) {
			cout << *(ar2 + i++);
		}
		cout << endl;

		cout << find_max_sum_path(ar1, n1, ar2, n2) << endl;
	}
	
	return 0;
}
