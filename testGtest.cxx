#include <gtest/gtest.h>

#include "PieceGtest.h"

/**
 * Programme principal
 */
int
main( int argc, char **argv )
{
    /* run google tests */
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}