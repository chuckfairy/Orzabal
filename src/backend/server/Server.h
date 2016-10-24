/**
 * Abstract server
 *
 */
#include <map>
#include <vector>
#include <string>

class Server {

    protected:

        Server();

    public:

        virtual bool start() { return false; }

        virtual bool stop() { return false; }

        virtual bool connect();

}
