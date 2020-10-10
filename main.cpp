#include "Console.h"
#include "Tree.h"
#include "Test.h"
#include "Menu.h"

#define TEST

#ifdef TEST
int main() {
    Console::setSystem(SYSTEMS::LINUX);
    Console::setLogging();

    int n = 1000;

    Console::debug("START ORD TEST");

    test_ord(n);

    Console::debug("END ORD TEST");

    Console::debug("START RAND TEST");

    test_rand(n);

    Console::debug("END RAND TEST");

    return 0;
}
#else

int main() {
    Console::setSystem(SYSTEMS::LINUX);
    Console::setLogging();
    Console::setDebug(false);

    Tree<> tree;
    tree.insert(5,2);
    tree.insert(3,2);
    tree.insert(2,2);
    tree.insert(4,2);
    tree.insert(7,2);
    tree.insert(6,2);
    Menu<>::startMenu(tree);

    return 0;
}

#endif
