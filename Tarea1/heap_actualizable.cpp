#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unistd.h>

#define inf 10000000

using namespace std;

template <class TPriority, class TKey>
class UpdatableHeap {
    private:
        vector<pair <TPriority, TKey>> tree;
        vector<unsigned int> tpos;
        int tree_size;
        void fixDown(int pos);
        void fixUp(int pos);
    public:
        UpdatableHeap<TPriority, TKey>() {
            tree_size = 0;
            //tree.reserve(1000);
            //tpos.reserve(1000);
        }
        ~UpdatableHeap<TPriority, TKey>()   {
            tree.clear();
            tpos.clear();
        }
        pair<TPriority, TKey> top();
        void pop();
        void insertOrUpdate(const TPriority &p, const TKey &k);
        bool isInserted(const TKey &k);
        int getSize() {return tree_size;}
        void erase(const TKey &k);
};

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::fixDown(int pos)    {
    // Fix down by priority 
    int left, right, F, S;
    bool  lRot, rRot, leaf;
    while(1)    {
        // Have I a Left son?
        lRot = rRot = leaf = 0;
        if(2*tpos[pos]+1 <= (int)tpos.size()) {
            if(tpos[2*tpos[pos]+1] != -1) {
                // Yes! I have a Left son
                left = tpos[2*tpos[pos]+1];
                // Have I a Right son?
                if(2*tpos[pos]+2 <= (int)tpos.size()) {
                    if(tpos[2*tpos[pos]+2] != -1) {
                        // Yes! I have a Right son
                        right = tpos[2*tpos[pos]+2];
                        // Who has a greater priority?
                        if(tree[left].first == tree[right].first) // Both have same priority
                            {tree[left].second.compare(tree[right].second) > 0 ? rRot=1 : lRot=1;}
                        else 
                            {tree[left].first > tree[right].first ? rRot=1 : lRot=1;}
                    }
                    // I just have a Left son
                    else
                        {rRot = 1;}
                }
                // I just have a Left son
                else
                    {rRot = 1;}
            }
            // I don't have a Left son
            // Have I a Right son?
            if(2*tpos[pos]+2 <= (int)tpos.size()) {
                if(tpos[2*tpos[pos]+2] != -1) {
                    // Yes! I have a Right son
                    right = tpos[2*tpos[pos]+2];
                    // I just have a Right son
                    lRot=1;
                }
                // I am a leaf
                else
                    {leaf = 1;}
            }
            // I am a leaf
            else
                {leaf = 1;}
        }
        // I don't have a Left son
        // Have I a Right son?
        if(2*tpos[pos]+2 <= (int)tpos.size()) {
            if(tpos[2*tpos[pos]+2] != -1) {
                // Yes! I have a Right son
                right = tpos[2*tpos[pos]+2];
                // I just have a Right son
                lRot = 1;
            }
            // I am a leaf
            else
                {leaf = 1;}
        }
        // I am a leaf
        else
            {leaf = 1;}
        
        /*** Fixing rotation ***/
        // Am I a leaf?
        if(leaf == 1) {
            tpos[pos] = -1;
            tree_size--;
            return;
        }
        // Extend memory
        pair<TPriority, TKey> vacio=make_pair(-1,string("-1"));
        for(int i=(int)tpos.size(); i<=2*(2*tpos[pos]+2)+2; i++) {
            tpos.push_back(-1);
            tree.push_back(vacio);
        }
        // Right rotation
        if(rRot == 1) {
            F = tpos[pos];  // Father
            S = left;       // Son
            tpos[2*F+1] = tpos[2*S+2];
            tpos[2*S+2] = F;
            tpos[pos] = S;
            pos = 2*S+2;
        }
        // Left rotation
        else    {
            F = tpos[pos];  // Father
            S = right;       // Son
            tpos[2*F+2] = tpos[2*S+1];
            tpos[2*S+1] = F;
            tpos[pos] = S;
            pos = 2*S+1;
        }
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::fixUp(int pos)    {
    // Fix up by priority 
    int F, S;
    bool  lRot, rRot;
    while(1)    {
        // Am I the root?
        if(pos == 0)
            return;
        // Am I a Left son? Then, Right rotation
        lRot = rRot = 0;
        F = tpos[(int)(tpos[pos]-1)/2];
        S = tpos[pos];
        tree[S].second.compare( tree[F].second ) < 0 ? rRot=1 : lRot=1;
        
        /*** Fixing rotation ***/
        // Extend memory
        pair<TPriority, TKey> vacio=make_pair(-1,string("-1"));
        for(int i=(int)tpos.size(); i<=(2*tpos[pos]+2); i++) {
            tpos.push_back(-1);
            tree.push_back(vacio);
        }
        // Right rotation
        if(rRot == 1) {
            // I am a Left son
            tpos[2*F+1] = tpos[2*S+2];
            tpos[2*S+2] = F;
            tpos[(int)(tpos[pos]-1)/2] = S;
            pos = (int)(tpos[pos]-1)/2;
        }
        // Left rotation
        else    {
            // I am a Right son
            tpos[2*F+2] = tpos[2*S+1];
            tpos[2*S+1] = F;
            tpos[(int)(tpos[pos]-1)/2] = S;
            pos = (int)(tpos[pos]-1)/2;
        }
    }
}

template <class TPriority, class TKey>
pair<TPriority, TKey> UpdatableHeap<TPriority, TKey>::top()    {
    if(tree_size > 0)
        return tree[tpos[0]];
    else
        return make_pair(-1,string("-1"));
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::pop()    {
    // Fix down by priority
    int pos=0;
    if(tree_size > 0)  {
        fixDown(pos);
        tree_size--;
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::insertOrUpdate(const TPriority &p, const TKey &k)   {
    // Void tree
    if(tree_size == 0)  {
        tree.push_back(make_pair(p,k));
        tpos.push_back(0);
        tree_size++;
        return;
    }
    // Insert as BST by key
    int pos=0, vsize;
    pair<TPriority, TKey> vacio=make_pair(-1,string("-1"));
    while(1)    {
        // Free space to new node
        if(tpos[pos] == -1)   {
            tpos[pos] = pos;
            tree[pos] = make_pair(p,k);
            tree_size++;
            break;
        }
        // We found the same key
        if(tree[tpos[pos]].second.compare(k) == 0)    {
            tree[tpos[pos]].first = p;
            break;
        }
        // Keep searching
        tree[tpos[pos]].second.compare(k) > 0 ? pos=2*tpos[pos]+1 : pos=2*tpos[pos]+2;
        // Extended memory
        vsize = (int)tpos.size();
        if(pos >= vsize)  {
            for(; vsize<=pos; vsize++) {
                tree.push_back(vacio);
                tpos.push_back(-1);
            }
        }
    }
    
    // Fix up by priority
    fixUp(pos);
}

template <class TPriority, class TKey>
bool UpdatableHeap<TPriority, TKey>::isInserted(const TKey &k)  {
    // Binary search in the BST by key
    int pos=tpos[0];
    int vsize = (int)tpos.size();
    while(1)    {
        // Position out of bounds
        if(vsize <= pos)
            return false;
        if(tpos[pos] == -1)
            return false;
        // We found the key
        if(tree[tpos[pos]].second.compare(k) == 0)
            return true;
        // Keep searching
        tree[tpos[pos]].second.compare(k) > 0 ? pos=2*pos+1 : pos=2*pos+2;
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::erase(const TKey &k)    {
    // Binary search in the BST by key
    int pos=tpos[0];
    int vsize = (int)tpos.size();
    while(1)    {
        // It does not exist
        if(vsize <= pos)
            return;
        if(tpos[pos] == -1)
            return;
        // Proceed to delete node by fix down
        if(tree[tpos[pos]].second.compare(k) == 0) 
            // Fix down by priority
            fixDown(pos);
        // Keep searching
        tree[tpos[pos]].second.compare(k) > 0 ? pos=2*pos+1 : pos=2*pos+2;
    }
}

int main()    {
    unsigned int N;
    int prty, aux;
    string key;
    string op;
    UpdatableHeap<int, string> tree;
    pair<int, string> p;
    cin >> N;
    for(int i=0; i<N; i++)  {
        cin >> op;
        op == "P" ? aux=1 : (op == "IU" ? aux=2 : (op == "DL" ? aux=3 : (op == "D" ? aux=4 : aux=-1)));
        switch(aux)  {
            case(1):  {
                p = tree.top();
                p.second.compare(string("-1")) == 0 ? cout<<-1 : cout<<p.second<<" "<<p.first;
                cout<<endl;
                break;
            }
            case(2): {
                cin >> key >> prty;
                tree.insertOrUpdate(prty,key);
                break;
            }
            case(3): {
                tree.pop();
                break;
            }
            case(4):  {
                cin >> key;
                tree.erase(key);
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
