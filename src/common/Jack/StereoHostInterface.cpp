/**
 * Stereo interface impl
 */

#include "StereoHostInterface.h"

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
 * Port redirection
 */

void StereoHostInterface::redirectInput( jack_nframes_t nframes ) {

    jack_default_audio_sample_t
        * inLeft,
        * inRight,
        * outLeft,
        * outRight;

    size_t bufSize = sizeof( jack_default_audio_sample_t ) * (nframes);


    //Port buffer getting

    inLeft = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _inputLeft, nframes );

    inRight = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _inputRight, nframes);

    outLeft = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _outputLeft, nframes );

    outRight = (jack_default_audio_sample_t*)
        jack_port_get_buffer( _outputRight, nframes );


    //Buffer copy redirection

    memcpy( outLeft, inLeft, bufSize );
    memcpy( outRight, inRight, bufSize );

};

};
