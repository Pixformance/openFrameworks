#pragma once

#include "ofConstants.h"
#include "ofTypes.h"

#include "poco/Thread.h"
#include "poco/Runnable.h"

/// a thread base class with a built in mutex
///
/// derive this class and implement threadedFunction()
class ofThread : protected Poco::Runnable {

	public:
	
		ofThread();
		virtual ~ofThread();
	
		/// returns true if the thread is currently running
		bool isThreadRunning();
		
		/// get the unique thread id
		///
		/// note: this is *not* the OS thread id!
		int getThreadId();
		
		/// get the unique thread name, in the form of "Thread id#"
		string getThreadName();
		
		/// start the thread
		///
		/// set blocking to true if you want the mutex to block on lock()
		///
		/// set verbose to true if you want detailed logging on thread and mutex
		/// events
		void startThread(bool blocking = true, bool verbose = false);
		
		/// try to lock the mutex
		///
		/// if the thread is blocking, this call will wait until the mutex is
		/// available
		///
		/// if the thread is non-blocking, this call will return a true or false
		/// if the mutex is available
		bool lock();
		
		/// unlock the mutex
		///
		/// only unlocks the mutex if the calling thread had previosuly locked
		/// it
		void unlock();
		
		/// stop the thread
		///
		/// set close to true if you want the thread to exit immediately
		///
		/// set close to false if you want to signal the thread to exit, then
		/// wait for it to finish with waitForThread()
		void stopThread(bool close = true);
		
		/// wait for the thread to exit
		///
		/// this function waits for the thread to exit before it returns to make
		/// sure the thread is cleaned up, otherwise you will get errors on exit
		///
		/// set stop to true if you want to signal the thread to exit before
		/// waiting, this is the equivalent to calling stopThread(false)
		///
		/// set stop to false if you have already signalled the thread to exit 
		/// by calling stopThread(false) and only need to wait for it to finish
		///
		void waitForThread(bool stop = true);
		
		/// tell the thread to sleep for a certain amount of milliseconds
		///
		/// this is useful inside the threadedFunction() when a thread is
		/// waiting for input to process:
		///
		/// void myClass::threadedFunction() {
		///
		///		// start
		///
		///		while(isThreadRunning()) {
		///
		///			if(bReadyToProcess == true) {
		///
		///				// do some time intensive processing
		///
		///				bReadyToProcess = false;
		///			}
		///			else {
		///				
		///				// sleep the thread to give up some cpu
		///				sleep(20);
		///			}
		///		}
		///
		///		// done
		///	}
		///
		/// not sleeping the thread means the thread will take 100% of the cpu
		/// while it's waiting and will impact performance of your app 
		///
		void sleep(int sleepMS);
		
		/// tell the thread to give up the cpu to other threads
		///
		/// this function is similar to sleep() and can be used in the same way,
		/// the main difference is that 1 ms is a long time on modern processors
		/// and yeild() simply gives up processing time to the next thread
		/// instead of waiting for a certain amount of time
		///
		/// this can be faster in some circumstances
		///
		void yield();
		
		/// get the current thread, returns 0 if in the main app thread
		///
		/// this is useful for checking which thread a function is currently
		/// running in:
		///
		/// if(ofThread::getCurrentThread() == &myThread){
		///	    // we are myThread, do something
		/// }
		///
		/// or:
		///
		/// if(ofThread::getCurrentThread() != 0){
		///     // we are in a thread
		/// }
		/// else {
		///     // we are in the main app thread
		/// }
		///
		static ofThread * getCurrentThread();

	protected:

		/// this is the thread run function
		///
		/// you need to overide this in your derived class and implement your 
		/// thread stuff inside
		///
		/// if you do not have a loop inside this function, it will run once
		/// then exit
		///
		/// if you want the thread to run until you signal it to stop, use a 
		/// while loop inside that checks if the thread is should keep running:
		///
		/// void myClass::threadedFunction() {
		///
		///		// start
		///
		///		while(isThreadRunning()) {
		///
		///			// do stuff
		///		}
		///
		///		// done
		///	}
		///
		virtual void threadedFunction();
		
		/// the internal mutex called through lock() & unlock()
		ofMutex mutex;

		bool threadRunning;	///< is the thread running?
		bool blocking;		///< should the mutex block?
		bool verbose;		///< print detailed run/mutex info?
	
	private:
	
		/// runs the user thread function
		void run(); 
		
		Poco::Thread thread;
};
