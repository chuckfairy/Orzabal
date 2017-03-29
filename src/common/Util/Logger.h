/**
 * Logger interface
 */
#pragma once

#include "Dispatcher.h"

namespace Util {

/**
 * Logger interface
 */

class Logger : public Util::Dispatcher {

    private:

    public:

        Logger() {};

        /**
         * Static log event types
         */

        static const char * LOG_ANY = "a";
        static const char * LOG_ERROR = "e";
        static const char * LOG_INFO = "i";
        static const char * LOG_WARN = "w";


        /**
         * Singleton
         */

        Logger * getLogger() {

            static Logger * logger;

            if( ! logger ) {

                logger = new Logger;

            }

            return logger;

        };


        /**
         * Main log method
         */

        void log( const char * logType, const char * message ) {

            dispatch( logType, message );
            dispatch( LOG_ANY, message );

        };


        /**
         * Log helpers
         */

        void error( const char * message ) {

            return log( message, LOG_ERROR );

        }:

        void info( const char * message ) {

            return log( message, LOG_INFO );

        }:

        void warn( const char * message ) {

            return log( message, LOG_WARN );

        }:

};

};
