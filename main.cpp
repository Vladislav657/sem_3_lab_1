#include <iostream>
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "stack.h"

using std::cout;

TEST(StackTest, DefaultConstructor) {
    Stack<int> s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.capacity(), 10);
    EXPECT_TRUE(s.empty());
}

// Тест на добавление элементов
TEST(StackTest, Push) {
    Stack<int> s;
    s.push(10);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.check_pop(), 10);
}

// Тест на удаление элементов
TEST(StackTest, Pop) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    EXPECT_EQ(s.pop(), 20);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.pop(), 10);
    EXPECT_EQ(s.size(), 0);
    EXPECT_THROW(s.pop(), std::length_error);
}

// Тест на копирование
TEST(StackTest, CopyConstructor) {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);

    Stack<int> s2 = s1;
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.check_pop(), 20);
    EXPECT_EQ(s2.pop(), 20);
    EXPECT_EQ(s2.pop(), 10);
}

// Тест на перемещение
TEST(StackTest, MoveConstructor) {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);

    Stack<int> s2 = std::move(s1);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.pop(), 20);
    EXPECT_EQ(s2.pop(), 10);
    EXPECT_TRUE(s1.empty());
}

// Тест на инициализатор
TEST(StackTest, InitializerListConstructor) {
    Stack<int> s = {1, 2, 3, 4};
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s.pop(), 4);
    EXPECT_EQ(s.pop(), 3);
}

// Тест на перегруженные операторы <<
TEST(StackTest, PushOperator) {
    Stack<int> s;
    s << 10 << 20;
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.check_pop(), 20);
}

// Тест на перегруженные операторы >>
TEST(StackTest, PopOperator) {
    Stack<int> s;
    s << 10 << 20;
    int value;
    s >> value;
    EXPECT_EQ(value, 20);
    EXPECT_EQ(s.size(), 1);
    s >> value;
    EXPECT_EQ(value, 10);
    EXPECT_TRUE(s.empty());
}

// Тест на проверку пустого стека
TEST(StackTest, Empty) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    s.push(10);
    EXPECT_FALSE(s.empty());
}

// Тест на очистку стека
TEST(StackTest, Clear) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_THROW(s.pop(), std::length_error);
}

// Тест на оператор сравнения ==
TEST(StackTest, EqualityOperator) {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);

    Stack<int> s2;
    s2.push(10);
    s2.push(20);

    EXPECT_TRUE(s1 == s2);

    s2.push(30);
    EXPECT_FALSE(s1 == s2);
}

// Тест на оператор !=
TEST(StackTest, InequalityOperator) {
    Stack<int> s1;
    s1.push(10);

    Stack<int> s2;
    s2.push(20);

    EXPECT_TRUE(s1 != s2);
}

// Тест на проверку верхнего элемента
TEST(StackTest, Top) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.top(30);
    EXPECT_EQ(s.check_pop(), 30);
}

// Тест на swap
TEST(StackTest, Swap) {
    Stack<int> s;
    s.push(10);
    int data = 20;
    s.swap(data);
    EXPECT_EQ(data, 10);
    EXPECT_EQ(s.check_pop(), 20);
}

// Бенчмарк для операции push с добавлением n элементов в стек
static void BM_StackPush(benchmark::State& state) {
    for (auto _ : state) {
        Stack<int> s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push(i);
        }
    }
}
// Регистрируем бенчмарк для разных размеров
BENCHMARK(BM_StackPush)->Range(8, 8 << 10);

// Бенчмарк для операции pop с удалением n элементов из стека
static void BM_StackPop(benchmark::State& state) {
    for (auto _ : state) {
        Stack<int> s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push(i);
        }
        for (int i = 0; i < state.range(0); ++i) {
            s.pop();
        }
    }
}
// Регистрируем бенчмарк для разных размеров
BENCHMARK(BM_StackPop)->Range(8, 8 << 10);

// Бенчмарк для конструктора копирования
static void BM_StackCopyConstructor(benchmark::State& state) {
    Stack<int> s;
    for (int i = 0; i < state.range(0); ++i) {
        s.push(i);
    }
    for (auto _ : state) {
        Stack<int> s_copy(s);
    }
}
// Регистрируем бенчмарк для разных размеров
BENCHMARK(BM_StackCopyConstructor)->Range(8, 8 << 10);

// Бенчмарк для конструктора перемещения
static void BM_StackMoveConstructor(benchmark::State& state) {
    for (auto _ : state) {
        Stack<int> s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push(i);
        }
        Stack<int> s_moved(std::move(s));
    }
}
// Регистрируем бенчмарк для разных размеров
BENCHMARK(BM_StackMoveConstructor)->Range(8, 8 << 10);

// Бенчмарк для конструктора с initializer_list
static void BM_StackInitializerListConstructor(benchmark::State& state) {
    for (auto _ : state) {
        Stack<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    }
}
// Регистрируем бенчмарк
BENCHMARK(BM_StackInitializerListConstructor);

// Бенчмарк для функции clear
static void BM_StackClear(benchmark::State& state) {
    for (auto _ : state) {
        Stack<int> s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push(i);
        }
        s.clear();
    }
}
// Регистрируем бенчмарк для разных размеров
BENCHMARK(BM_StackClear)->Range(8, 8 << 10);

// Бенчмарк для оператора сравнения ==
static void BM_StackEqualityOperator(benchmark::State& state) {
    Stack<int> s1, s2;
    for (int i = 0; i < state.range(0); ++i) {
        s1.push(i);
        s2.push(i);
    }
    for (auto _ : state) {
        bool are_equal = (s1 == s2);
        benchmark::DoNotOptimize(are_equal);
    }
}
// Регистрируем бенчмарк для разных размеров
BENCHMARK(BM_StackEqualityOperator)->Range(8, 8 << 10);

int main() {
    int n = RUN_ALL_TESTS();
    cout << (n == 0 ? "ALL TESTS PASSED" : "SOME TEST FAILED") << std::endl;
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}
