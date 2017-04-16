#include <bits/stdc++.h>
using namespace std;

struct Point{     double x, y;};

Point *convex_hull_set;
int h=0;

inline void print_point(Point p){    cout<<p.x<<" "<<p.y<<endl;}

inline int area(Point p, Point q, Point r){     return abs( p.x*(q.y-r.y) + q.x*(r.y-p.y) + r.x*(p.y-q.y) );}

int get_sign(Point A, Point B, Point X){
    int sign = (A.y-B.y)*X.x + (B.x-A.x)*X.y + (B.y*A.x-A.y*B.x);
    if(sign>0) return 1;
    if(sign<0) return -1;
    return 0;
}

void FindHull(Point *pt, int n, Point A, Point B){
    if(n<=0) return;
    int index=0, max_dis, temp_dis;
    for(int i=0;i<n;i++){
        temp_dis = area(A, B, pt[i]);
        if(i==0) max_dis=temp_dis;
        else if(temp_dis > max_dis){
            max_dis = temp_dis;
            index = i;
        }
    }
    convex_hull_set[h++]=pt[index];
    Point C = pt[index];
    Point G;
    G.x = (A.x + B.x + C.x)/3;
    G.y = (A.y + B.y + C.y)/3;
    int sign = get_sign(A, C, G);
    Point *pt_pos = new Point[n];
    Point *pt_neg = new Point[n];
    int p=0, q=0;
    for(int i=0;i<n;i++){
        if(sign*get_sign(A,C,pt[i]) < 0) pt_pos[p++]=pt[i];
    }
    sign = get_sign(B, C, G);
    for(int i=0;i<n;i++){
        if(sign*get_sign(B,C,pt[i]) < 0) pt_neg[q++]=pt[i];
    }
    FindHull(pt_pos, p, A, C);
    FindHull(pt_neg, q, C, B);   
}

int main(){
    int n;
    cout << "Number of points: ";
    cin >> n;
    Point *pt = new Point[n];
    convex_hull_set = new Point[n];
    cout << "Enter the points\n";
    int leftmost=0, rightmost=0;
    for(int i=0;i<n;i++){
        cin >> pt[i].x >> pt[i].y;
        if(pt[i].x < pt[leftmost].x) leftmost=i;
        if(pt[i].x > pt[rightmost].x) rightmost=i;
    }

    clock_t t;
    t=clock();
    
    Point *pt_pos = new Point[n];
    Point *pt_neg = new Point[n];
    
    int A,B,C;
    A = pt[leftmost].y - pt[rightmost].y;
    B = -pt[leftmost].x + pt[rightmost].x;
    C = pt[rightmost].y*pt[leftmost].x - pt[leftmost].y*pt[rightmost].x;
    
    int p=0, q=0, val;
    for(int i=0;i<n;i++){
        if(i!=leftmost && i!=rightmost){
            val = A*pt[i].x + B*pt[i].y + C;
            if(val>0){
                pt_pos[p++]=pt[i];
            }
            if(val<0){
                pt_neg[q++]=pt[i];
            }
        }
    }
    
    convex_hull_set[h++] = pt[leftmost];
    convex_hull_set[h++] = pt[rightmost];

    FindHull(pt_pos, p, pt[leftmost], pt[rightmost]);
    FindHull(pt_neg, q, pt[leftmost], pt[rightmost]);

    cout<<"Convex hull set points:\n";
    for(int i=0;i<h;i++){
        print_point(convex_hull_set[i]);
    }

    t=clock()-t;
    printf ("It took %f seconds.\n", ((float)t)/CLOCKS_PER_SEC);
    return 0;
}