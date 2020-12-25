#import <XCTest/XCTest.h>
#import "Artefact.h"

using namespace Dungeon;

@interface test : XCTestCase

@end

@implementation test

- (void)testConstructor {
    Artefact artefact;
    XCTAssertEqual(ARTEFACT, artefact.GetName());
}

- (void)testGetModificators {
    Artefact artefact;
    characteristic health = {HEALTH, 0, 0};
    std::vector <characteristic> mod;
    mod = artefact.GetModificators();
    XCTAssertEqual(health.current, mod[0].current);
    XCTAssertEqual(health.max, mod[0].max);
    XCTAssertEqual(health.type, mod[0].type);
}

- (void)testSetModificators {
    Artefact artefact;
    characteristic health = {HEALTH, 1, 1};
    XCTAssertNoThrow(artefact.SetModificator(health));
    std::vector <characteristic> mod;
    mod = artefact.GetModificators();
    XCTAssertEqual(health.current, mod[1].current);
    XCTAssertEqual(health.max, mod[1].max);
    XCTAssertEqual(health.type, mod[1].type);
}

- (void)testClearModificators {
    Artefact artefact;
    XCTAssertNoThrow(artefact.ClearModificators());
}


- (void)testDeleteModificators {
    Artefact artefact;
    XCTAssertNoThrow(artefact.DeleteModificator(0));
    characteristic health = {HEALTH, 1, 1};
    artefact.SetModificator(health);
    XCTAssertThrows(artefact.DeleteModificator(1));
}

@end
