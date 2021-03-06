#ifndef MEDIALIB_PARTICLES_RANDOM_GENERATOR_HEADER
#define MEDIALIB_PARTICLES_RANDOM_GENERATOR_HEADER

#include <xtl/functional_fwd>

namespace media
{

namespace particles
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///Generator of random float numbers in range [-1;1]
///////////////////////////////////////////////////////////////////////////////////////////////////
class RandomGenerator
{
  public:
    ///function which generates array of random float values in range [-1; 1]
    typedef xtl::function<void (size_t count, float* values)> RandomFunction;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructors / destructor / assignment
///////////////////////////////////////////////////////////////////////////////////////////////////
    RandomGenerator  ();
    RandomGenerator  (const RandomFunction&);
    RandomGenerator  (const RandomGenerator&);
    ~RandomGenerator ();

    RandomGenerator& operator = (const RandomGenerator&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Generate single float in range [-1; 1]
///////////////////////////////////////////////////////////////////////////////////////////////////
    float Generate () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Swap
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (RandomGenerator&);

  private:
  	struct Impl;
  	Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///Swap
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (RandomGenerator&, RandomGenerator&);

}

}

#endif
