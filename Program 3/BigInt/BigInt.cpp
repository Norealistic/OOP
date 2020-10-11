//
//  BigInt.cpp
//  BigInt
//
//  Created by Никита on 11.10.2020.
//  Copyright © 2020 Никита. All rights reserved.
//

#include <iostream>
#include "BigInt.hpp"
#include "BigIntPriv.hpp"

void BigInt::HelloWorld(const char * s)
{
    BigIntPriv *theObj = new BigIntPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void BigIntPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

