/**
 * Dispatcher base
 */
#pragma once

#include <map>
#include <iostream>
#include <vector>

using std::map;
using std::vector;


namespace Util {


/**
 * Event to run class
 */

class Event {

    public:

        Event() {};
        ~Event() {};

        virtual void run( void * p ) {};

};


/**
 * Main class
 */

class Dispatcher {

    protected:

        /**
         * Main events
         */

        map<const char *, vector<Event*> *> _events;


    public:

        /**
         * Set an event handler mapped
         *
         */

        void on( const char * event, Event * e ) {

            if( ! hasEvents( event ) ) {

                _events[ event ] = new vector<Event*>;

            };

            _events[ event ]->push_back( e );

        };


        /**
         * Dispatch mapped event
         *
         */

        void dispatch( const char * event, void * data ) {

            if( ! hasEvents( event ) ) {

                return;

            };

            vector<Event*> mapEvents = * _events[ event ];

            vector<Event*>::iterator it;

            for( it = mapEvents.begin(); it != mapEvents.end(); ++ it ) {

                (*it)->run( data );

            }

        };


        /**
         * Event been found
         *
         */

        bool hasEvents( const char * event ) {

            return ( _events.find( event ) != _events.end() );

        };

};

};
