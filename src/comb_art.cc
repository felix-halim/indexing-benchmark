#include <cstdio>
#include <cassert>

#define LARGE_SIZE 4096
#define SMALL_SIZE 64

#include "comb_art.h"
#include "test.h"

inline uintptr_t getLeafValue(Node* node) {
  // The the value stored in the pseudo-leaf
  uintptr_t v = getData((uintptr_t) node);
  return isPointer(v) ? data((Bucket<unsigned>*) v) : getData(v);
}

Comb<unsigned> c;

void init(unsigned *arr, unsigned N) {
  // art_debug = 1;
  c.load(arr, N);
  // for (int i = 0; i < N; i++) {
  //   insert(arr[i]);
  //   if (i % 1000) lower_bound(arr[i]);
  // }
}

void insert(unsigned value) {
  // fprintf(stderr, "insert %u\n", value);
  c.insert(value);
}

void erase(unsigned value) {
  // fprintf(stderr, "erase %u\n", value);
  #ifdef NDEBUG
    c.erase(value);
  #else
    bool ok = c.erase(value);
    if (!ok) fprintf(stderr, "ERASE error %d\n", value);
    assert(ok);
  #endif
}

unsigned lower_bound(unsigned value) {
  unsigned ret = c.lower_bound(value);
  // fprintf(stdout, "%d (%d)\n", ret, value); fflush(stdout);
  return ret;
}

unsigned select(unsigned a, unsigned b) {
  return c.lower_bound(a) + c.lower_bound(b);
}

unsigned count(unsigned a, unsigned b) {
  return 0;
}

void results(Statistics &s) {
  // assert(c.check());
  c.statistics([&](int n_index, long long n_bytes, int n_slack_art, int n_slack_leaves, int n_internal, int n_leaf,
      int n_small, int n_large, int n_chain, int art_n4, int art_n16, int art_n48, int art_n256) {
    s.n_index = n_index;
    s.n_bytes = n_bytes;
    s.n_slack_int = n_slack_art;
    s.n_slack_leaf = n_slack_leaves;
    s.n_internal = n_internal;
    s.n_leaf = n_leaf;
    s.n_small = n_small;
    s.n_large = n_large;
    s.n_chained = n_chain;
    s.art_n4 = art_n4;
    s.art_n16 = art_n16;
    s.art_n48 = art_n48;
    s.art_n256 = art_n256;
  });

  s.bt_int_sz = 0;
  s.bt_leaf_sz = 0;
  s.large_touch = LARGE_TOUCH;
  s.small_touch = SMALL_TOUCH;
}
