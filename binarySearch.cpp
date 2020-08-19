int binarySearch()
{
  string s="00000001111111";//find first 1;
  //could be s="111111111" s="00000000";
  int lo=0,hi=s.size(),md;//hi=n+1;
  while(lo<hi)
  {
    md=(lo+hi)/2;
    if(s[md]=='1')hi=md;else lo=md+1;
  }
  return lo;
}
