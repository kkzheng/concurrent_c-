#include <iostream>
#include <random>

#include "../include/ThreadPool.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);

void simulate_hard_computation() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

void multiply(const int a, const int b) {
  simulate_hard_computation();
  int res = a*b;
  std::cout << a << " * " << b << " = " << res << std::endl;
}

int main() {
  ThreadPool pool(5);
  pool.init();
  for(int i = 1; i < 3; i++) {
    for(int j = 1; j < 10; j++) {
      pool.submit(multiply, i, j);
    }
  }
  pool.shutdown();
  return 0;
}
