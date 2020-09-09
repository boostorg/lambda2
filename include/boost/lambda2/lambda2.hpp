#ifndef BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED
#define BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <functional>
#include <type_traits>
#include <utility>

namespace boost
{
namespace lambda2
{

namespace detail
{

template<class T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<class T, class T2 = remove_cvref_t<T>> using is_lambda_expression =
    std::integral_constant<bool, std::is_placeholder<T2>::value || std::is_bind_expression<T2>::value>;

template<class A> using enable_unary_lambda =
    std::enable_if_t<is_lambda_expression<A>::value>;

template<class A, class B> using enable_binary_lambda =
    std::enable_if_t<is_lambda_expression<A>::value || is_lambda_expression<B>::value>;

} // namespace detail

#define BOOST_LAMBDA2_UNARY_LAMBDA(op, fn) \
    template<class A, class = detail::enable_unary_lambda<A>> \
    auto operator op( A&& a ) \
    { \
        return std::bind( std::fn<>(), std::forward<A>(a) ); \
    }

#define BOOST_LAMBDA2_BINARY_LAMBDA(op, fn) \
    template<class A, class B, class = detail::enable_binary_lambda<A, B>> \
    auto operator op( A&& a, B&& b ) \
    { \
        return std::bind( std::fn<>(), std::forward<A>(a), std::forward<B>(b) ); \
    }

BOOST_LAMBDA2_BINARY_LAMBDA(+, plus)
BOOST_LAMBDA2_BINARY_LAMBDA(-, minus)
BOOST_LAMBDA2_BINARY_LAMBDA(*, multiplies)
BOOST_LAMBDA2_BINARY_LAMBDA(/, divides)
BOOST_LAMBDA2_BINARY_LAMBDA(%, modulus)
BOOST_LAMBDA2_UNARY_LAMBDA(-, negate)

BOOST_LAMBDA2_BINARY_LAMBDA(==, equal_to)
BOOST_LAMBDA2_BINARY_LAMBDA(!=, not_equal_to)
BOOST_LAMBDA2_BINARY_LAMBDA(>, greater)
BOOST_LAMBDA2_BINARY_LAMBDA(<, less)
BOOST_LAMBDA2_BINARY_LAMBDA(>=, greater_equal)
BOOST_LAMBDA2_BINARY_LAMBDA(<=, less_equal)

BOOST_LAMBDA2_BINARY_LAMBDA(&&, logical_and)
BOOST_LAMBDA2_BINARY_LAMBDA(||, logical_or)
BOOST_LAMBDA2_UNARY_LAMBDA(!, logical_not)

BOOST_LAMBDA2_BINARY_LAMBDA(&, bit_and)
BOOST_LAMBDA2_BINARY_LAMBDA(|, bit_or)
BOOST_LAMBDA2_BINARY_LAMBDA(^, bit_xor)
BOOST_LAMBDA2_UNARY_LAMBDA(~, bit_not)

#undef BOOST_LAMBDA2_UNARY_LAMBDA
#undef BOOST_LAMBDA2_BINARY_LAMBDA

using namespace std::placeholders;

} // namespace lambda2
} // namespace boost

#endif // #ifndef BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED
