const int sz=1e7;//more size better, normaly 2*(number of insert) works fine
int key[sz+2],val[sz+2];//can be any data type
static inline int h(int x){return((x^179)*7LL)%sz;}
void init()
{
  memset(key,-1,sizeof key);//-1 is invalid
}
void add(int x,int y)//assign
{
  int k=h(x);
  while(key[k]!=-1&&key[k]!=x)k=(k+1)%sz;//first non-taken index
  key[k]=x,val[k]=y;
}
int get(int x)
{
  for(int k=h(x);key[k]!=-1;k=(k+1)%sz)
    if(key[k]==x)return val[k];
  return -1;
}



/*
for negative insert
with clear() function
*/
const int sz=1e7;//more size better, normaly 2*(number of insert) works fine
int key[sz+2],val[sz+2];//can be any data type
int buf[sz+2],id;
const int inv=inf+1;//something that will never be inserted
static inline int h(int x){return(((x^179)*7LL)%sz+sz)%sz;}//negtive value
void init()
{
  for(int i=0;i<sz+2;i++)key[i]=inv;
}
void add(int x,int y)//assign
{
  int k=h(x);
  while(key[k]!=inv&&key[k]!=x)k=(k+1)%sz;//first non-taken index
  key[k]=x,val[k]=y;
  buf[++id]=k;
}
int get(int x)
{
  for(int k=h(x);key[k]!=inv;k=(k+1)%sz)
    if(key[k]==x)return val[k];
  return -1;//something that will never be in val
}
void clear()
{
  for(int i=1;i<=id;i++)key[buf[i]]=inv,val[buf[i]]=0;
  id=0;
}
