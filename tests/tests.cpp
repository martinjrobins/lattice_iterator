
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "lattice.h"
using namespace lattice;

TEST_CASE( "iterators work", "[iterator]" ) {
    const unsigned int D = 2;

    typedef std::array<int,D> int_d;

    lattice_iterator<D> it({0,0}, {2,2}, {0,0});
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

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 1 );
    }

    SECTION( "looping" ) {

        lattice_iterator<2> end({0,0}, {2,2}, {1,1});
        end++;

        SECTION( "fori loop" ) {
            int count = 0;
            for (size_t i = 0; i < end-it; ++i) {
                ++count;
            }

            REQUIRE( count == 3 );
        }

        SECTION( "iterator loop" ) {
            int count = 0;
            for (; it != end; ++it) {
                ++count;
            }

            REQUIRE( count == 3 );
        }

        SECTION( "range loop" ) {
            auto test_range = make_iterator_range(it,end);
            int count = 0;
            for (auto& val: test_range) {
                ++count;
            }

            REQUIRE( count == 3 );
        }
    }
}
