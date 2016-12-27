/**
 * Abstract server
 *
 */
#pragma once

#include <Util/Dispatcher.h>


class Server : public Util::Dispatcher {

    protected:

        Server() {};
        ~Server() {};

        const char * _name;
        const char * _clientName;

    public:

        virtual bool start() { return false; };

        virtual bool stop() { return false; };

        virtual bool connect() { return false; };

};
