/**
 * @file mexUDP.cpp
 * @author Julien (julien.esposito@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  mexUDP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "simstruc.h"

/* Include custom code */
#include "QtUdpSender.hpp"

#include <cstring>
#include <cstdio>

#define MDL_START
#define MDL_SET_INPUT_PORT_DATA_TYPE
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define NUM_PARAMETERS  0
#define NUM_INPUTS      1
#define NUM_OUTPUTS     0
#define NUM_POINTER_OBJECTS 2
#define NUM_REAL_OBJECTS 0
#define NUM_INT_OBJECTS 0
#define NUM_SAMPLE_TIMES 1
#define INPUT_PORT_WIDTH 12
#define SINGLE_INPUT_PORT_INDEX 0
#define INDEX_UDP_SENDER    0

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static void write_timestamp_file( void )
{
    static bool hasBeenCreated = false;
    if( !hasBeenCreated ) {
        FILE* f = fopen( "mexUDP.txt", "w" );
        fclose( f );
        hasBeenCreated = true;
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static void mdlInitializeSizes( SimStruct* S )
{
    ssSetNumSFcnParams( S, NUM_PARAMETERS );

    /* Parameter mismatch will be reported by Simulink */
    if( ssGetNumSFcnParams( S ) != ssGetSFcnParamsCount( S ) ) {
        mexPrintf( "Parameter mismatch detected.\n" );
        return;
    } else {
        mexPrintf( "No parameter mismatch detected.\n" );
    }

    /* Specify I/O */
    if( !ssSetNumInputPorts( S, NUM_INPUTS ) )
        return;
    ssSetInputPortWidth( S, SINGLE_INPUT_PORT_INDEX, INPUT_PORT_WIDTH );

    // note: dupplicate code in "mdlSetInputPortDataType"
    ssSetInputPortDataType( S, SINGLE_INPUT_PORT_INDEX, SS_DOUBLE );
    ssSetInputPortDirectFeedThrough( S, SINGLE_INPUT_PORT_INDEX, 1 );
    if( !ssSetNumOutputPorts(S,NUM_OUTPUTS ) )
    return;

    ssSetNumSampleTimes( S, NUM_SAMPLE_TIMES );

    ssSetNumPWork( S, NUM_POINTER_OBJECTS );
    ssSetNumRWork( S, NUM_REAL_OBJECTS );
    ssSetNumIWork( S, NUM_INT_OBJECTS );
    return;
}

#if defined( MDL_SET_INPUT_PORT_DATA_TYPE )
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void mdlSetInputPortDataType(SimStruct *S, int_T port, DTypeId id )
{
    ssSetInputPortDataType( S, SINGLE_INPUT_PORT_INDEX, SS_DOUBLE );
    return;
}
#endif /* MDL_SET_INPUT_PORT_DATA_TYPE defined */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static void mdlInitializeSampleTimes( SimStruct* S )
{
    ssSetSampleTime( S, 0, INHERITED_SAMPLE_TIME );
    ssSetOffsetTime( S, 0, 0.0 );
    ssSetModelReferenceSampleTimeDefaultInheritance( S );
    return;
}

#if defined( MDL_START )
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void mdlStart( SimStruct* S )
{
    QtUdpSender* qt_udp_sender = new QtUdpSender;
    void** pointer_array = ssGetPWork( S );
    pointer_array[ INDEX_UDP_SENDER ] = qt_udp_sender;
    return;
}
#endif /* MDL_START defined */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static void mdlOutputs( SimStruct* S, int_T tid )
{
    /* Retrieve C++ object from the pointers vector */
    void** pointer_array = ssGetPWork( S );
    QtUdpSender* qt_udp_sender = static_cast< QtUdpSender* >( pointer_array[ INDEX_UDP_SENDER ] );
    return;

    // Get data addresses of I/O
    double*  inputs = ( double* )( ssGetInputPortRealSignalPtrs( S, SINGLE_INPUT_PORT_INDEX ) );

    double first_element = inputs[ 0 ];
    write_timestamp_file(  );
    return;
}
    
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static void mdlTerminate( SimStruct* S )
{
    void** pointer_array = ssGetPWork( S );
    QtUdpSender* qt_udp_sender = static_cast< QtUdpSender* >( pointer_array[ INDEX_UDP_SENDER ] );
    delete qt_udp_sender;
    return;
}

/* Required S-function trailer */
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
