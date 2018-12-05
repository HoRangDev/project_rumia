#include "gtest/gtest.h"
#include "VectorTest.h"

VectorTest::VectorTest()
{
   // Empty
}

VectorTest::~VectorTest()
{
   // Empty
}

void VectorTest::SetUp()
{
   v1 = rumia::Vector2();
}

void VectorTest::TearDown()
{
   // Empty
}

TEST_F(VectorTest, Initialize)
{
   EXPECT_EQ(v1.xx, 0.0f);
   EXPECT_EQ(v1.yy, 0.0f);

   v1 = rumia::Vector2(0.5f);
   EXPECT_EQ(v1.xx, 0.5f);
   EXPECT_EQ(v1.yy, 0.5f);

   v1 = rumia::Vector2(0.3f, 0.7f);
   EXPECT_EQ(v1.xx, 0.3f);
   EXPECT_EQ(v1.yy, 0.7f);
}