#include <bits/stdc++.h>
using namespace std;

vector< pair<int, int> > pts, res;

int check(pair<int,int > p, pair<int,int> q, pair<int,int> r)
{
	int val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

void find_hull() {
	int n = pts.size();
	int count = 0;
	int left_index;
	if (n < 3) return;
	int leftmost = pts[0].first;
	for (int i = 1; i < n ; i++) {
		if (leftmost > pts[i].first) {
			leftmost = pts[i].first;
			left_index = i;
		}
	}

	int a, b;
	a = left_index;

	do {
		res.push_back(pts[a]);
		b = (a + 1) % n;

		for (int i = 0; i < n; i++) {
			if (check(pts[a], pts[i], pts[b]) == 2) b = i;
		}

		a = b;
	} while (a != left_index);

	cout << " The required points are : " << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << "[" << res[i].first << ", " << res[i].second << "]\n";
	}
}

int main() {
	int n;
	cout << "Number of points: ";
	cin >> n;
	cout << "Enter the points\n";

	// Taking the input of points and pushing into the points vector	 
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pts.push_back(make_pair(x, y));
	}

	
	// Finding the convex hull
	clock_t t;
	t = clock();
	find_hull();
	t = clock() - t;
	printf ("It took %f seconds.\n", ((float)t)/CLOCKS_PER_SEC);
	return 0;
}