/*!*****************************************************************************
\file   fibonacci.cpp
\author Roland Shum
\par    email: roland.shum\@digipen.edu
\par    DigiPen Login: roland.shum 
\par    Course: CS170
\par    Section: A
\par    Lab week 3
\date   01/31/2019

\brief
  This file contains the definition of fibonacci, which prints the fibonnaci
  sequence to console up till max.
  
*******************************************************************************/
#include <iostream> // cout
#include <iomanip>  // width, fixed, precision

/******************************************************************************/
/*!
  \fn void fibonacci(int max)

  \brief 
    Removes the item that is at the top of the stack. Verifies the
  stack is not empty before removing the item. Changes the stack.

  \param max
    The maximum fibonacci sequence to print to.

*/
/******************************************************************************/
void fibonacci(int max)
{
  /* Print table to console with very nice formatting. */
  std::cout << "           Fibonacci        Fibonacci" << std::endl;
  std::cout << " N           number          quotient" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << " 0             0                  N/A" << std::endl;
  std::cout << " 1             1                  N/A" << std::endl;

  int count = max;        /* Use a temporary variable to hold max.      */
  int fib1 = 0, fib2 = 1; /* The first two fibonacci numbers are known. */
  
  /* Start looping from unknown fibonacci until the max. */
  for (int i = 2; i <= count; i++)
  {
    // Find the next fibonacci number. 
    int next = fib1 + fib2; 
    
    // Print the fibonnaci out nicely. 
    std::cout.width(2);
    std::cout << i << std::fixed;
    
    std::cout.width(14);
    std::cout << next << "   ";
    
    // Print the fib quo out. 
    std::cout.precision(16);
    std::cout << (double)next / (double)fib2 << std::right << std::endl;
    
    // Record the last two fib numbers.
    fib1 = fib2;
    fib2 = next;
  }
}