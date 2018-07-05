#include<iostream>
#include<cstdlib>
#include "BST.cpp"
using namespace std;

template<class T>
class RBT: public BST<T>
{
private:
    static const int rosso=0;
    static const int nero=1;
    static const int snero=2;
    static const bool sinistra=true;
    static const bool destra=false;
    void rbInsertFixUp(Nodo<T>*pa)
    {
        if((pa==BST<T>::pradice) && (pa->getColore()==rosso))
        {
            pa->setColore(nero);
        }
        else
        {
            if(pa->getUp()!=BST<T>::pradice)
            {
                Nodo<T>*pb=pa->getUp();
                if(pb->getColore()==rosso)
                {
                    Nodo<T>*pc;
                    bool direction=false;
                    if(pb->getUp()->getSx()==pb)
                    {
                        pc=pb->getUp()->getDx();
                        direction=sinistra;
                    }
                    else if(pb->getUp()->getDx()==pb)
                    {
                        pc=pb->getUp()->getSx();
                        direction=destra;
                    }
                    if((pc) && (pc->getColore()==rosso))
                    {
                        if(pb->getUp()!=BST<T>::pradice)
                        {
                            pb->getUp()->setColore(rosso);
                        }
                        pb->setColore(nero);
                        pc->setColore(nero);
                        if((pb->getUp()->getColore()==rosso) && (pb->getUp()->getUp()->getColore()==rosso))
                        {
                            rbInsertFixUp(pb->getUp());
                        }
                    }
                    else if((!pc) || (pc->getColore()==nero))
                    {
                        if(direction==sinistra)
                        {
                            if(pb->getSx()==pa)
                            {
                                pb->setColore(nero);
                                pb->getUp()->setColore(rosso);
                                BST<T>::dxRotate(pb->getUp()->getInfo());
                            }
                            else if(pb->getDx()==pa)
                            {
                                pa->setColore(nero);
                                pb->setColore(rosso);
                                pb->getUp()->setColore(rosso);
                                BST<T>::sxRotate(pb->getInfo());
                                BST<T>::dxRotate(pa->getUp()->getInfo());
                            }
                        }
                        else if(direction==destra)
                        {
                            if(pb->getDx()==pa)
                            {
                                pb->setColore(nero);
                                pb->getUp()->setColore(rosso);
                                BST<T>::sxRotate(pb->getUp()->getInfo());
                            }
                            else if(pb->getSx()==pa)
                            {
                                pa->setColore(nero);
                                pb->setColore(rosso);
                                pb->getUp()->setColore(rosso);
                                BST<T>::dxRotate(pb->getInfo());
                                BST<T>::sxRotate(pa->getUp()->getInfo());
                            }
                        }
                    }
                }
            }
        }
    }
public:
    RBT<T>(): BST<T>() {}
    RBT<T>*ins(T x)
    {
        Nodo<T>*pa=new Nodo<T>(x);
        BST<T>::ins(pa->getInfo());
        rbInsertFixUp(BST<T>::lastFind(x));
        return this;
    }
    const char* colore(int c)
    {
        if(c==rosso)
        {
            return "rosso";
        }
        if(c==nero)
        {
            return "nero";
        }
        return "rosso";
    }
};

int main(int argc, char**argv)
{
    RBT<int>*r=new RBT<int>();
    if(argc==1){cout<<endl<<endl<<endl<<endl<<endl<<"Albero rosso-nero"<<endl<<endl<<endl<<endl<<endl;exit(0);}
    int ordine=1;
    int c=1;
    if(strcmp(argv[1],"-i")==0)
    {
        ordine=1;
        c++;
    }
    else if(strcmp(argv[1],"-post")==0)
    {
        ordine=2;
        c++;
    }
    else if(strcmp(argv[1],"-pre")==0)
    {
        ordine=3;
        c++;
    }
    for(int i=c; i<=argc-1; i++)
    {
        r->ins(atoi(argv[i]));
    }
    r->stampa(ordine);
}
