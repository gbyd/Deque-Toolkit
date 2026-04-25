/**
 * @file main.cpp
 * @author AJ Hopkins
 * @date 2026-04-22
 * @brief Automated stress test driver for the custom deque implementation
 *
 * Runs hundreds of coordinated push/pop and operator[] tests against both
 * the custom deque and std::deque to verify correctness.
 */
 
#include "deque.h"
#include <deque>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
 
// Compare our deque front/back/size/empty against std::deque reference
static int passed = 0;
static int failed = 0;
 
void check(bool condition, const std::string& label) {
  if (condition) {
    passed++;
  } else {
    std::cerr << "FAIL: " << label << std::endl;
    failed++;
  }
}
 
int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
 
  std::cout << "=== Basic functionality tests ===" << std::endl;
 
  // ---- empty deque ----
  {
    deque d;
    check(d.empty(),      "empty() on new deque");
    check(d.size() == 0,  "size() == 0 on new deque");
  }
 
  // ---- push_back / front / back / size ----
  {
  deque d;
  d.push_back(10);
  check(!d.empty(),       "not empty after push_back");
  check(d.size() == 1,    "size == 1 after one push_back");
  check(d.front() == 10,  "front() after one push_back");
  check(d.back()  == 10,  "back()  after one push_back");

  d.push_back(20);
  check(d.size() == 2,    "size == 2 after two push_backs");
  check(d.front() == 10,  "front() unchanged after second push_back");
  check(d.back()  == 20,  "back() == 20 after second push_back");
}

// ---- push_front ----
  {
    deque d;
    d.push_front(5);
    check(d.front() == 5 && d.back() == 5, "push_front single element");
    d.push_front(1);
    check(d.front() == 1, "front() == 1 after push_front");
    check(d.back()  == 5, "back() still 5 after push_front");
  }

// ---- pop_front / pop_back ----
  {
    deque d;
    for (int i = 0; i < 5; i++) d.push_back(i);   // 0 1 2 3 4
    d.pop_front();
    check(d.front() == 1 && d.size() == 4, "pop_front basic");
    d.pop_back();
    check(d.back()  == 3 && d.size() == 3, "pop_back basic");
  }

// ---- operator[] ----
  {
    deque d;
    for (int i = 0; i < 10; i++) d.push_back(i * 10);
    bool ok = true;
    for (int i = 0; i < 10; i++)
      if (d[i] != i * 10) ok = false;
    check(ok, "operator[] sequential access");
  }

std::cout << "\n=== Stress test: push_back + pop_front (queue mode) ===" << std::endl;
{
  deque     custom;
  std::deque<int> ref;

  for (int i = 0; i < 2000; i++) {
    int val = std::rand() % 10000;
    custom.push_back(val);
    ref.push_back(val);
  }
  bool ok = true;
  while (!ref.empty()) {
    if (custom.front() != ref.front() || custom.size() != (int)ref.size()) {
      ok = false;
      break;
    }
    custom.pop_front();
    ref.pop_front();
  }
  check(ok && custom.empty(), "2000-element queue stress test");
}

std::cout << "\n=== Stress test: push_front + pop_back (reverse queue) ===" << std::endl;
{
  deque     custom;
  std::deque<int> ref;

  for (int i = 0; i < 2000; i++) {
    int val = std::rand() % 10000;
    custom.push_front(val);
    ref.push_front(val);
  }
  bool ok = true;
  while (!ref.empty()) {
    if (custom.back() != ref.back() || custom.size() != (int)ref.size()) {
      ok = false;
      break;
    }
    custom.pop_back();
    ref.pop_back();
  }
  check(ok && custom.empty(), "2000-element reverse queue stress test");
}

std::cout << "\n=== Stress test: random mixed pushes/pops ===" << std::endl;
{
  deque     custom;
  std::deque<int> ref;
  bool ok = true;

  for (int i = 0; i < 5000; i++) {
    int op = std::rand() % 4;
    if (op == 0) {
      int v = std::rand() % 1000;
      custom.push_back(v);
      ref.push_back(v);
    } else if (op == 1) {
      int v = std::rand() % 1000;
      custom.push_front(v);
      ref.push_front(v);
    } else if (op == 2) {
      if (!ref.empty()) {
	if (custom.front() != ref.front()) { ok = false; break; }
	custom.pop_front();
	ref.pop_front();
      }
    } else {
      if (!ref.empty()) {
	if (custom.back() != ref.back()) { ok = false; break; }
	custom.pop_back();
	ref.pop_back();
      }
    }
    // Size & empty must match at all times
    if (custom.size() != (int)ref.size() || custom.empty() != ref.empty()) {
      ok = false;
      break;
    }
  }
  check(ok, "5000-op random mixed push/pop stress test");
}

std::cout << "\n=== Stress test: operator[] random access ===" << std::endl;
{
  deque     custom;
  std::deque<int> ref;

  for (int i = 0; i < 500; i++) {
    int v = std::rand() % 9999;
    custom.push_back(v);
    ref.push_back(v);
  }
  bool ok = true;
  for (int i = 0; i < 500; i++) {
    if (custom[i] != ref[i]) { ok = false; break; }
  }
  check(ok, "500-element operator[] random access");
}

std::cout << "\n=== Stress test: blockmap resize (large push_back) ===" << std::endl;
{
  deque     custom;
  std::deque<int> ref;
  for (int i = 0; i < 10000; i++) {
    custom.push_back(i);
    ref.push_back(i);
  }
  bool ok = (custom.size() == (int)ref.size());
  if (ok) {
    ok = (custom.front() == ref.front() && custom.back() == ref.back());
  }
  check(ok, "10000 push_back resize stress test");
}

std::cout << "\n=== Stress test: blockmap resize (large push_front) ===" << std::endl;
{
  deque     custom;
  std::deque<int> ref;
  for (int i = 0; i < 10000; i++) {
    custom.push_front(i);
    ref.push_front(i);
  }
  bool ok = (custom.size() == (int)ref.size());
  if (ok) {
    ok = (custom.front() == ref.front() && custom.back() == ref.back());
  }
  check(ok, "10000 push_front resize stress test");
}

std::cout << "\n==============================" << std::endl;
std::cout << "Passed: " << passed << std::endl;
std::cout << "Failed: " << failed << std::endl;
std::cout << "==============================" << std::endl;

return (failed == 0) ? 0 : 1;
}
