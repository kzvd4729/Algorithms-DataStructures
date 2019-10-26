const unsigned long mx=(1ULL<<64)-1;
const int sz=100;
unsigned long bt[N+2][sz];//64 multiplied
bool ck(int id,int i){return (bool)(bt[id][i/64]&(1ULL<<(i%64)));}
void set1(int id,int i){bt[id][i/64]|=(1ULL<<(i%64));}
void set0(int id,int i){bt[id][i/64]&=(mx^(1ULL<<(i%64)));}
void set1(int id,int lt,int rt)
{
  while(lt%64&&lt<=rt)set1(id,lt++);
  while(rt%64!=63&&lt<=rt)set1(id,rt--);
  for(int i=lt/64;i<rt/64;i++)bt[id][i]=mx;
}
void set0(int id,int lt,int rt)
{
  while(lt%64&&lt<=rt)set0(id,lt++);
  while(rt%64!=63&&lt<=rt)set0(id,rt--);
  for(int i=lt/64;i<rt/64;i++)bt[id][i]=0ULL;
}
int count1(int id,int lt,int rt)
{
  int ret=0;
  while(lt%64&&lt<=rt)ret+=ck(id,lt++);
  while(rt%64!=63&&lt<=rt)ret+=ck(id,rt--);
  for(int i=lt/64;i<rt/64;i++)ret+=__builtin_popcountll(bt[id][i]);
  return ret;
}
void dXor(int id1,int id2,int lt,int rt,int id3)
{
  while(lt%64&&lt<=rt)
  {
    if(ck(id1,lt)^ck(id2,lt))set1(id3,lt);
    else set0(id3,lt);lt++;
  }
  while(rt%64!=63&&lt<=rt)
  {
    if(ck(id1,rt)^ck(id2,rt))set1(id3,rt);
    else set0(id3,rt);rt--;
  }
  for(int i=lt/64;i<rt/64;i++)bt[id3][i]=bt[id1][i]^bt[id2][i];
}
void dOr(int id1,int id2,int lt,int rt,int id3)
{
  while(lt%64&&lt<=rt)
  {
    if(ck(id1,lt)|ck(id2,lt))set1(id3,lt);
    else set0(id3,lt);lt++;
  }
  while(rt%64!=63&&lt<=rt)
  {
    if(ck(id1,rt)|ck(id2,rt))set1(id3,rt);
    else set0(id3,rt);rt--;
  }
  for(int i=lt/64;i<rt/64;i++)bt[id3][i]=bt[id1][i]|bt[id2][i];
}
void dAnd(int id1,int id2,int lt,int rt,int id3)
{
  while(lt%64&&lt<=rt)
  {
    if(ck(id1,lt)&ck(id2,lt))set1(id3,lt);
    else set0(id3,lt);lt++;
  }
  while(rt%64!=63&&lt<=rt)
  {
    if(ck(id1,rt)&ck(id2,rt))set1(id3,rt);
    else set0(id3,rt);rt--;
  }
  for(int i=lt/64;i<rt/64;i++)bt[id3][i]=bt[id1][i]&bt[id2][i];
}
