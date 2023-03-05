#include "main.h"

template <class Type>
bool container_comparison(std::list<Type> &std_list, s21::list<Type> &s21_list) {
  if (std_list.size() != s21_list.size())
    return false;
  auto it_std_list = std_list.begin();
  auto it_s21_list = s21_list.begin();
  while (it_s21_list != s21_list.end()) {
    auto value = *it_s21_list - *it_std_list;
    if ((value > 1e-7) || (value < -1e-7)) {
      return false;
    }
    it_s21_list++;
    it_std_list++;
  }
  return true;
}

TEST(List, st_cost) {
  s21::list<double> s21_list;
  std::list<double> std_list;
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(*std_list.end(), *s21_list.end());
}

TEST(List, size) {
  s21::list<double> s21_list(35);
  std::list<double> std_list(35);
  ASSERT_EQ(std_list.size(), s21_list.size());
  EXPECT_TRUE(container_comparison(std_list, s21_list));
}

TEST(List, initializer_list) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(container_comparison(std_list, s21_list));
}

TEST(List, copy) {
  s21::list<double> s21_first = {3.4, 2.5, 3.4, 2.423455};
  std::list<double> std_first = {3.4, 2.5, 3.4, 2.423455};
  s21::list<double> s21_second = s21_first;
  std::list<double> std_second = std_first;
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(List, move) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double> s21_second = std::move(s21_first);
  std::list<double> std_second = std::move(std_first);
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(List, copy2) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double> s21_second;
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_second;
  s21_second = s21_first;
  std_second = std_first;
  EXPECT_TRUE(container_comparison(std_second, s21_second));
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, move2) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double> s21_second;
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_second;
  s21_second = std::move(s21_first);
  std_second = std::move(std_first);
  EXPECT_TRUE(container_comparison(std_second, s21_second));
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, front) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_NEAR(s21_first.front(), std_first.front(), 1e-7);
}

TEST(List, back) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(s21_first.back(), std_first.back());
}

TEST(List, begin) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(*s21_first.begin(), *std_first.begin());
}

TEST(List, end) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(*s21_first.end(), *std_first.end());
}

TEST(List, empty) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double> s21_second;
  std::list<double> std_second;
  EXPECT_TRUE(s21_first.empty() == std_first.empty());
  EXPECT_TRUE(s21_second.empty() == std_second.empty());
}

TEST(List, size2) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  EXPECT_TRUE(s21_first.size() == std_first.size());
}

