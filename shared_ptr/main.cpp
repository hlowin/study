#include <iostream>
#include <string>

#include "CalcTest.h"

int main(int argc, char* argv[])
{
#if DEBUG_
  argc = 3;
  argv[1] = '5';
  argv[2] = '2';
#endif

  // if (argc != 3) {
  //   std::cout << "Input parameters 2 number." << std::endl;
  //   return -1;
  // }

  std::unique_ptr<so::CalcTest> ct_process = std::make_unique<so::CalcTest>();

  so::CalcTest::source ct_src;

  ct_src.a = atoi(argv[1]);
  ct_src.b = atoi(argv[2]);

  // ct_src.a = 5;
  // ct_src.b = 2;

  ct_process->SetSource(ct_src);

  auto ct_rst = ct_process->Calc();

  std::cout << "Result:" << std::endl;
  std::cout << "add = " << *ct_rst->add << std::endl;
  std::cout << "mux = " << *ct_rst->mux << std::endl;

  return 0;
}