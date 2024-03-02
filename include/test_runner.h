#pragma once

#include <stdexcept>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <sstream>

namespace TestRunnerPrivate {
  template <
    typename K,
    typename V,
    template <typename, typename> class Map
  >
  std::wostream& PrintMap(std::wostream& os, const Map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
      if (!first) {
        os << ", ";
      }
      first = false;
      os << kv.first << ": " << kv.second;
    }
    return os << "}";
  }
}


template <class T>
std::wostream& operator << (std::wostream& os, const std::vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
std::wostream& operator << (std::wostream& os, const std::set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
std::wostream& operator << (std::wostream& os, const std::map<K, V>& m) {
  return TestRunnerPrivate::PrintMap(os, m);
}

template <class K, class V>
std::wostream& operator << (std::wostream& os, const std::unordered_map<K, V>& m) {
  return TestRunnerPrivate::PrintMap(os, m);
}

template <class T, class U>
std::wostream& operator << (std::wostream& os, const std::pair<T, U>& p) {
  os << '(' << p.first << ", " << p.second << ')';
  return os;
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::wstring& hint = {}) {
  if (!(t == u)) {
    std::wostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    std::string s{os.str().begin(), os.str().end()};
    throw std::runtime_error(s);
  }
}

inline void Assert(bool b, const std::wstring& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const std::wstring& test_name) {
    try {
      func();
      std::wcerr << test_name << " OK" << std::endl;
    } catch (std::exception& e) {
      ++fail_count;
      std::wcerr << test_name << " fail: " << e.what() << std::endl;
    } catch (...) {
      ++fail_count;
      std::wcerr << "Unknown exception caught" << std::endl;
    }
  }

  ~TestRunner() {
    std::wcerr.flush();
    if (fail_count > 0) {
      std::wcerr << fail_count << " unit tests failed. Terminate" << std::endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};



#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif

#define ASSERT_EQUAL(x, y) {                          \
  std::wostringstream __assert_equal_private_os;       \
  __assert_equal_private_os                           \
    << #x << " != " << #y << ", "                     \
    << FILE_NAME << ":" << __LINE__;                  \
  AssertEqual(x, y, __assert_equal_private_os.str()); \
}

#define ASSERT(x) {                           \
  std::wostringstream __assert_private_os;     \
  __assert_private_os << #x << " is false, "  \
    << FILE_NAME << ":" << __LINE__;          \
  Assert(x, __assert_private_os.str());       \
}

#define CAT(A, B) A##B
#define WCAT(A) CAT(L, A)

#define RUN_TEST(tr, func) \
  tr.RunTest(func, WCAT(#func))

