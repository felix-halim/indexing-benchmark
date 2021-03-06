#include <cstdio>
#include <cassert>
#include <algorithm>
#include "ctree_eager.h"

#ifdef NOUP
  // #include "test_noup.h"
#else
  // #include "test_lfhv.h"
#endif

using namespace std;
using namespace ctree;

CTree c;

void init(int *arr, int N) {
  for (int i = 0; i < N; i++) {
    c.insert(arr[i]);
  }
  c.optimize();
  // c.debug();
}

void insert(int value) {
  c.insert(value);
}

void erase(int value) {
  bool ok = c.erase(value);
  assert(ok);
}

int lower_bound(int value) {
  auto it = c.lower_bound(value);
  int ret = it.first ? it.second : 0;
  // fprintf(stderr, "%d (%d)\n", ret, value);
  return ret;
}

int select(int a, int b) {
  auto it1 = c.lower_bound(a);
  auto it2 = c.lower_bound(b);
  int ret1 = it1.first ? it1.second : 0;
  int ret2 = it2.first ? it2.second : 0;
  // fprintf(stderr, "%d (%d)\n", ret, value);
  return ret1 + ret2;
}

void results(double insert_time, double query_time, int checksum) {
  printf("%.6lf,%.6lf,%d,", insert_time, query_time, checksum);
  printf("\"%s\",%d,%d,%d,%d,%d,%.6lf,%.6lf,%.6lf\n", "optimized", nLeaves, nCap, nInternals, c.max_depth(), c.slack(), c.t1, c.t2, c.t3);
}
