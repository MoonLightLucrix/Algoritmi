#include<iostream>
#include<cstdlib>
using namespace std;

template<class T>
class Nodo
{
private:
	T info;
    int colore;
	Nodo<T>*sx;
	Nodo<T>*dx;
	Nodo<T>*up;
public:
	Nodo<T>(T info, Nodo<T>*sx=0, Nodo<T>*dx=0, Nodo<T>*up=0): info(info), colore(0), sx(sx), dx(dx), up(up) {}
	void setSx(Nodo<T>*sx)
	{
		this->sx=sx;
	}
	Nodo<T>*getSx()
	{
		return sx;
	}
	void setDx(Nodo<T>*dx)
	{
		this->dx=dx;
	}
	Nodo<T>*getDx()
	{
		return dx;
	}
	void setUp(Nodo<T>*up)
	{
		this->up=up;
	}
	Nodo<T>*getUp()
	{
		return up;
	}
	void setInfo(T info)
	{
		this->info=info;
	}
    void setColore(int colore)
    {
        this->colore=colore;
    }
    int getColore()
    {
        return colore;
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
class BST
{
protected:
	Nodo<T>*pradice;
	int s;
    Nodo<T>*lastFind(T x)
    {
        Nodo<T>*pa=pradice;
        Nodo<T>*pb=NULL;
        while(pa)
        {
            if(x>pa->getInfo())
            {
                pa=pa->getDx();
            }
            else if(x<pa->getInfo())
            {
                pa=pa->getSx();
            }
            else if(x==pa->getInfo())
            {
                pb=pa;
                pa=pa->getDx();
            }
        }
        return pb;
    }
    void inorder(Nodo<T>*pa)
    {
        if(pa)
        {
            inorder(pa->getSx());
            cout<<pa->getInfo()<<"<-"<<colore(pa->getColore())<<endl;
            inorder(pa->getDx());
        }
    }
    void postorder(Nodo<T>*pa)
    {
        if(pa)
        {
            postorder(pa->getSx());
            postorder(pa->getDx());
            cout<<pa->getInfo()<<"<-"<<colore(pa->getColore())<<endl;
        }
    }
    void preorder(Nodo<T>*pa)
    {
        if(pa)
        {
            cout<<pa->getInfo()<<"<-"<<colore(pa->getColore())<<endl;
            preorder(pa->getSx());
            preorder(pa->getDx());
        }
    }
private:
    Nodo<T>*find(T x)
    {
        Nodo<T>*pa=pradice;
        while((pa) && (pa->getInfo()!=x))
        {
            if(x>pa->getInfo())
            {
                pa=pa->getDx();
            }
            else
            {
                pa=pa->getSx();
            }
        }
        return pa;
    }
    Nodo<T>*max(Nodo<T>*pa)
    {
        if(pa)
        {
            while(pa->getDx())
            {
                pa=pa->getDx();
            }
        }
        return pa;
    }
    Nodo<T>*min(Nodo<T>*pa)
    {
        if(pa)
        {
            while(pa->getSx())
            {
                pa=pa->getSx();
            }
        }
        return pa;
    }
    void trapianta(Nodo<T>*pa, Nodo<T>*pb)
    {
        if(!pa->getUp())
        {
            pradice=pb;
        }
        else if(pa->getUp()->getSx()==pa)
        {
            pa->getUp()->setSx(pb);
        }
        else if(pa->getUp()->getDx()==pa)
        {
            pa->getUp()->setDx(pb);
        }
        if(pb)
        {
            pb->setUp(pa->getUp());
        }
    }
    int altezza(Nodo<T>*pa)
    {
        if(!pa)
        {
            return -1;
        }
        int Sx=altezza(pa->getSx());
        int Dx=altezza(pa->getDx());
        int max;
        if(Sx>=Dx)
        {
            max=Sx;
        }
        else
        {
            max=Dx;
        }
        return max+1;
    }
    Nodo<T>*predecessore(Nodo<T>*pa)
    {
        if(pa->getDx())
        {
            return max(pa->getSx());
        }
        else
        {
            Nodo<T>*pb=pa->getUp();
            while(pb->getDx()==pa)
            {
                pa=pb;
                pb=pb->getUp();
            }
            return pb;
        }
        return pa;
    }
    Nodo<T>*successore(Nodo<T>*pa)
    {
        if(pa->getDx())
        {
            return min(pa->getDx());
        }
        else
        {
            Nodo<T>*pb=pa->getUp();
            while(pb->getSx()==pa)
            {
                pa=pb;
                pb=pb->getUp();
            }
            return pb;
        }
        return pa;
    }
public:
    virtual const char* colore(int c)=0;
    BST<T>(): pradice(0), s(0) {}
	Nodo<T>*get_pradice()
    {
        return pradice;
    }
    int getSize()
    {
        return s;
    }
    BST<T>*ins(T x)
    {
        Nodo<T>*pa=new Nodo<T>(x);
        if(!s)
        {
            pradice=pa;
            s++;
        }
        else
        {
            Nodo<T>*pb=pradice;
            Nodo<T>*pc;
            while(pb)
            {
                pc=pb;
                if(x>=pb->getInfo())
                {
                    pb=pb->getDx();
                }
                else
                {
                    pb=pb->getSx();
                }
            }
            pa->setUp(pc);
            if(x>=pc->getInfo())
            {
                pc->setDx(pa);
            }
            else
            {
                pc->setSx(pa);
            }
            s++;
        }
        return this;
    }
    BST<T>*del(T x)
    {
        Nodo<T>*pa=find(x);
        if(!pa){return this;}
        if(!pa->getDx())
        {
            trapianta(pa,pa->getSx());
        }
        else if(!pa->getSx())
        {
            trapianta(pa,pa->getDx());
        }
        else if((pa->getSx()) && (pa->getDx()))
        {
            Nodo<T>*pb=min(pa->getDx());
            if(pb->getUp()!=pa)
            {
                trapianta(pb,pb->getDx());
                pb->setDx(pa->getDx());
                pb->getDx()->setUp(pb);
            }
            trapianta(pa,pb);
            pb->setSx(pa->getSx());
            pb->getSx()->setUp(pb);
        }
        delete pa;
        s--;
        return this;
    }
    int depht()
    {
        return altezza(pradice);
    }
    T*search(T x)
    {
        return find(x)->get_pinfo();
    }
    T*predecessore(T x)
    {
        return predecessore(find(x))->get_pinfo();
    }
    T*successore(T x)
    {
        return successore(find(x))->get_pinfo();
    }
    BST<T>*sxRotate(T x)
    {
        Nodo<T>*pa=find(x);
        if((pa) && (pa->getDx()))
        {
            Nodo<T>*pb=pa->getDx();
            if(pa==pradice)
            {
                pa->setDx(NULL);
                pb->setUp(NULL);
                pa->setUp(pb);
                pa->setDx(pb->getSx());
                pb->setSx(pa);
                pradice=pb;
            }
            else
            {
                Nodo<T>*pc=pa->getUp();
                if(pc->getDx()==pa)
                {
                    pc->setDx(pb);
                }
                else if(pc->getSx()==pa)
                {
                    pc->setSx(pb);
                }
                pb->setUp(pc);
                pa->setUp(NULL);
                pa->setDx(NULL);
                pc=pb;
                pb=pc->getSx();
                pa->setUp(pc);
                pc->setSx(pa);
                if(pb)
                {
                    pb->setUp(pa);
                    pa->setDx(pb);
                }
            }
        }
        return this;
    }
    BST<T>*dxRotate(T x)
    {
        Nodo<T>*pa=find(x);
        if((pa) && (pa->getSx()))
        {
            Nodo<T>*pb=pa->getSx();
            if(pa==pradice)
            {
                pa->setSx(NULL);
                pb->setUp(NULL);
                pa->setUp(pb);
                pa->setSx(pb->getDx());
                pb->setDx(pa);
                pradice=pb;
            }
            else
            {
                Nodo<T>*pc=pa->getUp();
                if(pc->getSx()==pa)
                {
                    pc->setSx(pb);
                }
                else if(pc->getDx()==pa)
                {
                    pc->setDx(pb);
                }
                pb->setUp(pc);
                pa->setUp(NULL);
                pa->setSx(NULL);
                pc=pb;
                pb=pc->getDx();
                pa->setUp(pc);
                pc->setDx(pa);
                if(pb)
                {
                    pb->setUp(pa);
                    pa->setSx(pb);
                }
            }
        }
        return this;
    }
    void stampa(int ordine)
    {
        if(ordine==1)
        {
            inorder(pradice);
        }
        else if(ordine==2)
        {
            postorder(pradice);
        }
        else if(ordine==3)
        {
            preorder(pradice);
        }
    }
    friend ostream& operator <<(ostream &str, BST&a)
    {
        a.stampa();
        return str;
    }
};
