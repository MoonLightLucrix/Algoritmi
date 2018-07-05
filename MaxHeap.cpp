#include<iostream>
#include<cstdlib>
#include "BHeap.cpp"
using namespace std;

template<class T>
class MaxHeap:public Heap<T>
{
private:
public:
    T compare(T*a,T*b)
    {
        return (*a)-(*b);
    }
    MaxHeap<T>(int s): Heap<T>(s) {}
    MaxHeap<T>(T*Nodo,int s): Heap<T>(Nodo,s) {}
    MaxHeap<T>*extractMax()
    {
        Heap<T>::extract();
        return this;
    }
    void incrementa(T x,int a)
    {
        Heap<T>::modify(x,a);
    }
};

int main(int argc, char**argv)
{
    MaxHeap<int>*m=new MaxHeap<int>(argc+5);
    if(argc==1){cout<<endl<<endl<<endl<<endl<<endl<<"MaxHeap"<<endl<<endl<<endl<<endl<<endl;exit(0);}
    int*vett=new int[argc-1];
    for(int i=0; i<=argc-2; i++)
    {
        vett[i]=(atoi(argv[i+1]));
    }
    m->buildHeap(vett,argc-1);
    m->enqueue(7)->enqueue(10)->enqueue(12);
    m->extractMax()->extractMax();
    cout<<*m<<endl;
}
