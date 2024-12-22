/**
 * Author: Sushil Raaja
 * Date: 2009-10-30
 * License: CC0
 * Source: Discord
 * Description: Wavelet Tree
 * Status: Stress-tested
 */
struct wavelet_tree{
    struct node{
        node *l = nullptr, *r = nullptr;
        vector<int> b;
    };
    node* root;
    int n;
    wavelet_tree() {}
    node* build(vector<int> &a, vector<int> &inds, int lx, int rx) {
        if(lx > rx) return nullptr;
        int mid = (lx+rx) >> 1;
        vector<int> b(sz(inds)+1);
        vector<int> lind,rind;
        int ptr = 1;
        trav(i,inds){
            int x = a[i];
            b[ptr] = b[ptr-1]+(x <= mid);
            ptr++;
            if(x <= mid){
                lind.pb(i);
            }
            else{
                rind.pb(i);
            }
        }
        node* curr = new node();
        curr->b = b;
        if(lx != rx){
            curr->l = build(a,lind,lx,mid);
        }
        curr->r = build(a,rind,mid+1,rx);
        return curr;
    }
    void build(vector<int> &a, int n_){
        n = n_;
        vector<int> inds(sz(a));
        iota(all(inds),0);
        root = build(a,inds,0,n);
    }
    int kth(node* u, int l, int r, int k, int lx, int rx){
        if(lx == rx) return lx;
        int mid = (lx+rx) >> 1;
        auto &b = u->b;
        int cl = b[r]-b[l-1];

        if (k <= cl) return kth(u->l,b[l-1]+1,b[r],k,lx,mid);
        else return kth(u->r,l-b[l-1],r-b[r],k-cl,mid+1,rx);
    }
    int kth(int l, int r, int k) { return kth(root,l+1,r+1,k,0,n); }
    int get_cnt(node* u, int l, int r, int vl, int vr, int lx, int rx){
        if(!u) return 0;
        if(lx > vr or rx < vl) return 0;
        if(lx >= vl and rx <= vr) return r-l+1;

        int mid = (lx+rx) >> 1;
        auto &b = u->b;
        return get_cnt(u->l,b[l-1]+1,b[r],vl,vr,lx,mid)+get_cnt(u->r,l-b[l-1],r-b[r],vl,vr,mid+1,rx);
    }
    int get_cnt(int l, int r, int vl, int vr){
        return get_cnt(root,l+1,r+1,vl,vr,0,n);
    }
};