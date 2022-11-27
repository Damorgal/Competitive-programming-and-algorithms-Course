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
        vector<vector <int>> tpos; // [left son, right son, father]
        int tree_size, root;
        void fixDown(int pos);
        void fixUp(int pos);
        void deleteDown(int pos);
    public:
        UpdatableHeap<TPriority, TKey>() {
            tree_size = 0;
            root = -1;
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
void UpdatableHeap<TPriority, TKey>::deleteDown(int pos)    {
    // Fix down by priority
    int left, right, F, S;
    bool  lRot, rRot, leaf;
    while(1)    {
        // Have I a Left son?
        lRot = rRot = leaf = 0;
        left = tpos[pos][0];
        right = tpos[pos][1];
        if(tpos[pos][0] != -1)    {
            // Yes! I have a Left son
            // Have I a Right son?
            if(tpos[pos][1] != -1)  {
                // Yes! I have a Right son
                // Who has a greater priority?
                if(tree[left].first == tree[right].first) // Both have same priority
                    tree[left].second.compare(tree[right].second) > 0 ? rRot=1 : lRot=1;
                else
                    tree[left].first > tree[right].first ? rRot=1 : lRot=1;
            }
            // I just have a Left son
            else
                rRot = 1;
        }
        else    {
            // I don't have a Left son
            // Have I a Right son?
            if(tpos[pos][1] != -1) {
                // Yes! I have a Right son
                // I just have a Right son
                lRot=1;
            }
            // I am a leaf
            else
                leaf = 1;
        }
        /*** Fixing rotation ***/
        // Am I a leaf?
        if(leaf == 1) {
            if(pos == root) {
                root = -1;
                tpos[pos][2]=-1;
                //tree_size=0;
            }
            else    {
                F = tpos[pos][2];
                tpos[F][0] == pos ? tpos[F][0] = -1 : tpos[F][1] = -1;
                tpos[pos][2] = -1;
                //tree_size--;
            }
            return;
        }
        F = pos;
        // Right rotation
        if(rRot == 1) {
            // I have a Left son
            S = tpos[F][0];
            tpos[F][0] = tpos[S][1];
            tpos[S][1] = F;
            tpos[S][2] = tpos[F][2];
            tpos[F][2] = S;
        }
        // Left rotation
        else    {
            // I have a Right son
            S = tpos[F][1];
            tpos[F][1] = tpos[S][0];
            tpos[S][0] = F;
            tpos[S][2] = tpos[F][2];
            tpos[F][2] = S;
        }
        // Check if it is a root
        if(tpos[S][2] == F) {
            root = S;
            tpos[S][2] = S;
        }
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::fixDown(int pos)    {
    // Fix down by priority
    int left, right, F, S;
    bool  lRot, rRot, leaf;
    while(1)    {
        // Have I a Left son?
        lRot = rRot = leaf = 0;
        left = tpos[pos][0];
        right = tpos[pos][1];
        if(tpos[pos][0] != -1)    {
            // Yes! I have a Left son
            // Have I a Right son?
            if(tpos[pos][1] != -1)  {
                // Yes! I have a Right son
                // I have greater piority
                if(tree[left].first <= tree[pos].first && tree[right].first < tree[pos].first)
                    return;
                if(tree[left].first > tree[pos].first || tree[right].first >= tree[pos].first)  {
                    //   Who has a greater priority?
                    if(tree[left].first == tree[right].first) // Both have same priority
                        tree[left].second.compare(tree[right].second) > 0 ? rRot=1 : lRot=1;
                    else
                        tree[left].first > tree[right].first ? rRot=1 : lRot=1;
                }
            }
            // I just have a Left son
            else    {
                if(tree[left].first > tree[pos].first)
                    rRot = 1;
                else
                    return;

            }
        }
        else    {
            // I don't have a Left son
            // Have I a Right son?
            if(tpos[pos][1] != -1) {
                // Yes! I have a Right son
                // I just have a Right son
                if(tree[right].first >= tree[pos].first)
                    lRot=1;
                else
                    return;
            }
            // I am a leaf
            else
                leaf = 1;
        }
        /*** Fixing rotation ***/
        // Am I a leaf?
        if(leaf == 1) {
            return;
        }
        F = pos;
        // Right rotation
        if(rRot == 1) {
            // I have a Left son
            S = tpos[F][0];
            tpos[F][0] = tpos[S][1];
            tpos[S][1] = F;
            tpos[S][2] = tpos[F][2];
            tpos[F][2] = S;
        }
        // Left rotation
        else    {
            // I have a Right son
            S = tpos[F][1];
            tpos[F][1] = tpos[S][0];
            tpos[S][0] = F;
            tpos[S][2] = tpos[F][2];
            tpos[F][2] = S;
        }
        // Check if it is a root
        if(tpos[S][2] == F) {
            root = S;
            tpos[S][2] = S;
        }
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::fixUp(int pos)    {
    // Fix up by priority
    int F, S = pos;
    bool  lRot, rRot;
    while(1)    {
        // Am I the root?
        if(pos == root)
            return;
        // Am I a Left son? Then, Right rotation
        lRot = rRot = 0;
        F = tpos[S][2];
        tree[S].second.compare( tree[F].second ) < 0 ? rRot=1 : lRot=1;

        /*** Fixing rotation ***/
        // Right rotation
        if(rRot == 1) {
            // I am a Left son
            // Have I more priority?
            if(tree[S].first <= tree[F].first)
                return;
            tpos[F][0] = tpos[S][1];
            tpos[S][1] = F;
            tpos[S][2] = tpos[F][2];
            tpos[F][2] = S;
        }
        // Left rotation
        else    {
            // I am a Right son
            // Have I more priority?
            if(tree[S].first < tree[F].first)
                return;
            tpos[F][1] = tpos[S][0];
            tpos[S][0] = F;
            tpos[S][2] = tpos[F][2];
            tpos[F][2] = S;
        }
        // I am the root
        if(tpos[S][2] == F) {
            root = S;
            tpos[S][2] = S;
        }
    }
}

template <class TPriority, class TKey>
pair<TPriority, TKey> UpdatableHeap<TPriority, TKey>::top()    {
    if(tree_size > 0)
        return tree[root];
    else
        return make_pair(-1,string("-1"));
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::pop()    {
    // Fix down by priority
    if(tree_size > 0)   {
        deleteDown(root);
        tree_size--;
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::insertOrUpdate(const TPriority &p, const TKey &k)   {
    // Void tree
    if(tree_size == 0)  {
        tree.push_back(make_pair(p,k));
        vector<int> info;
        info.push_back(-1); info.push_back(-1); info.push_back(0);
        tpos.push_back(info);
        tree_size++;
        root = 0;
        return;
    }
    // Insert as BST by key
    int pos=root;
    while(1)    {
        // We found the same key
        if(tree[pos].second.compare(k) == 0)    {
            if(tree[pos].first > p) {
                tree[pos].first = p;
                fixDown(pos);
                return;
            }
            else    {
                tree[pos].first = p;
                fixUp(pos);
                return;
            }
        }
        if(tree[pos].second.compare(k) > 0) {
            // Left son
            if(tpos[pos][0] == -1)   {
                // Free space to new node
                tree.push_back(make_pair(p,k));
                tpos[pos][0] = (int)tree.size()-1;
                vector<int> info;
                info.push_back(-1); info.push_back(-1); info.push_back(pos);
                tpos.push_back(info);
                tree_size++;
                pos = tpos[pos][0];
                break;
            }
            else
                // Keep searching
                pos = tpos[pos][0];
        }
        else    {
            // Right son
            if(tpos[pos][1] == -1)   {
                // Free space to new node
                tree.push_back(make_pair(p,k));
                tpos[pos][1] = (int)tree.size()-1;
                vector<int> info;
                info.push_back(-1); info.push_back(-1); info.push_back(pos);
                tpos.push_back(info);
                tree_size++;
                pos = tpos[pos][1];
                break;
            }
            else
                // Keep searching
                pos = tpos[pos][1];
        }
    }
    // Fix up by priority
    fixUp(pos);
}

template <class TPriority, class TKey>
bool UpdatableHeap<TPriority, TKey>::isInserted(const TKey &k)  {
    // Binary search in the BST by key
    int pos=root;
    int vsize = (int)tree.size();
    while(1)    {
        // We found the key
        if(tree[pos].second.compare(k) == 0)
            return true;
        // Keep searching
        if(tree[pos].second.compare(k) > 0) {
            if(tpos[pos][0] == -1)
                return false;
            else
                pos = tpos[pos][0];
        }
        else    {
            if(tpos[pos][1] == -1)
                return false;
            else
                pos = tpos[pos][1];
        }
    }
}

template <class TPriority, class TKey>
void UpdatableHeap<TPriority, TKey>::erase(const TKey &k)    {
    // Binary search in the BST by key
    int pos=root;
    while(1)    {
        // Proceed to delete node by fix down
        if(tree[pos].second.compare(k) == 0)    {
            deleteDown(pos);
            tree_size--;
            return;
        }
        // Keep searching
        if(tree[pos].second.compare(k) > 0) {
            if(tpos[pos][0] == -1)
                return;
            else
                pos = tpos[pos][0];
        }
        else    {
            if(tpos[pos][1] == -1)
                return;
            else
                pos = tpos[pos][1];
        }
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
