
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "lattice.h"
using namespace lattice;

TEST_CASE( "iterators work", "[iterator]" ) {
    const unsigned int D = 2;

    typedef std::array<int,D> int_d;

    lattice_iterator<D> it({{0,0}}, {{2,2}});
    int_d value;

    SECTION( "initial value" ) {
        value = *it; 

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "pre-increment" ) {
        value = *(++it); 

        REQUIRE( value[0] == 1 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "post-increment" ) {
        value = *(it++); 

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 0 );

        value = *it;

        REQUIRE( value[0] == 1 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "increment by n" ) {
        value = *(it+2); 

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 1 );
    }

    SECTION( "decrement by n" ) {
        it += 3;
        it -= 2;
        value = *it; 

        REQUIRE( value[0] == 1 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "looping" ) {

        lattice_iterator<2> end;

        SECTION( "fori loop" ) {
            int count = 0;
            for (size_t i = 0; i < end-it; ++i) {
                ++count;
            }

            REQUIRE( count == 4 );
        }

        SECTION( "iterator bool loop" ) {
            int count = 0;
            for (; it != false; ++it) {
                ++count;
            }

            REQUIRE( count == 4 );
        }

        SECTION( "iterator loop" ) {
            int count = 0;
            for (; it != end; ++it) {
                ++count;
            }

            REQUIRE( count == 4 );
        }

        SECTION( "range loop" ) {
            auto test_range = make_iterator_range(it,end);
            int count = 0;
            for (auto& val: test_range) {
                ++count;
            }

            REQUIRE( count == 4 );
        }
    }
}

TEST_CASE( "finite difference") {
    const unsigned int D = 2;
    const size_t m = 10;
    const size_t n = 11;
    const std::array<int,D> min = {{0,0}};
    const std::array<int,D> max = {{n,m}};

    auto outer_range = make_iterator_range(
                        lattice_iterator<D>(min,max),
                        false);

    auto inner_range = make_iterator_range(
                        lattice_iterator<D>({{-1,-1}},{{1,1}}),
                        false);

    std::vector<double> values(outer_range.size());

    for(auto outer_index&: range) {
        for(auto inner_index&: inner_range) {


    

