#include "CalcTest.h"

namespace so{

  CalcTest::CalcTest() {}

  CalcTest::~CalcTest() {}

  void CalcTest::SetSource(source& src) {
    mtx_.lock();

    src_ = src;

    mtx_.unlock();
  }

  void CalcTest::GetSource(source& src) {
    mtx_.lock();

    src = src_;

    mtx_.unlock();
  }

  std::shared_ptr<CalcTest::result> CalcTest::Calc() {
    
    source src;
    GetSource(src);

    std::shared_ptr<CalcTest::result> rst = std::make_shared<CalcTest::result>();

    rst->add = std::make_shared<int>();
    rst->mux = std::make_shared<int>();

    *rst->add = src.a + src.b;
    *rst->mux = src.a * src.b;

    return rst;
  }
} // namespace so