#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;

const int maxn=1e5+5;

typedef pair<int,int> PI;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)

int N, M, K, Sn;
long long ans;
map<int,int> A[maxn<<1], B[maxn<<1];
pair<PI,int> SS[maxn*10];

#define NE 1
#define SE 2
#define SW 4
#define NW 8
#define L(x,k) ((x)>>(k)?(x)>>(k):(x)<<(4-(k)))
#define R(x,k) ((x)>>(4-(k))?(x)>>(4-(k)):(x)<<(k))
#define oA(x,y) ((x)+(y))
#define oB(x,y) ((x)-(y)+M)
#define INS(x,y,v) (SS[Sn++]=mkp(PI(x,y),v))

int GO(int X, int Y, int D)
{
	int Sx(X), Sy(Y), Sd(D);
	A[oA(X,Y)].insert(PI(oB(X,Y),0));
	B[oB(X,Y)].insert(PI(oA(X,Y),0));
	map<int,int>::iterator NEW;
	NEW=(D==NE || D==SW? A[oA(X,Y)].find(oB(X,Y)): B[oB(X,Y)].find(oA(X,Y)));
	do
	{
		int d=NEW->se, dis;
		if (d==(D|L(D,1))) D=R(D,1); else
		if (d==(D|R(D,1))) D=L(D,1); else
		if ((__builtin_popcount(d)&1) && (d&D)==D) return true;
		NEW=(D==NE || D==SW? A[oA(X,Y)].find(oB(X,Y)): B[oB(X,Y)].find(oA(X,Y)));
		if (D==NE || D==NW) NEW--; else NEW++;
		dis=abs((D==NE || D==SW? oB(X,Y): oA(X,Y))-NEW->fi)/2;
		ans+=dis;
		if (D==SE || D==SW) X+=dis; else X-=dis;
		if (D==NE || D==SE) Y+=dis; else Y-=dis;
	} while (X!=Sx || Y!=Sy || D!=Sd);
	return false;
}

int main()
{
	freopen("mirror.in","r",stdin);
	freopen("mirror.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for (int i=1;i<=K;i++)
	{
		int x, y;
		scanf("%d%d",&x,&y);
		INS(x-1,y-1,SE), INS(x-1,y,SW), INS(x,y,NW), INS(x,y-1,NE);
	}
	for (int i=1;i<M;i++) INS(0,i,NE|NW), INS(N,i,SE|SW);
	for (int i=1;i<N;i++) INS(i,0,NW|SW), INS(i,M,NE|SE);
	INS(0,0,SW|NW|NE), INS(0,M,NW|NE|SE);
	INS(N,0,NW|SW|SE), INS(N,M,SW|SE|NE);
	sort(SS,SS+Sn);
	PI cur(-1,-1);
	int tot(0);
	for (int i=0;i<Sn;i++)
		if (SS[i].fi!=cur)
		{
			if (i)
			{
				A[oA(cur.fi,cur.se)].insert(PI(oB(cur.fi,cur.se),tot));
				B[oB(cur.fi,cur.se)].insert(PI(oA(cur.fi,cur.se),tot));
			}
			tot=SS[i].se, cur=SS[i].fi;
		} else
			tot|=SS[i].se;
	if (cur.fi!=-1)
	{
		A[oA(cur.fi,cur.se)].insert(PI(oB(cur.fi,cur.se),tot));
		B[oB(cur.fi,cur.se)].insert(PI(oA(cur.fi,cur.se),tot));
	}
	int X, Y, D;
	char s[3];
	scanf("%d%d%s",&X,&Y,s);
	D=(s[0]=='N' && s[1]=='E'? NE: s[0]=='S' && s[1]=='E'? SE: s[0]=='S' && s[1]=='W'? SW: NW);
	if (D==NW? GO(X-1,Y-1,D): D==NE? GO(X-1,Y,D): D==SE? GO(X,Y,D): GO(X,Y-1,D))
	{
		ans++, D=L(D,2);
		D==NW? GO(X-1,Y-1,D): D==NE? GO(X-1,Y,D): D==SE? GO(X,Y,D): GO(X,Y-1,D);
	}
	printf("%lld\n",ans);
	return 0;
}

