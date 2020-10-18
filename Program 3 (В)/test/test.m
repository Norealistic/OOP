#import <XCTest/XCTest.h>
#import "BigInt_dyn.hpp"

using namespace NS3;

@interface test : XCTestCase

@end

@implementation test

- (void)testDefaultConstructor{
    BigInt bigint;
    XCTAssertEqual(0, int(bigint));
}

- (void)testStringConstructor{
    char c[] = "0000";
    BigInt bigint(c);
    XCTAssertEqual(0, (int)bigint);
    XCTAssertNoThrow(bigint);
    char a[] = "-0002";
    BigInt bigint1(a);
    XCTAssertEqual(-2, (int)bigint1);
    XCTAssertNoThrow(bigint1);
}

-(void)testIntConstructor{
    BigInt bigint(-0);
    XCTAssertEqual(0, (int)bigint);
    XCTAssertNoThrow(bigint);
    BigInt bigint1(-1111);
    XCTAssertEqual(-1111, (int)bigint1);
    XCTAssertNoThrow(bigint1);
}

- (void)testTwosComplimentOperator{
    BigInt bigint(0);
    XCTAssertNoThrow(~bigint);
    XCTAssertEqual(0, int(~bigint));
    BigInt bigint1(22);
    XCTAssertNoThrow(~bigint1);
    XCTAssertEqual(22, int(~bigint1));
    BigInt bigint2(-1);
    XCTAssertNoThrow(~bigint2);
    XCTAssertEqual(-9, int(~bigint2));
}

- (void)testUnaryOperatorMinus{
    BigInt bigint(0);
    XCTAssertNoThrow(-bigint);
    XCTAssertEqual(0, int(~bigint));
    BigInt bigint1(22);
    XCTAssertNoThrow(-bigint1);
    XCTAssertEqual(-22, int(-bigint1));
    BigInt bigint2(-1);
    XCTAssertNoThrow(-bigint2);
    XCTAssertEqual(1, int(-bigint2));
}

- (void)testSumOperator{
    BigInt bigint(0);
    BigInt bigint1(34);
    XCTAssertEqual(-20, int(bigint-20));
    XCTAssertEqual(34, int(bigint+34));
    XCTAssertEqual(0, int(-bigint1+34));
    XCTAssertEqual(34, int(bigint+bigint1));
    XCTAssertEqual(-34, int(bigint-bigint1));
}

- (void)testMultiplicationDevisionOperator{
    BigInt bigint(0);
    BigInt bigint1(-23);
    XCTAssertNoThrow(bigint/10);
    XCTAssertNoThrow(bigint*10);
    XCTAssertThrows(bigint/3);
    XCTAssertThrows(bigint*3);
    XCTAssertEqual(0, int(bigint/10));
    XCTAssertEqual(-2, int(bigint1/10));
    XCTAssertEqual(0, int(bigint*10));
    XCTAssertEqual(-230, int(bigint1*10));
}

@end
