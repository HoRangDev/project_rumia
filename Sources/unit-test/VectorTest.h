#pragma once
#include "gtest/gtest.h"
#include "Math/Vector2.hpp"

class VectorTest : public testing::Test
{
public:
   VectorTest();
   ~VectorTest();

   virtual void SetUp();
   virtual void TearDown();

public:
   rumia::Vector2 v1;
};