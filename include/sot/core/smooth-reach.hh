/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 */

#ifndef __SOT_SMOOTHREACH_H_H
#define __SOT_SMOOTHREACH_H_H

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* Matrix */
#include <dynamic-graph/linear-algebra.h>
namespace dg = dynamicgraph;

/* SOT */
#include <dynamic-graph/entity.h>
#include <dynamic-graph/all-signals.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32)
#  if defined (com_freezer_EXPORTS)
#    define SOTSMOOTHREACH_EXPORT __declspec(dllexport)
#  else
#    define SOTSMOOTHREACH_EXPORT __declspec(dllimport)
#  endif
#else
#  define SOTSMOOTHREACH_EXPORT
#endif


namespace dynamicgraph { namespace sot {

namespace dg = dynamicgraph;

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

class SOTSMOOTHREACH_EXPORT SmoothReach
: public dg::Entity
{
  public:
    static const std::string CLASS_NAME;
    virtual const std::string & getClassName() const { return CLASS_NAME; }

  private:
    dg::Vector start,goal;
    int startTime, lengthTime;
    bool isStarted, isParam;
    int smoothMode; double smoothParam;

    double smoothFunction( double x );

  public: /* --- CONSTRUCTION --- */
    SmoothReach(const std::string & name);
    virtual ~SmoothReach(void) {};

  public: /* --- SIGNAL --- */
    dg::SignalPtr<dg::Vector, int> startSIN;
    dg::SignalTimeDependent<dg::Vector, int> goalSOUT;
    //dg::SignalTimeDependent<double, int> percentSOUT;

  public: /* --- FUNCTION --- */
    dg::Vector& goalSOUT_function(dg::Vector & goal, const int& time);

    void set( const dg::Vector & goal, const int & length );
    const dg::Vector & getGoal( void );
    const int & getLength( void );
    const int & getStart( void );

    void setSmoothing( const int & mode, const double & param );

  public: /* --- PARAMS --- */
    virtual void display(std::ostream & os) const;
    void initCommands( void );
};



} /* namespace sot */} /* namespace dynamicgraph */



#endif /* #ifndef __SOT_SMOOTHREACH_H_H */
