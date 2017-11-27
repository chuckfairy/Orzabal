/**
 * Stereo interface impl
 */
#include <string.h>
#include <vector>

#include "StereoHostInterface.h"

using std::vector;
using std::string;

namespace Jack {


/**
 * Construct from Standalone
 */

StereoHostInterface::StereoHostInterface( jack_client_t * c ) :
    ServerStandalone( c )
{
};


/**
 *  Get full name with prefix
 */

const char * StereoHostInterface::getPortFullName( const char * name ) {

    char * c = (char*) malloc( 255 );

    sprintf( c, "%s:%s", getPrefix(), name );

    return c;

};


/**
 * Create input ports
 */

void StereoHostInterface::createPorts() {

    _inputLeftNameFull = getPortFullName( _inputLeftName );
    _inputRightNameFull = getPortFullName( _inputRightName );
    _outputLeftNameFull = getPortFullName( _outputLeftName );
    _outputRightNameFull = getPortFullName( _outputRightName );

    _inputLeft = jack_port_register(
        _jackClient,
        _inputLeftNameFull,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput,
        0
    );

    _inputRight = jack_port_register(
        _jackClient,
        _inputRightNameFull,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput,
        0
    );

    _outputLeft = jack_port_register(
        _jackClient,
        _outputLeftNameFull,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );

    _outputRight = jack_port_register(
        _jackClient,
        _outputRightNameFull,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );

    _inputPorts.push_back( _inputLeft );
    _inputPorts.push_back( _inputRight );
    _outputPorts.push_back( _outputLeft );
    _outputPorts.push_back( _outputRight );

};

/**
 * StereoHostInterface back connection to private client
 *
 */

int StereoHostInterface::connectJackPort( const char * source, const char * destination ) {

    return jack_connect( _jackClient, source, destination );

};


/**
 * StereoHostInterface back connection to private client
 *
 */

int StereoHostInterface::disconnectJackPort( jack_port_t * port ) {

    return jack_port_disconnect( _jackClient, port );

};

/**
 * Connection to mono
 */

bool StereoHostInterface::connectInputTo( const char * out ) {

    connectJackPort( out, getInputNameLeft() );
    connectJackPort( out, getInputNameRight() );

    return true;

};


/**
 * Connection to stereo
 */

bool StereoHostInterface::connectInputTo( const char * outLeft, const char * outRight ) {

    std::cout << "\n" << outLeft << " " << outRight;

    connectJackPort( outLeft, getInputNameLeft() );
    connectJackPort( outRight, getInputNameRight() );

    return true;

};


/**
 * Connection to mono
 */

bool StereoHostInterface::connectOutputTo( const char * input ) {

    connectJackPort( getOutputNameLeft(), input );
    connectJackPort( getOutputNameRight(), input );

    return true;

};


/**
 * Connection to stereo
 */

bool StereoHostInterface::connectOutputTo( const char * inLeft, const char * inRight ) {

    connectJackPort( getOutputNameLeft(), inLeft );
    connectJackPort( getOutputNameRight(), inRight );

    return true;

};


/**
 * Clear methods
 */

void StereoHostInterface::clearInputs() {

    disconnectJackPort( _inputLeft );
    disconnectJackPort( _inputRight );

};

void StereoHostInterface::clearOutputs() {

    disconnectJackPort( _outputLeft );
    disconnectJackPort( _outputRight );

};


/**
 * Port redirection
 */

void StereoHostInterface::redirectInput( jack_nframes_t nframes ) {

    StereoHostInterface::redirectInputPort( _outputLeft, _inputLeft, nframes );
    StereoHostInterface::redirectInputPort( _outputRight, _inputRight, nframes );

};

/**
 * Port redirection
 */

void StereoHostInterface::redirectInputPort(
    jack_port_t * output,
    jack_port_t * input,
    jack_nframes_t nframes
) {

    jack_default_audio_sample_t * inBuffer, * outBuffer;

    size_t bufSize = sizeof( jack_default_audio_sample_t ) * (nframes);


    //Port buffer getting

    inBuffer = (jack_default_audio_sample_t*)
        jack_port_get_buffer( input, nframes );

    outBuffer = (jack_default_audio_sample_t*)
        jack_port_get_buffer( output, nframes );


    //Buffer copy redirection

    memcpy( outBuffer, inBuffer, bufSize );

};


/**
 * Port methods
 */

vector<const char *> StereoHostInterface::getConnectedPorts( Jack::Port * port ) {

    vector<const char *> out;

    const char ** connections = jack_port_get_connections( port->jack_port );

    if( ! connections ) {

        return out;

    }

    int i = 0;

    while( connections[ i ] ) {

        std::cout << connections[ i ] << " CONNECTION\n";
        out.push_back( connections[ i ] );

        ++ i;

    }

    return out;

};

};
