////////////////////////////////////////
//  Event.h
//
//  Purpose:
// 	    1. Declair the CEvent class that encapsulates the functionality of a 
//          single-locking semaphore.
//
//  Revisions:
// 	    07/10/2001  Created                                    
//

#ifndef BASE_LINUX_EVENT_H
#define BASE_LINUX_EVENT_H

#include "Platform.h"

namespace Base
{

    ////////////////////////////////////////
    //  Class:
    // 	    CEvent
    //
    //  Purpose:
    // 	    Encapsulates the functionality of a singal-locking semaphore.
    //      This class is valuable for thread syncronization when a thead's
    //      execution needs to be dependent upon another thread.  
    //
    //  Public Methods:
    // 	    Signal() : Signals a thread that has called Wait() so that it can 
    //          continue execution.  This function returns true if the waiting 
    //          thread was signalled successfully, otherwise false is returned.
    //      Wait() : Halts the calling thread's execution indefinately until
    //          a Singal() call is made by an external thread.  If the thread is 
    //          successfully signalled, the function returns eWAIT_SIGNAL.  If
    //          timeout period expires without a signal, eWAIT_TIMEOUT is returned.
    //          If the function fails, eWAIT_ERROR is returned.
    //
    class CEvent  
    {
        public:
	        CEvent();
	        virtual ~CEvent();

            bool    Signal();
            int32   Wait(uint32 timeout = 0);
    
        public:
                enum    { eWAIT_ERROR, eWAIT_SIGNAL, eWAIT_TIMEOUT };
        private:
            pthread_mutex_t mMutex;
            pthread_cond_t  mCond;
            bool            mInitialized;
    };

    inline bool CEvent::Signal()
    {
        if (!mInitialized)
            return false;

        pthread_cond_signal(&mCond);
        return true;
    }

}

#endif  //  BASE_LINUX_EVENT_H
