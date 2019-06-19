#include <iostream>
#include <mutex>

namespace so {
  class CalcTest {
  
  public:
   struct source {
     unsigned int a;
     unsigned int b;
   };

   struct result {
     std::shared_ptr<unsigned int> add;
     std::shared_ptr<unsigned int> mux;
   };

   CalcTest() {}

   ~CalcTest() {}

   void SetSource(source& src);
   void GetSource(source* src);
   result Calc();

  private:
   source src_;
   std::mutex mtx_;
  };
} // namespace so