#include <list>
using std::list;

// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include<climits>
using namespace std;

#include <iterator>

#include <vector>

struct Pair { double key; int value; };

void swap(Pair **x, Pair **y)
{
    Pair** temp = x;
    x = y;
    y = temp;
}

void swap (int* x, int* y) 
{
    int* temp = x;
    x = y;
    y = temp;
}

class MinHeap
{
    Pair **harr;
    int capacity;
    int heap_size;
public:

    MinHeap(int capacity);

    void MinHeapify(int i, int*);

    int parent(int i) { return (i-1)/2; }

    int left(int i) { return (2*i + 1); }

    int right(int i) { return (2*i + 2); }

    Pair* extractMin(int*);

    void decreaseKey(int, double, int*);

    Pair* getMin() { return harr[0]; }

    void deleteKey(int i, int*);

    int insertKey(double k, int v, int p[]);

    bool isEmpty() { return heap_size == 0; }

    double indexKey(int i) { return harr[i]->key; }
};
  

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;

    harr = new Pair*[cap];
}
  


int MinHeap::insertKey(double k, int v, int p[])
{


    heap_size++;
    int i = heap_size - 1;
    Pair* par = new Pair; 
    par->key = k; par->value = v;
    harr[i] = par;
	p[v] = i;

    while (i != 0 && harr[parent(i)]->key > harr[i]->key)
    {
        swap(harr[i], harr[parent(i)]);
		swap(p[harr[i]->value], p[harr[parent(i)]->value]);
        i = parent(i);
    }

    return i;
}
  
void MinHeap::decreaseKey(int i, double new_val, int p[])
{
    harr[i]->key = new_val;
    while (i != 0 && harr[parent(i)]->key > harr[i]->key)
    {
        swap(harr[i], harr[parent(i)]);
		swap(p[harr[i]->value], p[harr[parent(i)]->value]);
        i = parent(i);
    }
}
  

Pair* MinHeap::extractMin(int p[])
{

    if (heap_size <= 0)
    {
        Pair* p = new Pair; p->key = INT_MAX;  p->value = INT_MAX;
        return p;
    }
    if (heap_size == 1)
    {
        heap_size--; 
        return harr[0];
    }


    Pair* root = harr[0];
    harr[0] = harr[heap_size-1];
	p[harr[heap_size-1]->value] = 0;
    heap_size--;
    MinHeapify(0, p);

    return root;
}



void MinHeap::deleteKey(int i, int p[])
{
    decreaseKey(i, INT_MIN, p);
    extractMin(p);
}
  
void MinHeap::MinHeapify(int i, int p[])
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l]->key < harr[i]->key)
        smallest = l;
    if (r < heap_size && harr[r]->key < harr[smallest]->key)
        smallest = r;
    if (smallest != i)
    {
        swap(harr[i], harr[smallest]);
		int temp = p[harr[i]->value];
		p[harr[i]->value] = p[harr[smallest]->value];
		p[harr[smallest]->value] = temp;
        MinHeapify(smallest, p);
    }
}


int main () 
{
    int l, m, n; double o;

    scanf("dl\nformat=edgelist1\nn=%d\ndata:",&n);

    n++;

    int* pai = new int[n];
    int* pos = new int[n];

    for (int i = 0; i < n; i++)
    {
        pai[i] = -1;
        pos[i] = -1;
    }

    MinHeap h(n);
    vector<list<Pair>> adj;
    adj.resize(n);

    while (scanf("%d %d %lf", &l, &m, &o) == 3)
    {
        Pair temp1; temp1.key = o; temp1.value = l;
        Pair temp2; temp2.key = o; temp2.value = m;
        adj[l].push_back(temp2);
        adj[m].push_back(temp1);
    }

    for (auto a : adj[1])
    {
        pos[a.value] = h.insertKey(a.key, a.value, pos);
        pai[a.value] = 1;
    }

    double peso = 0.00;

    pai[1] = 1;

    while (!h.isEmpty()) 
    {
        Pair u = *(h.extractMin(pos));
        pos[u.value] = -1;
        peso += u.key;

        for (auto v : adj[u.value])
        {
            if (pai[v.value] == -1)
            {
                pai[v.value] = u.value;
                pos[v.value] = h.insertKey(v.key, v.value, pos);
            }

            else if (pos[v.value] != -1)
            {
				

                if (v.key < (h.indexKey(pos[v.value])))
                {
                    h.decreaseKey(pos[v.value], v.key, pos);
                    pai[v.value] = u.value;
                }
            }
        }
    }

    printf("%.3lf\n", peso);
}