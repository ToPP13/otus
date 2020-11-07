// Example program
#include <iostream>
#include <string>

template<typename T>
void tfunc1(T param)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;    
}
template<typename T>
void tfunc2(T & param)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;    
}
template<typename T>
void tfunc3(T * param)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;    
}
template<typename T>
void tfunc4(T && param)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;    
}

int main()
{
    // int a = 1;
    // const int b = 1;
    // const int & c = b;
    // tfunc1(a);
    // tfunc1(b);
    // tfunc1(c);
    
    
    int i = 10;
    const int ci = 15;
    const int &cir = ci;
    int * pi = &i;
    const int * cpi = &i;
    
    // by value
    tfunc1(i);  // 1.1. param type ? int
    tfunc1(ci); // 1.2. param type ? int
    tfunc1(cir); // 1.3. param type ? int
    tfunc1(42); // 1.4. param type ? int
    tfunc1(pi); // 1.5. param type ? int*
    tfunc1(cpi); // 1.6. param type ?  const int*
    // initializer_list
    // tfunc1({1}); // 1.7. param type ?  couldn't deduce template parameter 'T'
    // tfunc1({1, 2, 3}); // 1.8. param type ?  couldn't deduce template parameter 'T'
    
    // reference
    tfunc2(i); // 2.1. param type ? int
    tfunc2(ci); // 2.2. param type ? const int
    tfunc2(cir); // 2.3. param type ? const int
    // tfunc2(42); // 2.4. param type ? invalid initialization of non-const reference of type 'int&' from an rvalue of type 'int'
    tfunc2(pi); // 2.5. param type ? int*
    tfunc2(cpi); // 2.6. param type ?const int*
    
    // pointer
    // tfunc3(i); // 3.1. param type ? mismatched types 'T*' and 'int'
    // tfunc3(ci); // 3.2. param type ? mismatched types 'T*' and 'int'
    // tfunc3(cir); // 3.3. param type ? mismatched types 'T*' and 'int'
    // tfunc3(42); // 3.4. param type ? mismatched types 'T*' and 'int'
    tfunc3(pi); // 3.5. param type ?
    tfunc3(cpi); // 3.6. param type ?
    
    // rvalue reference
    tfunc4(i); // 4.1. param type? int&
    tfunc4(ci); // 4.2. param type ? const int&
    tfunc4(cir); // 4.3. param type ? const int&
    tfunc4(42); // 4.4. param type ? int 
    tfunc4(pi); // 4.5. param type ? int*&
    tfunc4(cpi); // 4.6. param type ? const int*&
}

