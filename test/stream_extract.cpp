// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/lambda2.hpp>
#include <boost/core/lightweight_test.hpp>
#include <sstream>
#include <string>

template<class T> T from_string( std::string const& s )
{
    using namespace boost::lambda2;

    std::istringstream is( s );

    T t{};

    ( is >> _1 )( t );

    return t;
}

int main()
{
    BOOST_TEST_EQ( from_string<int>( "123" ), 123 );

    return boost::report_errors();
}
