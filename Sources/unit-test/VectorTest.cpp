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
   v1 = rumia::Vector2{};
   v2 = rumia::Vector3{};
   v3 = rumia::Vector4{};
}

void VectorTest::TearDown()
{
   // Empty
}

TEST_F(VectorTest, Initialize)
{
   /* Vector2 struct test **/
   EXPECT_EQ(v1.xx, 0.0f);
   EXPECT_EQ(v1.yy, 0.0f);

   v1 = rumia::Vector2{0.5f};
   EXPECT_EQ(v1.xx, 0.5f);
   EXPECT_EQ(v1.yy, 0.5f);

   v1 = rumia::Vector2{ 0.3f, 0.7f };
   EXPECT_EQ(v1.xx, 0.3f);
   EXPECT_EQ(v1.yy, 0.7f);

   v1 = rumia::Vector2::Right;
   EXPECT_EQ(v1.xx, 1.0f);
   EXPECT_EQ(v1.yy, 0.0f);

   /* Vector3 struct test **/
   EXPECT_EQ(v2.xx, 0.0f);
   EXPECT_EQ(v2.yy, 0.0f);
   EXPECT_EQ(v2.zz, 0.0f);

   v2 = rumia::Vector3{ 0.5f };
   EXPECT_EQ(v2.xx, 0.5f);
   EXPECT_EQ(v2.yy, 0.5f);
   EXPECT_EQ(v2.zz, 0.5f);

   v2 = rumia::Vector3{ 0.1f, 0.2f, 0.3f };
   EXPECT_EQ(v2.xx, 0.1f);
   EXPECT_EQ(v2.yy, 0.2f);
   EXPECT_EQ(v2.zz, 0.3f);

   v2 = rumia::Vector3::Right;
   EXPECT_EQ(v2.xx, 1.0f);
   EXPECT_EQ(v2.yy, 0.0f);
   EXPECT_EQ(v2.zz, 0.0f);

   /* Vector4 struct test **/
   EXPECT_EQ(v3.xx, 0.0f);
   EXPECT_EQ(v3.yy, 0.0f);
   EXPECT_EQ(v3.zz, 0.0f);
   EXPECT_EQ(v3.ww, 0.0f);

   v3 = rumia::Vector4{ 0.5f };
   EXPECT_EQ(v3.xx, 0.5f);
   EXPECT_EQ(v3.yy, 0.5f);
   EXPECT_EQ(v3.zz, 0.5f);
   EXPECT_EQ(v3.ww, 0.5f);

   v3 = rumia::Vector4{ 0.1f, 0.2f, 0.3f };
   EXPECT_EQ(v3.xx, 0.1f);
   EXPECT_EQ(v3.yy, 0.2f);
   EXPECT_EQ(v3.zz, 0.3f);
   EXPECT_EQ(v3.ww, 0.0f);

   v3 = rumia::Vector4{ 0.1f, 0.2f, 0.3f, 0.4f };
   EXPECT_EQ(v3.xx, 0.1f);
   EXPECT_EQ(v3.yy, 0.2f);
   EXPECT_EQ(v3.zz, 0.3f);
   EXPECT_EQ(v3.ww, 0.4f);

   v2 = rumia::Vector3::Right;
   v3 = rumia::Vector4{ v2 };
   EXPECT_EQ(v3.xx, 1.0f);
   EXPECT_EQ(v3.yy, 0.0f);
   EXPECT_EQ(v3.zz, 0.0f);
   EXPECT_EQ(v3.ww, 0.0f);

   v3 = rumia::Vector4{ v2, 1.0f };
   EXPECT_EQ(v3.xx, 1.0f);
   EXPECT_EQ(v3.yy, 0.0f);
   EXPECT_EQ(v3.zz, 0.0f);
   EXPECT_EQ(v3.ww, 1.0f);

   v3 = rumia::Vector4::Right;
   EXPECT_EQ(v3.xx, 1.0f);
   EXPECT_EQ(v3.yy, 0.0f);
   EXPECT_EQ(v3.zz, 0.0f);
   EXPECT_EQ(v3.ww, 0.0f);
}