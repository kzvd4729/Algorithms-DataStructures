/*
not enough tested.
*/
#define setp(a) cout<<setprecision(a)<<fixed
const double eps=1e-9;
int sgn(double x)
{
  if(fabs(x)<=eps)return 0;
  return x>0?1:-1;
}
struct point
{
  double x,y;
  point(){}
  point(double _x,double _y):x(_x),y(_y){}
  point operator-(const point &p){return {x-p.x,y-p.y};}
  point operator+(const point &p){return {x+p.x,y+p.y};}
  point operator*(double d){return {x*d,y*d};}
  double operator^(const point &p){return x*p.y-y*p.x;}
};
struct line
{
  point p,v;double ang;
  line(){}
  line(point p1,point p2){p=p1,v=p2-p1;ang=atan2(v.y,v.x);}
  bool operator<(const line &l)const{return ang<l.ang;}
  point intersection(line l)
  {
    //care for parallel lines???
    double t=(l.v^(p-l.p))/(v^l.v);
    return p+v*t;
  }
};
/*
lines are extended to infinity. there is a halfplane in counter-clock 
side of every line. finds the common polygoan of those halfplane.
if lines are not bounded, infinity rectangle can be added. 
to include the point that doesn't generate area(intersection is a 
straight line) replace eps with -eps.
*/
vector<point>halfPlaneIntersection(vector<line>&l)
{
  //lines are anti-clockwise
  int n=l.size();sort(l.begin(),l.end());
  int first=0,last=0;vector<point>poly;
  vector<point>p(n);vector<line>q(n);
  q[first]=l[0];
  for(int i=1;i<n;i++)
  {
    while(first<last&&(l[i].v^(p[last-1]-l[i].p))<=eps)last--;//<-eps
    while(first<last&&(l[i].v^(p[first]-l[i].p))<=eps)first++;//<-eps
    q[++last]=l[i];
    if(sgn(q[last].v^q[last-1].v)==0)
    {
      last--;
      if((q[last].v^(l[i].p-q[last].p))>eps)q[last]=l[i];//>=-eps
    }
    if(first<last)p[last-1]=q[last-1].intersection(q[last]);
  }
  while(first<last&&(q[first].v^(p[last-1]-q[first].p))<=eps)//<-eps
    last--;
  if(last-first<=1)return poly;
  p[last]=q[last].intersection(q[first]);
  for(int i=first;i<=last;i++)poly.push_back(p[i]);
  return poly;//ccw path
}
