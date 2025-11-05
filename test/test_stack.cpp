// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(stack, empty_is_empty)
{
	TStack<int> st;
	EXPECT_TRUE(st.IsEmpty());
}

TEST(stack, can_push)
{
	TStack<int> st;
	st.push(1);
	EXPECT_EQ(1, st.top());
}

TEST(stack, can_pop)
{
	TStack<int> st;
	st.push(1);
	st.push(2);
	st.pop();
	EXPECT_EQ(1, st.top());
}

TEST(stack, cant_pop_empty)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.pop());
}

