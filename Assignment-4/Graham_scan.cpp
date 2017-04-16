#include <bits/stdc++.h>
using namespace std;

const int maxN = 100005;

class Point {
public:
    int x, y;

    // comparison is done first on y coordinate and then on x coordinate
    bool operator < (Point b) {
        if (y != b.y)
            return y < b.y;
        return x < b.x;
    }
};

Point points[maxN];
Point pivot;

// returns -1 if a -> b -> c forms a counter-clockwise turn,
// +1 for a clockwise turn, 0 if they are collinear
int counterclockwise(Point a, Point b, Point c) {
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}

// returns square of Euclidean distance between two points
int distance_square(Point a, Point b)  {
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b)  {
    int order = counterclockwise(pivot, a, b);
    if (order == 0)
        return distance_square(pivot, a) < distance_square(pivot, b);
    return (order == -1);
}

stack<Point> find_convex_hull(Point *pts, int N)    {
    stack<Point> res;

    if (N < 3) return res;

    // find the point having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    int min_y = 0;
    for (int i = 1; i < N; i++)
        if (pts[i] < pts[min_y]) min_y = i;

    // swap the pivot with the first point
    Point temp = pts[0];
    pts[0] = pts[min_y];
    pts[min_y] = temp;

    // sort the remaining point according to polar order about the pivot
    pivot = pts[0];
    sort(pts + 1, pts + N, POLAR_ORDER);

    res.push(pts[0]);
    res.push(pts[1]);
    res.push(pts[2]);

    for (int i = 3; i < N; i++) {
        Point top = res.top();
        res.pop();
        while (counterclockwise(res.top(), top, pts[i]) != -1)   {
            top = res.top();
            res.pop();
        }
        res.push(top);
        res.push(pts[i]);
    }
    return res;
}

int main()  {
    int n;
    cout << "Number of points: ";
    cin >> n;

    int x, y;
   
    cout<<"Enter the points "<<endl;
    for(int i = 0 ; i < n; i++) {
        cin >> x >> y;
        points[i] = {x, y};
    }

    clock_t t;
    t = clock();
    stack<Point> hull = find_convex_hull(points, n);
    cout<<"The required points are "<<endl;
    while (!hull.empty())   {
        Point p = hull.top();
        hull.pop();
        printf("(%d, %d)\n", p.x, p.y);
    }
    t = clock() - t;
    printf ("It took %f seconds.\n", ((float)t)/CLOCKS_PER_SEC);

    return 0;
}