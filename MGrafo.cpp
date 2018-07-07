#include<iostream>
#include<cstdlib>
#define infinito N+1
using namespace std;

template<class H>
class Node
{
private:
	H info;
public:
	Node(H info): info(info) {}
	void setInfo(H info)
	{
		this->info=info;
	}
	H getInfo()
	{
		return info;
	}
	H*get_pinfo()
	{
		return &info;
	}
};

template<class H>
class Queue
{
private:
	int N;
	H*vett;
	int testa;
	int coda;
	int s;
public:
	Queue<H>(int N): N(N), vett(new H[N]), testa(0), coda(-1), s(0) {}
	int getSize()
	{
		return s;
	}
	Queue<H>*enqueue(H x)
	{
		if(s==N)
		{
			cout<<"Coda piena!"<<endl;
		}
		else
		{
			coda=(coda+1)%N;
			vett[coda]=x;
			s++;
		}
		return this;
	}
	H dequeue()
	{
		if(!s)
		{
			cout<<"la coda e vuota!"<<endl;
			return -1;
		}
		H x=vett[testa];
		testa=(testa+1)%N;
		s--;
		return x;
	}
	Queue<H>*del()
	{
		H x=dequeue();
		return this;
	}
	void stampa()
	{
		if(!s)
		{
			cout<<"coda vuota!"<<endl;
		}
		else
		{
			int i;
			for(i=coda; i%N!=testa; i--)
			{
				cout<<vett[i%N]<<" ";
			}
			cout<<vett[i%N]<<endl;
		}
	}
};

template<class H>
class Graph
{
private:
	int N;
	static const int bianco=0;
	static const int grigio=1;
	static const int nero=2;
	int n;
	int m;
	H**Grafo;
	int**mat;
	int t;
	int*d,*c,*p,*r,*f;
	int findIndex(H x)
	{
		for(int i=0; i<=n-1; i++)
		{
			if(x==*Grafo[i])
			{
				return i;
			}
		}
		return -1;
	}
	void bfsvisit(int x)
	{
		Queue<int>*q=new Queue<int>(N);
		for(int i=0; i<=n-1; i++)
		{
			c[i]=bianco;
			p[i]=-1;
			d[i]=infinito;
		}
		c[x]=grigio;
		d[x]=0;
		q->enqueue(x);
		while(q->getSize())
		{
			int i=q->dequeue();
			for(int j=0; j<=n-1; j++)
			{
				if(mat[i][j])
				{
					if(c[j]==bianco)
					{
						d[j]=d[i]+1;
						p[j]=i;
						q->enqueue(j);
						c[j]=grigio;
				}	}
			}
			c[i]=nero;
		}
		for(int i=0; i<=n-1; i++)
		{
			cout<<"["<<i<<"]->";
			if(d[i]==infinito)
			{
				cout<<"infinito"<<endl;
			}
			else
			{
				cout<<d[i]<<endl;
			}
		}
	}
public:
	Graph<H>(int N): N(N), n(0), m(0), Grafo(new H*[N]), t(0), mat(new int*[N]), d(new int[N]), p(new int[N]), c(new int[N]), r(new int[N]), f(new int[N])
	{
		for(int i=0; i<=N-1; i++)
		{
			mat[i]=new int[N];
			Grafo[i]=NULL;
		}
	}
	int getSizeNodo()
	{
		return n;
	}
	int getSizeArco()
	{
		return m;
	}
	Graph<H>*addNode(H*x)
	{
		if(n==N){return this;}
		int a=findIndex(*x);
		if(a==-1)
		{
			Grafo[n]=new H(*x);
			n++;
		}
		return this;
	}
	Graph<H>*addEdge(Node<H>*x, Node<H>*y)
	{
		int i=findIndex(x->getInfo());
		int j=findIndex(y->getInfo());
		if((i!=-1) && (j!=-1))
		{
			if(!mat[i][j])
			{
				mat[i][j]=1;
				m++;
			}
		}
		return this;
	}
	int hasNode(H*x)
	{
		int a=findIndex(*x);
		if(a!=-1)
		{
			return 1;
		}
		return 0;
	}
	int hasEdge(Node<H>*x,Node<H>*y)
	{
		int i=findIndex(x->getInfo());
		int j=findIndex(y->getInfo());
		if((i!=-1) && (j!=-1))
		{
			if(mat[i][j])
			{
				return 1;
			}
		}
		return 0;
	}
	void bfs()
	{
		bfsvisit(0);	
	}
	void stampa()
	{
		for(int i=0; i<=n-1; i++)
		{
			cout<<"["<<*Grafo[i]<<"]->";
			for(int j=0; j<=n-1; j++)
			{
				if(mat[i][j])
				{
					cout<<*Grafo[j]<<" ";
				}
			}
			cout<<endl;
		}
	}
	friend ostream& operator <<(ostream &str, Graph&a)
	{
		a.stampa();
		return str;
	}
};

int main()
{
	Graph<int>*gr=new Graph<int>(10);
	Node<int>*a=new Node<int>(0);
	Node<int>*b=new Node<int>(1);
	Node<int>*c=new Node<int>(2);
	Node<int>*d=new Node<int>(3);
	Node<int>*e=new Node<int>(4);
	gr->addNode(a->get_pinfo())->addNode(b->get_pinfo())->addNode(c->get_pinfo())->addNode(d->get_pinfo())->addNode(e->get_pinfo());
	gr->addEdge(a,e)->addEdge(e,b)->addEdge(e,c)->addEdge(b,d);
	cout<<*gr<<endl;
	gr->bfs();
	int*f=new int(3);
	cout<<(gr->hasNode(f))<<endl;
	cout<<(gr->hasEdge(e,c))<<endl;
}
