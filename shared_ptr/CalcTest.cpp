#include "CalcTest.h"

namespace so{
  void CalcTest::SetSource(source& src) {
    mtx_.lock();

    src_ = src;

    mtx_.unlock();
  }

  void CalcTest::GetSource(source* src) {
    mtx_.lock();

    src = &src_;

    mtx_.unlock();
  }

  struct result CalcTest::Calc() {
    
    source src;
    GetSource(&src);

    result rst;

    rst.add = std::make_shared<unsigned int>();
    rst.mux = std::make_shared<unsigned int>();

    *rst.add = src.a + src.b;
    *rst.mux = src.a * src.b;

    return rst;
  }
} // namespace so