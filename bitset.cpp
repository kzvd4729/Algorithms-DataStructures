const unsigned long mx=(1ULL<<64)-1;
const int sz=100;//64 multiplied
unsigned long on[64][64],of[64][64];
void init()
{
  for(int i=0;i<64;i++)
  {
    for(int j=i;j<64;j++)
    {
      if(j==i)on[i][j]=(1ULL<<j);
      else on[i][j]=on[i][j-1]|(1ULL<<j);
      of[i][j]=mx^on[i][j];
    }
  }
}
struct bitSet
{
  unsigned long bt[sz];
  void clear(){for(int i=0;i<sz;i++)bt[i]=0;}
  bool ck(int i){return (bool)(bt[i/64]&(1ULL<<(i%64)));}
  void set1(int i){bt[i/64]|=(1ULL<<(i%64));}
  void set0(int i){bt[i/64]&=(mx^(1ULL<<(i%64)));}
  void set1(int lt,int rt)
  {
    if(lt/64==rt/64){bt[lt/64]|=on[lt%64][rt%64];return ;}
    bt[lt/64]|=on[lt%64][63];bt[rt/64]|=on[0][rt%64];
    for(int i=lt/64+1;i<rt/64;i++)bt[i]=mx;
  }
  void set0(int lt,int rt)
  {
    if(lt/64==rt/64){bt[lt/64]&=of[lt%64][rt%64];return ;}
    bt[lt/64]&=of[lt%64][63];bt[rt/64]&=of[0][rt%64];
    for(int i=lt/64+1;i<rt/64;i++)bt[i]=0ULL;
  }
  int count1(int lt,int rt)
  {
    int ret=0;
    if(lt/64==rt/64){return __builtin_popcountll(bt[lt/64]&on[lt%64][rt%64]);}
    ret+=__builtin_popcountll(bt[lt/64]&on[lt%64][63]);
    ret+=__builtin_popcountll(bt[rt/64]&on[0][rt%64]);
    for(int i=lt/64+1;i<rt/64;i++)ret+=__builtin_popcountll(bt[i]);
    return ret;
  }
  void dNot(int lt,int rt)//current bitSet will be changed
  {
    if(lt/64==rt/64){bt[lt/64]^=on[lt%64][rt%64];return ;}
    bt[lt/64]^=on[lt%64][63];bt[rt/64]^=on[0][rt%64];
    for(int i=lt/64+1;i<rt/64;i++)bt[i]^=mx;
  }
  void dOr(bitSet &st,int lt,int rt)//current bitSet will be changed
  {
    if(lt/64==rt/64){bt[lt/64]|=(st.bt[lt/64]&on[lt%64][rt%64]);return ;}
    bt[lt/64]|=(st.bt[lt/64]&on[lt%64][63]);
    bt[rt/64]|=(st.bt[rt/64]&on[0][rt%64]);
    for(int i=lt/64+1;i<rt/64;i++)bt[i]|=st.bt[i];
  }
  void dAnd(bitSet &st,int lt,int rt)//current bitSet will be changed
  {
    if(lt/64==rt/64){bt[lt/64]&=(st.bt[lt/64]|of[lt%64][rt%64]);return ;}
    bt[lt/64]&=(st.bt[lt/64]|of[lt%64][63]);
    bt[rt/64]&=(st.bt[rt/64]|of[0][rt%64]);
    for(int i=lt/64+1;i<rt/64;i++)bt[i]&=st.bt[i];
  }
  void dXor(bitSet &st,int lt,int rt)//current bitSet will be changed
  {
    if(lt/64==rt/64){bt[lt/64]^=(st.bt[lt/64]&on[lt%64][rt%64]);return ;}
    bt[lt/64]^=(st.bt[lt/64]&on[lt%64][63]);
    bt[rt/64]^=(st.bt[rt/64]&on[0][rt%64]);
    for(int i=lt/64+1;i<rt/64;i++)bt[i]^=st.bt[i];
  }
};
