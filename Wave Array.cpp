/*
Given an array of integers, sort the array into a wave-like array and return it. 
In other words, arrange the elements into a sequence such that a1 >= a2 <= a3 >= a4 <= a5.....
Example
Given [1, 2, 3, 4]
One possible answer : [2, 1, 4, 3]
Another possible answer : [4, 1, 3, 2]
NOTE: If there are multiple answers possible, return the one that's lexicographically smallest.

 Input:
The first line contains an integer T, depicting total number of test cases. 
Then following T lines contains an integer N depicting the size of square matrix and next line followed by the value of array.

Output:
Print the array into wave-like array.

Constraints:
1 ≤ T ≤ 130
1 ≤ N ≤ 1000
0 ≤ A[i] ≤1000

Example:
Input
1
5
5 7 3 2 8
Output
3 2 7 5 8
*/

#include <iostream>
using namespace std;

void wave_ar(int * ar, int n);
int divide(int * ar, int n, int b, int e);
void merge(int * ar, int n, int b, int m, int e);
void print(int * pt, int b, int n);
void swap(int * ar, int n, int i1, int i2);
void wave(int *ar, int n);

void wave_ar(int * ar, int n) {
	divide(ar, n, 0, n - 1);
	//print(ar, 0, n - 1);
	wave(ar, n);
}

void wave(int *ar, int n) {
	int i = 0;
	while (i < (n-1)) {
		swap(ar, n, i, i + 1);
		i = i + 2;
	}
}

int divide(int * ar, int n, int b, int e) {
	if ((e - b)>1) {
		int m = b + (e - b) / 2;
		divide(ar, n, b, m);
		divide(ar, n, m + 1, e);
		merge(ar, n, b, m, e);
		//print(ar, b, e);
	}
	else if ((e - b) == 1) {
		if (*(ar + b) > *(ar + e))
			swap(ar, n, b, e);
		return e;
	}
}

void merge(int * ar, int n, int b, int m, int e) {
	int n1 = e - b + 1;
	int * ar1 = new int[n1];
	int k = 0;

	int i = b, j = m + 1;
	while (i <= m && j <= e && j < n && k < n1) {
		if (*(ar + i) < (*(ar + j)))
			*(ar1 + k++) = *(ar + i++);
		else
			*(ar1 + k++) = *(ar + j++);
	}

	//add elements left in the first & second sub array
	while (i <= m && k < n1) {
		*(ar1 + k++) = *(ar + i++);
	}

	while (j <= e && k < n1) {
		*(ar1 + k++) = *(ar + j++);
	}

	//copy back to the original array
	k = 0;
	for (int t = b; (t <= e && t < n); t++) {
		*(ar + t) = *(ar1 + k);
		k++;
	}

}

void print(int * pt, int b, int n) {
	for (int i = 0; i <= n; i++) {
		cout << *(pt + i) << " ";
	}
	cout << "\n";
}

void swap(int * ar, int n, int i1, int i2) {
	if (i1 < n && i2 < n) {
		int temp = *(ar + i1);
		*(ar + i1) = *(ar + i2);
		*(ar + i2) = temp;
	}
}

int main() {
	int T = 0;
	cin >> T;
	while (T--) {
		int n = 0;
			cin >> n;
		int * pt = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> *(pt + i);
		}
		wave_ar(pt, n);
		print(pt, 0, n-1);
	}

}