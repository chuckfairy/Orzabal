/**
 * Abstract server
 *
 */
#include <map>
#include <vector>
#include <string>

class Server {

    protected:

        Server() {};
        ~Server() {};

        const char * name;

    public:

        virtual bool start() { return false; };

        virtual bool stop() { return false; };

        virtual bool connect() { return false; };

};
