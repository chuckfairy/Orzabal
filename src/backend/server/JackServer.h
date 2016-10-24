/**
 * Jack server
 *
 */
#include "Server.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <jack/jack.h>

jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;

class JackServer : public Server {

    private:

        jack_options_t JACK_OPTIONS = JackNullOption;

        jack_status_t JACK_STATUS;

    public:

        const char *name = NULL;

}
