/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 */

#ifndef __SOT_MAILBOX_HH
#define __SOT_MAILBOX_HH


/* --- SOT PLUGIN  --- */
#include <dynamic-graph/entity.h>
#include <dynamic-graph/all-signals.h>

/* --- BOOST --- */
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>

/* --- STD --- */
#include <time.h>
#ifndef WIN32
#include <sys/time.h>
#else
#include <sot/core/utils-windows.hh>
#endif /*WIN32*/
#include <string>

namespace dynamicgraph { namespace sot {

namespace dg = dynamicgraph;

template< class Object >
class Mailbox
: public dg::Entity
{
 public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

 public:
  struct sotTimestampedObject
  {
    Object obj;
    struct timeval timestamp;
  };

public:

  Mailbox( const std::string& name );
  ~Mailbox( void );

  void post( const Object& obj );
  sotTimestampedObject& get( sotTimestampedObject& res,const int& dummy );

  Object& getObject( Object& res,const int& time );
  struct timeval& getTimestamp( struct timeval& res,const int& time );

  bool hasBeenUpdated( void );

protected:

  boost::timed_mutex mainObjectMutex;
  Object mainObject;
  struct timeval mainTimeStamp;
  bool update;

 public: /* --- SIGNALS --- */

  dg::SignalTimeDependent< struct sotTimestampedObject,int > SOUT;
  dg::SignalTimeDependent< Object,int > objSOUT;
  dg::SignalTimeDependent< struct timeval,int > timeSOUT;

};



} /* namespace sot */} /* namespace dynamicgraph */

#endif // #ifndef  __SOT_MAILBOX_HH
