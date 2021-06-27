#ifndef BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED
#define BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <functional>
#include <type_traits>
#include <utility>

// Same format as BOOST_VERSION:
//   major * 100000 + minor * 100 + patch
#define BOOST_LAMBDA2_VERSION 107700

namespace boost
{
namespace lambda2
{

template<int I> struct lambda2_arg
{
};

#if defined(__cpp_inline_variables) && __cpp_inline_variables >= 201606L
# define BOOST_LAMBDA2_INLINE_VAR inline
#else
# define BOOST_LAMBDA2_INLINE_VAR
#endif

BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<1> _1;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<2> _2;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<3> _3;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<4> _4;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<5> _5;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<6> _6;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<7> _7;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<8> _8;
BOOST_LAMBDA2_INLINE_VAR constexpr lambda2_arg<9> _9;

#undef BOOST_LAMBDA2_INLINE_VAR

} // namespace lambda2
} // namespace boost

template<int I> struct std::is_placeholder< boost::lambda2::lambda2_arg<I> >: std::integral_constant<int, I>
{
};

namespace boost
{
namespace lambda2
{

namespace lambda2_detail
{

template<class T> using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<class T, class T2 = remove_cvref_t<T>> using is_lambda_expression =
    std::integral_constant<bool, std::is_placeholder<T2>::value || std::is_bind_expression<T2>::value>;

template<class A> using enable_unary_lambda =
    std::enable_if_t<is_lambda_expression<A>::value>;

template<class A, class B> using enable_binary_lambda =
    std::enable_if_t<is_lambda_expression<A>::value || is_lambda_expression<B>::value>;

} // namespace lambda2_detail

#define BOOST_LAMBDA2_UNARY_LAMBDA(op, fn) \
    template<class A, class = lambda2_detail::enable_unary_lambda<A>> \
    auto operator op( A&& a ) \
    { \
        return std::bind( fn(), std::forward<A>(a) ); \
    }

#define BOOST_LAMBDA2_BINARY_LAMBDA(op, fn) \
    template<class A, class B, class = lambda2_detail::enable_binary_lambda<A, B>> \
    auto operator op( A&& a, B&& b ) \
    { \
        return std::bind( fn(), std::forward<A>(a), std::forward<B>(b) ); \
    }

BOOST_LAMBDA2_BINARY_LAMBDA(+, std::plus<>)
BOOST_LAMBDA2_BINARY_LAMBDA(-, std::minus<>)
BOOST_LAMBDA2_BINARY_LAMBDA(*, std::multiplies<>)
BOOST_LAMBDA2_BINARY_LAMBDA(/, std::divides<>)
BOOST_LAMBDA2_BINARY_LAMBDA(%, std::modulus<>)
BOOST_LAMBDA2_UNARY_LAMBDA(-, std::negate<>)

BOOST_LAMBDA2_BINARY_LAMBDA(==, std::equal_to<>)
BOOST_LAMBDA2_BINARY_LAMBDA(!=, std::not_equal_to<>)
BOOST_LAMBDA2_BINARY_LAMBDA(>, std::greater<>)
BOOST_LAMBDA2_BINARY_LAMBDA(<, std::less<>)
BOOST_LAMBDA2_BINARY_LAMBDA(>=, std::greater_equal<>)
BOOST_LAMBDA2_BINARY_LAMBDA(<=, std::less_equal<>)

BOOST_LAMBDA2_BINARY_LAMBDA(&&, std::logical_and<>)
BOOST_LAMBDA2_BINARY_LAMBDA(||, std::logical_or<>)
BOOST_LAMBDA2_UNARY_LAMBDA(!, std::logical_not<>)

BOOST_LAMBDA2_BINARY_LAMBDA(&, std::bit_and<>)
BOOST_LAMBDA2_BINARY_LAMBDA(|, std::bit_or<>)
BOOST_LAMBDA2_BINARY_LAMBDA(^, std::bit_xor<>)
BOOST_LAMBDA2_UNARY_LAMBDA(~, std::bit_not<>)

} // namespace lambda2
} // namespace boost

#endif // #ifndef BOOST_LAMBDA2_LAMBDA2_HPP_INCLUDED
