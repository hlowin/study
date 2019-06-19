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

  if (argc != 3) {
    std::cout << "Input parameters 2 number." << std::endl;
    return -1;
  }

  std::unique_ptr<so::CalcTest> ct_process = std::make_unique<so::CalcTest>();

  so::CalcTest::source ct_src;

  so::CalcTest::result ct_rst;

  ct_src.a = atoi(argv[1]);
  ct_src.b = atoi(argv[2]);

  ct_process->SetSource(ct_src);

  ct_rst = ct_process->Calc();

  return 0;
}