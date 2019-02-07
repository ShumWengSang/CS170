#include <iostream>
#include <cstdlib>
#include <cstring>

void test1()
{
  new char[123];
}

void test2()
{
  char *p = new char[123];
  delete p;
}

void test3()
{
  char *p = new char;
  delete [] p;
}

void test4()
{
	char *p = (char *)malloc(123);
	delete p;
}

void test5()
{
	char *p = new char;
	free(p);
}

void test6()
{
	char *p = new char[5];
	std::strcpy(p, "ksdfd");
	delete [] p;
}

void test7()
{
	char a[10];
	std::cout << a << std::endl;
}

int main(int argc, char **argv)
{
	unsigned test = 1;
	if (argc > 1)
		test = std::atoi(argv[1]);

  void (*tests[])() = {test1, // leak
                       test2, // new[]/delete
                       test3, // new/delete[]
                       test4, // malloc/delete
                       test5, // new/free
                       test6, // buffer overflow
                       test7, // uninitialized read
                      };

	unsigned size = sizeof(tests) / sizeof(*tests);
	if (test > size)
		test = 1;

	if (test == 0)
	{
		for (unsigned i = 0; i < size; i++)
			tests[i]();
	}
	else
		tests[test - 1]();

  return 0;
}