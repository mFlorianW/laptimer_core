# System Module
The purpose of this modules is to provide some operating system independent features like timer, synchronization etc. 
All the elements in the module are developed with a event driven approach, that means that most of the implementations will have signals to notifier about changes that then can be handled by the caller.

**Restrictions**
The implementations are not thread safe but the classes are reentrant. That means all classes shouldn't be used in different threads.

## System Task
The system task implements the event handling for most of the elements in that module. The system task must be called
periodically in the application main loop. For a good responsiveness the system task should be called every 5ms. 

Is it necessary to use implementation like timers or thread synchronization of this module in a thread.
Then in this thread the system task must also and periodically called. 

## Timer
A timer can be used to periodically a function or just get notified when the timeout occur.


