#pragma once
#include "gtest/gtest.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

class VectorTest : public testing::Test
{
public:
   VectorTest();
   ~VectorTest();

   virtual void SetUp();
   virtual void TearDown();

public:
   rumia::Vector2 v1;
   rumia::Vector3 v2;
   rumia::Vector4 v3;
};