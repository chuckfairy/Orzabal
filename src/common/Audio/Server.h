/**
 * Abstract server
 *
 */
#pragma once

#include <Util/Dispatcher.h>
#include "ControlInterface.h"


namespace Audio {


class Server : public Util::Dispatcher, public ControlInterface {

    protected:

        Server() {};
        ~Server() {};

        const char * _name;
        const char * _clientName;

    public:

        virtual void start() {};

        virtual void stop() {};

        virtual bool connect() { return false; };

};

};
