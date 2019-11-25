
#include <chrono>         // C++ standard library, requires C++ 11
#include <thread>         // thread library required for thread wait
#include <random>         // C++ standard library, requires C++ 11


/* number of ticks since the epcoh

 - TODO: Requires chrono standard library and C++ 11, if C++ 11 not installed, need to fall back to older approach
 - TODO: Use a template datatype instead of unsigned long for different systems
 - TODO: Note forced casting by division with unsigned long (std::chrono::microseconds()), consider std::chrono::duration_cast() instead
*/
inline unsigned long timeSinceEpoch()
{
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::microseconds(1);
}

/* stops the current thread for n seconds - its possible for multithread management operatons to cause delayes beyond this */
inline void waitSeconds(unsigned long n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
}

/* stops the current thread for n seconds - its possible for multithread management operatons to cause delayes beyond this */
inline void waitMilliseconds(unsigned long n)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
}

/* stops the current thread for n seconds - its possible for multithread management operatons to cause delayes beyond this */
inline void waitMicroseconds(unsigned long n)
{
    std::this_thread::sleep_for(std::chrono::microseconds(n));
}

/* stops the current thread for n seconds - its possible for multithread management operatons to cause delayes beyond this */
inline void waitNanoseconds(unsigned long n)
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(n));
}

/* Move this to a random utils module */
inline float randomFloat(float min, float max)
{
    static std::default_random_engine e;                      // random engine should only be created once, hence static
    static std::uniform_real_distribution<> dis(min, max);    // uniform distribution should only be created once, hence static
    return dis(e);                                            // Pull a random value from the distribution
}

/* Move this to a random utils module */
inline bool randomBool(float prob_success)
{
    static std::default_random_engine e;                      // random engine should only be created once, hence static
    static std::bernoulli_distribution dis(prob_success);     // bernoulli distribution should only be created once, hence static
    return dis(e);                                            // Pull either True or false value from the distribution
}
