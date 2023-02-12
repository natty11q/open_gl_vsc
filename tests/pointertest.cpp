#include <iostream>

int main(int argc, char* argv[])
{
    int num = 2;
    int* ptr_num = &num;

    std::cout<< "number : " << num << "\n" << "pointer : " << ptr_num << "\n *ptr : " << *ptr_num << std::endl;

    *ptr_num = *ptr_num + 1;

    std::cout<< "number : " << num << "\n" << "pointer : " << ptr_num << "\n *ptr : " << *ptr_num << std::endl;

    return 0;
}