//
//  main.cpp
//  test
//
//  Created by Sung9 on 2018. 3. 19..
//  Copyright © 2018년 2018221468. All rights reserved.
//

#include <iostream>

int test(){
    std::cout << "test function\n";
    return 111;
}

int main() {
    // insert code here...
    std::cout << "Hello, World!\n";
    int aaa = test();
    std::cout << aaa << std::endl;
    return 0;
}

