/**
 * Simple layout change event impl
 */
#include "SimpleLayout.h"

#include "SimpleChangeEvent.h"


SimpleChangeEvent::SimpleChangeEvent( SimpleLayout * l ) {

    _Layout = l;

}

void SimpleChangeEvent::run( void * data ) {

    _Layout->handleChange( data );

};
