#include<iostream>
#include<cstdlib>
using namespace std;

template<class T>
class BHeap
{
public:
	virtual BHeap<T>*enqueue(T x)=0;
	virtual T*top()=0;
	virtual BHeap<T>*extract()=0;
	virtual BHeap<T>*buildHeap(T*v, int n)=0;
	virtual void stampa()=0;	
};

template<class T>
class Heap:public BHeap<T>
{
private:
	T**Nodo;
	int heaps;
	int N;
	int sx(int a)
	{
		return a<<1;
	}
	int dx(int a)
	{
		return (a<<1)+1;
	}
	int up(int a)
	{
		return a>>1;
	}
	void scambia(int a,int b)
	{
		T*x=Nodo[a];
		Nodo[a]=Nodo[b];
		Nodo[b]=x;
	}
	void heapify(int a)
	{
        if(a<=heaps)
        {
            int i=sx(a);
            int j=dx(a);
            int select=a;
            if((i>=1) && (compare(Nodo[select],Nodo[i])>=0))
            {
                select=i;
            }
            if((j>=1) && (compare(Nodo[select],Nodo[j])>=0))
            {
                select=j;
            }
            if(select!=a)
            {
                scambia(a,select);
                heapify(select);
            }
        }
	}
	void trapianta()
	{
		for(int i=heaps>>1; i>=1; i--)
		{
			if(dx(i)>heaps)
			{
				if(compare(Nodo[i],Nodo[sx(i)])<=-1)
				{
					scambia(i,sx(i));
					i=(heaps>>1)+1;
				}
			}
			else
			{
				if(compare(Nodo[sx(i)],Nodo[dx(i)])>=0)
				{
					if(compare(Nodo[i],Nodo[sx(i)])<=-1)
					{
						scambia(i,sx(i));
						i=(heaps>>1)+1;
					}
				}
				else
				{
					if(compare(Nodo[i],Nodo[dx(i)])<=-1)
					{
						scambia(i,dx(i));
						i=(heaps>>1)+1;
					}
				}
			}
		}
	}
	T*dequeue()
	{
		if(!heaps)
		{
			cout<<"Heap vuoto!"<<endl;
			return NULL;
		}
        scambia(1,heaps);
		T*x=Nodo[heaps];
		heaps--;
		heapify(1);
		trapianta();
		return x;
	}
public:
	virtual T compare(T*a,T*b)=0;
	Heap<T>(int s): N(s), Nodo(new T*[s]), heaps(0) {}
	Heap<T>(T*Nodo, int s): N(s+1), Nodo(Nodo), heaps(s) {}
	int getHeapsize()
	{
		return heaps;
	}
	BHeap<T>*enqueue(T x)
	{
		if(heaps+1==N)
		{
			cout<<"Heap pieno!"<<endl;
		}
		else
		{
			heaps++;
			Nodo[heaps]=new T(x);
			int a=heaps;
			while((a>=2) && (compare(Nodo[a],Nodo[up(a)])>=0))
			{
				scambia(a,up(a));
				a=up(a);
			}
		}
		return this;
	}
	T*top()
	{
		return Nodo[1];
	}
	BHeap<T>*extract()
	{
		T*x=dequeue();
		return this;
	}
	void modify(T x,int a)
	{
		if((a>=1) && (a<=heaps))
		{
			if(compare(Nodo[a],&x)<=-1)
			{
				Nodo[a]=new T(x);
				while((a>=2) && (compare(Nodo[a],Nodo[up(a)])>=0))
				{
					scambia(a,up(a));
					a=up(a);
				}
			}
		}
	}
    BHeap<T>*buildHeap(T*v, int n)
    {
        if(heaps+n+1<=N)
        {
            for(int i=0; i<=n-1; i++)
            {
                heaps++;
                Nodo[heaps]=new T(v[i]);
            }
            trapianta();
        }
        return this;
    }
    void stampa()
    {
        if(!heaps)
        {
            cout<<"Heap vuoto!"<<endl;
        }
        else
        {
            for(int i=1; i<=heaps; i++)
            {
                cout<<*Nodo[i];
                if(i!=heaps)
                {
                    cout<<", ";
                }
            }
        }
    }
    friend ostream& operator <<(ostream &str, Heap&a)
    {
        a.stampa();
        return str;
    }
};