TEST(List, clear) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, insert) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  auto it_std_list = std_first.begin();
  auto it_s21_list = s21_first.begin();
  it_s21_list = s21_first.insert(it_s21_list, 345.345634);
  it_std_list = std_first.insert(it_std_list, 345.345634);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  ++it_std_list;
  ++it_std_list;
  ++it_s21_list;
  ++it_s21_list;
  s21_first.insert(it_s21_list, 4325.3456);
  std_first.insert(it_std_list, 4325.3456);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, earse) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  auto it_std_list = std_first.begin();
  auto it_s21_list = s21_first.begin();
  std_first.erase(it_std_list);
  s21_first.erase(it_s21_list);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  it_std_list = std_first.begin();
  it_s21_list = s21_first.begin();
  --it_std_list;
  --it_std_list;
  it_s21_list--;
  it_s21_list--;
  std_first.erase(it_std_list);
  s21_first.erase(it_s21_list);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, push_back) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21_first.push_back(534.532);
  s21_first.push_back(0.432456);
  std_first.push_back(534.532);
  std_first.push_back(0.432456);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, pop_back) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21_first.pop_back();
  s21_first.pop_back();
  std_first.pop_back();
  std_first.pop_back();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, push_front) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21_first.push_front(534.532);
  s21_first.push_front(0.432456);
  std_first.push_front(534.532);
  std_first.push_front(0.432456);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, pop_front) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21_first.pop_front();
  s21_first.pop_front();
  std_first.pop_front();
  std_first.pop_front();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, swap) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double> s21_second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  s21_first.swap(s21_second);
  std_first.swap(std_second);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(List, reverce) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21_first.reverse();
  std_first.reverse();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, unique) {
  s21::list<double> s21_first = {1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
                                 5, 6, 6, 6, 7, 7, 8, 8, 8, 9};
  std::list<double> std_first = {1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
                                 5, 6, 6, 6, 7, 7, 8, 8, 8, 9};
  s21_first.unique();
  std_first.unique();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, sort) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21_first.sort();
  std_first.sort();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, merge) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21::list<double> s21_second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  s21_first.merge(s21_second);
  std_first.merge(std_second);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(List, splice) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21::list<double> s21_second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  auto it_std_list = std_first.begin();
  auto it_s21_list = s21_first.begin();
  it_std_list++;
  it_std_list++;
  ++it_s21_list;
  ++it_s21_list;
  s21_first.splice(it_s21_list, s21_second);
  std_first.splice(it_std_list, std_second);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(List, splice2) {
  s21::list<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  s21::list<double> s21_second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  auto it_std_list = std_first.begin();
  auto it_s21_list = s21_first.begin();
  s21_first.splice(it_s21_list, s21_second);
  std_first.splice(it_std_list, std_second);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(List, max_size) {
  s21::list<double> s21_first;
  std::list<double> std_first;
  ASSERT_EQ(s21_first.max_size(), std_first.max_size());
}

TEST(List, emplace) {
  s21::list<double> s21_first = {2, 3, 4, 5};
  std::list<double> std_first = {2, 3, 4, 5};
  std_first.emplace(std_first.begin(), 1);
  s21_first.emplace(s21_first.begin(), 1);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, emplace_back) {
  s21::list<double> s21_first = {2, 3, 4, 5};
  std::list<double> std_first = {2, 3, 4, 5};
  std_first.emplace_back(543.2345);
  s21_first.emplace_back(543.2345);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, emplace_front) {
  s21::list<double> s21_first = {2, 3, 4, 5};
  std::list<double> std_first = {2, 3, 4, 5};
  std_first.emplace_front(2.345);
  s21_first.emplace_front(2.345);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(List, list_iterator) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::iterator it = s21_first.begin();
  s21::list<double>::iterator it_second = std::move(it);
  EXPECT_TRUE(it_second == s21_first.begin());
}

TEST(List, list_iterator2) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::iterator it = s21_first.begin();
  s21::list<double>::iterator it_second = std::move(it);
  EXPECT_TRUE(it_second == s21_first.begin());
}

TEST(List, list_iterator_const) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::const_iterator first_it = s21_first.begin();
  s21::list<double>::const_iterator second_it = first_it;
  EXPECT_TRUE(second_it == s21_first.begin());
}

TEST(List, list_iterator_const2) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::const_iterator first_it = s21_first.begin();
  s21::list<double>::const_iterator second_it = std::move(first_it);
  first_it = second_it;
  EXPECT_TRUE(second_it == s21_first.begin());
}

TEST(List, list_iterator_const3) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::const_iterator first_it = s21_first.begin();
  s21::list<double>::const_iterator second_it = s21_first.end();
  second_it = std::move(first_it);
  EXPECT_TRUE(second_it == s21_first.begin());
}

TEST(List, list_iterator_const4) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::const_iterator first_it = s21_first.begin();
  s21::list<double>::const_iterator second_it = s21_first.begin();
  first_it++;
  second_it++;
  ++first_it;
  ++second_it;
  EXPECT_FALSE(first_it != second_it);
}

TEST(List, list_iterator_const5) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::const_iterator first_it = s21_first.end();
  s21::list<double>::const_iterator second_it = s21_first.end();
  --first_it;
  --second_it;
  first_it--;
  second_it--;
  EXPECT_TRUE(*first_it == *second_it);
}

TEST(List, list_iterator_3) {
  s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::list<double>::iterator first_it = s21_first.begin();
  s21::list<double>::iterator second_it = s21_first.begin();
  first_it++;
  second_it++;
  EXPECT_FALSE(first_it != second_it);
  EXPECT_TRUE(first_it == second_it);
}

TEST(List, list_iterator_4) {
  const s21::list<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  auto first_it = s21_first.begin();
  auto second_it = s21_first.begin();
  first_it++;
  second_it++;
  EXPECT_FALSE(first_it != second_it);
  EXPECT_TRUE(first_it == second_it);
}
