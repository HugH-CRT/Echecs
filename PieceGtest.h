#include <gtest/gtest.h>
#include "Piece.h"

class PieceTest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        rptr = new Roi( true );
    }

    void TearDown() override
    {
        delete rptr;
    }

    Roi *rptr;
};

TEST_F( PieceTest, IsWhite )
{
    EXPECT_EQ( rptr->isWhite(), true );
}
