#include <cstdio>
#include <thread>

volatile unsigned glob = 0;
static constexpr auto OUTER_LOOP = 999U;
static constexpr auto INNER_LOOP = 999U;

struct S
{
  unsigned a : 4;
  unsigned b : 4;
};

void
inc_a(S &s) {
  for (auto i = 0U; i < OUTER_LOOP; ++i) {
    for (auto j = 0U; j < INNER_LOOP; ++j) {
      ++s.a;
      ++glob;
    }
  }
}

void
inc_b(S &s) {
  for (auto i = 0U; i < OUTER_LOOP; ++i) {
    for (auto j = 0U; j < INNER_LOOP; ++j) {
      ++s.b;
      ++glob;
    }
  }
}


int
main() {
  for (int i = 0; i < 3; ++i) {
    S s{0, 0};
    std::thread t1(inc_a, std::ref(s));
    std::thread t2(inc_b, std::ref(s));
    t1.join();
    t2.join();
    std::printf("%d %d\n", s.a, s.b);
  }
  return 0;
}

