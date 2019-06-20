#include <iostream>
#include <mutex>

namespace so {
  class CalcTest {
  
  public:
   struct source {
     int a;
     int b;
   };

   struct result {
     std::shared_ptr<int> add;
     std::shared_ptr<int> mux;
   };

   CalcTest();

   ~CalcTest();

   void SetSource(source& src);
   void GetSource(source& src);
   std::shared_ptr<CalcTest::result> Calc();

  private:
   source src_;
   std::mutex mtx_;
  };
} // namespace so