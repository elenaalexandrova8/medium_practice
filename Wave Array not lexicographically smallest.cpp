/*
Given an array of integers, sort the array into a wave-like array and return it. 
In other words, arrange the elements into a sequence such that a1 >= a2 <= a3 >= a4 <= a5.....
Example
Given [1, 2, 3, 4]
One possible answer : [2, 1, 4, 3]
Another possible answer : [4, 1, 3, 2]
*/

#include <iostream>
using namespace std;

void wave_ar(int * ar, int n);
int divide(int * ar, int n, int b, int e);
void wave(int * ar, int n, int b, int m, int e);
void print(int * pt, int b, int n);
void swap(int * ar, int n, int i1, int i2);
int find_min(int x, int y1, int y2, int & i1, int & i2);
int find_max(int x, int y1, int y2, int & i1, int & i2);
int max_index(int *ar, int b, int e);
int min_index(int *ar, int b, int e);

void wave_ar(int * ar, int n) {
	divide(ar, n, 0, n - 1);
}

int divide(int * ar, int n, int b, int e) {
	if ((e - b)>1) {
		int m = b + (e - b) / 2;
		divide(ar, n, b, m);
		divide(ar, n, m + 1, e);
		wave(ar, n, b, m, e);
		print(ar, b, e);
	}
	else if ((e - b) == 1) {
		return e;
	}
}

void wave(int * ar, int n, int b, int m, int e) {
	int n1 = e - b + 1;
	int * ar1 = new int[n1];
	int k = 0;

	int i = b, j = m + 1;
	while (i <= m && j <= e && j < n && k < (e-b)) {
		if (k == 0) {
			if (*(ar + i) < *(ar + j))
				*(ar1 + k++) = *(ar + i++);
			else
				*(ar1 + k++) = *(ar + j++);
		}
		else if (!((b+k) % 2)) {						//even
			int next_element = find_min(*(ar1 + k - 1), *(ar + i), *(ar + j), i, j);
			if (next_element != -1) {
				*(ar1 + k++) = next_element;
			}
			else {
				if (i <= (m - 1))
					swap(ar, n, i, i + 1);
				else
					break;
				if (j <= (e - 1) && j < (n - 1))
					swap(ar, n, i, i + 1);
				else
					break;
			}
		}
		else if ((b + k) % 2) {					// odd
			int next_element = find_max(*(ar1 + k - 1), *(ar + i), *(ar + j), i, j);
			if (next_element != -1) {
				*(ar1 + k++) = next_element;
			}
			else {
				if (i <= (m - 1))
					swap(ar, n, i, i + 1);
				else
					break;
				if (j <= (e - 1) && j < (n - 1))
					swap(ar, n, i, i + 1);
				else
					break;
			}
		}
	}

	//add elements left in the first & second sub array
	while (i <= m && k < n1 && k > 0) {
		if (!((b + k) % 2)) {
			//find element smaller than array[k-1]
			int index = min_index(ar, i, m);
			swap(ar, n, i, index);
			if (*(ar1 + k - 1) > *(ar + i)) {
				*(ar1 + k++) = *(ar + i++);
			}
		}
		else if ((b + k) % 2) {
			//find element larger than array[k-1]
			int index = max_index(ar, i, m);
			swap(ar, n, i, index);
			if (*(ar1 + k - 1) < *(ar + i)) {
				*(ar1 + k++) = *(ar + i++);
			}
		}
	}

	while (j <= e && k < n1 && k > 0) {
		if (!((b + k) % 2)) {
			//find element smaller than array[k-1]
			int index = min_index(ar, j, e);
			swap(ar, n, j, index);
			if (*(ar1 + k - 1) > *(ar + j)) {
				*(ar1 + k++) = *(ar + j++);
			}
		}
		else if ((b + k) % 2) {
			//find element larger than array[k-1]
			int index = max_index(ar, j, e);
			swap(ar, n, i, index);
			if (*(ar1 + k - 1) < *(ar + j)) {
				*(ar1 + k++) = *(ar + j++);
			}
		}
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

int find_min(int x, int y1, int y2, int & i1, int & i2) {
	if (y1 < x || y2 < x) {
		if (y1 < y2) {
			i1++;
			return y1;
		}
		else {
			i2++;
			return y2;
		}
	}
	else
		return -1;
}

int find_max(int x, int y1, int y2, int & i1, int & i2) {
	if (y1 > x || y2 > x) {
		if (y1 > y2) {
			i1++;
			return y1;
		}
		else {
			i2++;
			return y2;
		}
	}
	else
		return -1;
}

int min_index(int *ar, int b, int e) {
	int min = b;
	for (int i = b; i <= e; i++) {
		if (*(ar + i) < *(ar + min))
			min = i;
	}
	return min;
}

int max_index(int *ar, int b, int e) {
	int max = b;
	for (int i = b; i <= e; i++) {
		if (*(ar + i) > *(ar + max))
			max = i;
	}
	return max;
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