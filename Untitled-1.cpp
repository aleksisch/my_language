#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

constexpr int MINN = 1;
constexpr int MAXN = 2147483647;
constexpr int MINM = 1;
constexpr int MAXM = 100000;

void Assert(bool b) {
    if (!b) {
        fprintf(stderr, "BAD INPUT\n");
        exit(1);
    }
}


struct Segment {
    Segment *prev, *next;
    bool free;
    int ll, rr, pp;

    Segment(Segment *prev, Segment *next, bool free, int ll, int rr, int pp);

    void remove();
};

int nn, mm, kk, ll, rs[MAXM];
Segment *h[MAXM], *r[MAXM];

/* rs=request status: 0=declined, 1=allocated, 2=removed */

Segment::Segment(Segment *prev, Segment *next, bool free, int ll, int rr, int pp) {
    this->prev = prev;
    this->next = next;
    this->free = free;
    this->ll = ll;
    this->rr = rr;
    this->pp = pp;
    if (prev)
        prev->next = this;
    if (next)
        next->prev = this;
}

void Segment::remove() {
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
}

void swap(int aa, int bb) {
    Segment *t = h[aa];
    h[aa] = h[bb];
    h[bb] = t;
    h[aa]->pp = aa;
    h[bb]->pp = bb;
}

bool better(int aa, int bb) {
    return h[aa]->rr - h[aa]->ll > h[bb]->rr - h[bb]->ll;
}

void heapify(int aa) {
    int qq = aa + 1;
    for (;aa != qq;) {
            qq = aa;
            if (((aa << 1) + 1 < ll) && better((aa << 1) + 1, qq))
                qq = (aa << 1) + 1;
            if (((aa << 1) + 2 < ll) && better((aa << 1) + 2, qq))
                qq = (aa << 1) + 2;
            if (aa == qq)
                return;
            swap(aa, qq);
            aa = qq;
        }
}

void heap_remove() {
    --ll;
    if (ll) {
        swap(0, ll);
        heapify(0);
    }
}

void heap_lift(int aa) {
    while (aa && better(aa, (aa - 1) >> 1)) {
        swap(aa, (aa - 1) >> 1);
        aa = (aa - 1) >> 1;
    }
}

void heap_remove(int aa) {
    swap(aa, ll - 1);
    --ll;
    if (aa >= ll)
        return;
    heap_lift(aa);
    heapify(aa);
}

void heap_add(Segment *a) {
    a->pp = ll;
    h[ll] = a;
    heap_lift(ll++);
}

void allocate(int aa) {
    Assert((1 <= aa) && (aa <= nn));
    Segment *c = h[0];
    if (!ll || (c->rr - c->ll < aa)) // allocation impossible
    {
        rs[kk++] = 0;
        printf("-1\n");
        return;
    }
    rs[kk++] = 1;
    r[kk - 1] = new Segment(c->prev, c, false, c->ll, c->ll + aa, -1);
    printf("%d\n", 1 + c->ll);
    c->ll += aa;
    if (c->ll < c->rr) // decrease the key
        heapify(c->pp);
    else // remove the segment
    {
        c->remove();
        heap_remove();
        delete c;
    }
}

void remove(int aa) {
    --aa;
    Assert((0 <= aa) && (aa < kk) && (rs[aa] != 2));
    rs[kk++] = 2;
    if (!rs[aa])
        return;
    rs[aa] = 2;
    Segment *c = r[aa], *sp = c->prev, *sn = c->next;
    bool bp = sp && sp->free;
    bool bn = sn && sn->free;
    if (!bp && !bn) // create aa new segment
    {
        c->free = true;
        heap_add(c);
        return;
    }
    if (!bp) // enlarge the next segment
    {
        sn->ll = c->ll;
        heap_lift(sn->pp);
        c->remove();
        delete c;
        return;
    }
    if (!bn) // enlarge the previous segment
    {
        sp->rr = c->rr;
        heap_lift(sp->pp);
        c->remove();
        delete c;
        return;
    }
    sp->rr = sn->rr;
    heap_lift(sp->pp);
    c->remove();
    delete c;
    heap_remove(sn->pp);
    sn->remove();
    delete sn;
}

int main() {

    Assert((scanf("%d%d", &nn, &mm) == 2) && (MINN <= nn) && (nn <= MAXN) && (MINM
    <= mm) && (mm <= MAXM));
    ll = 1;
    h[0] = new Segment(0, 0, true, 0, nn, 0);
    for (int i = 0; i < mm; ++i) {
            int tt;
            Assert(scanf("%d", &tt) == 1);

            if (tt > 0)
                allocate(tt);
            else
                remove(-tt);
        }
    return 0;
}