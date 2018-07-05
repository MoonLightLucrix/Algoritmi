#include<iostream>
#include<cstdlib>
using namespace std;

template<class T>
class Nodo
{
private:
    T info;
    Nodo<T>*psucc;
    Nodo<T>*pprec;
public:
    Nodo<T>(T info, Nodo<T>*psucc=0, Nodo<T>*pprec=0): info(info), psucc(psucc), pprec(pprec) {}
    void set_psucc(Nodo<T>*psucc)
    {
        this->psucc=psucc;
    }
    Nodo<T>*get_psucc()
    {
        return psucc;
    }
    void set_pprec(Nodo<T>*pprec)
    {
        this->pprec=pprec;
    }
    Nodo<T>*get_pprec()
    {
        return pprec;
    }
    void setInfo(T info)
    {
        this->info=info;
    }
    T getInfo()
    {
        return info;
    }
    T*get_pinfo()
    {
        return &info;
    }
};

template<class T>
class Lista
{
protected:
    Nodo<T>*ptesta;
    Nodo<T>*pcoda;
    int s;
private:
    Nodo<T>*find(T x)
    {
        for(Nodo<T>*pa=ptesta; (pa); pa=pa->get_psucc())
        {
            if(pa->getInfo()==x)
            {
                return pa;
            }
        }
        return NULL;
    }
public:
    Lista<T>(): ptesta(NULL), pcoda(NULL), s(0) {}
    Nodo<T>*get_ptesta()
    {
        return ptesta;
    }
    Nodo<T>*get_pcoda()
    {
        return pcoda;
    }
    int getSize()
    {
        return s;
    }
    Lista<T>*ins(T x)
    {
        Nodo<T>*pa=new Nodo<T>(x);
        if(!s)
        {
            ptesta=pcoda=pa;
            s++;
        }
        else
        {
            pa->set_pprec(pcoda);
            pcoda->set_psucc(pa);
            pa->set_psucc(NULL);
            pcoda=pa;
            s++;
        }
        return this;
    }
    T*search(T x)
    {
        return find(x)->get_pinfo();
    }
    Lista<T>*del(T x)
    {
        Nodo<T>*pa=find(x);
        if(pa)
        {
            if(pa==ptesta)
            {
                ptesta=ptesta->get_psucc();
                ptesta->set_pprec(NULL);
                delete pa;
                s--;
            }
            else if(pa==pcoda)
            {
                pcoda=pcoda->get_pprec();
                pcoda->set_psucc(NULL);
                delete pa;
                s--;
            }
            else
            {
                pa->get_pprec()->set_psucc(pa->get_psucc());
                pa->get_psucc()->set_pprec(pa->get_pprec());
                delete pa;
                s--;
            }
        }
        return this;
    }
    void stampa()
    {
        for(Nodo<T>*pa=ptesta; pa; pa=pa->get_psucc())
        {
            cout<<pa->getInfo();
            if(pa->get_psucc())
            {
                cout<<", ";
            }
        }
    }
    friend ostream& operator <<(ostream &str, Lista&a)
    {
        a.stampa();
        return str;
    }
};

/*int main(int argc, char**argv)
{
    Lista<int>*l=new Lista<int>();
    for(int i=1; i<=argc-1; i++)
    {
        l->ins(atoi(argv[i]));
    }
    cout<<*l<<endl;
    l->del(4)->del(45);
    cout<<*l<<endl;
    if(l->search(5))
    {
        cout<<"True"<<endl;
    }
    else
    {
        cout<<"False"<<endl;
    }
}*/
