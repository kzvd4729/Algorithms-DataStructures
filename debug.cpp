#define SP(x) cerr<<#x<<" = "<<x<<endl
#define DP(x) cerr<<#x<<" = "<<x.first<<" "<<x.second<<endl
#define F cerr<<"flag"<<endl
template<typename T>//container
void _p(T v)
{
  cerr<<"( ";
  for(auto x:v)cerr<<x<<" ";
  cerr<<")"<<endl;
}
