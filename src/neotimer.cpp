#include "neotimer.hpp"

//Default constructor
Neotimer::Neotimer(IMillis& millis): _millis{millis}{
	this->_timer.time = 1000; //Default 1 second interval if not specified
}

Neotimer::Neotimer(IMillis& millis, unsigned long _t): _millis{millis}{
  this->_timer.time = _t;
}

//Default destructor
Neotimer::~Neotimer(){

}

//Initializations
void Neotimer::init(){
  this->_waiting = false;
}

/*
 * Repeats a timer x times
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10)){
 * 	  do something 10 times, every second (default)
 * }
 */
bool Neotimer::repeat(int times){
	if(times != NEOTIMER_UNLIMITED){
		// First repeat
		if(this->repetitions == NEOTIMER_UNLIMITED){
			this->repetitions = times;
		}
		// Stop
		if(this->repetitions == 0){
			return false;
		}

		if(this->repeat()){
			this->repetitions--;
			return true;
		}
		return false;
	}
	return this->repeat();
}

/*
 * Repeats a timer x times with a defined period
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10,5000)){
 * 	  do something 10 times, every 5 seconds
 * }
 */
bool Neotimer::repeat(int times, unsigned long _t){
	this->_timer.time = _t;
	return this->repeat(times);
}

/*
 * Repeats a timer indefinetely
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat()){
 * 	  do something indefinetely, every second (default)
 * }
 */
bool Neotimer::repeat(){
  bool ret = false;
	if(this->done()){
    this->reset();
    ret = true;
  }
	if(!this->_timer.started){
		this->_timer.last = _millis.get();
		this->_timer.started = true;
    this->_waiting = true;
  }
  return ret;
}

void Neotimer::repeatReset(){
	this->repetitions = -1;
}

/*
 * Checks if timer has finished
 * Returns true if it finished
 */
bool Neotimer::done(){
  if(!this->_timer.started) return false;
  if( (_millis.get()-this->_timer.last) >= this->_timer.time){
    this->_timer.done = true;
    this->_waiting = false;
    return true;
  }
  return false;
}

/*
 * Sets a timer preset
 */
void Neotimer::set(unsigned long t){
  this->_timer.time = t;
}

/*
 * Gets the timer preset
 */
unsigned long Neotimer::get(){
	return this->_timer.time;
}

/*
 * Returns the debounced value of signal
 * This is very useful to avoid "bouncing"
 * of electromechanical signals
 */
bool Neotimer::debounce(bool signal){
	if(this->done() && signal){
		this->start();
		return true;
	}
	return false;
}

/*
 * Resets a timer
 */
void Neotimer::reset(){
  this->stop();
  this->_timer.last = _millis.get();
  this->_timer.done = false;
}

/*
 * Start a timer
 */
void Neotimer::start(){
	this->reset();
  this->_timer.started = true;
  this->_waiting = true;
}

/*
 * Stops a timer
 */
unsigned long Neotimer::stop(){
  this->_timer.started = false;
  this->_waiting = false;
  return this->getEllapsed();
}

/*
 * Gets ellapsed time
 */
unsigned long Neotimer::getEllapsed(){
  return _millis.get()-this->_timer.last;
}

/*
 * Continues a stopped timer
 */
void Neotimer::restart(){
	if(!this->done()){
		this->_timer.started = true;
		this->_waiting = true;
	}
}

/*
 * Indicates if the timer is active
 * but has not yet finished.
 */
bool Neotimer::waiting(){
  return (this->_timer.started && !this->done()) ? true : false;
}

bool Neotimer::started(){
	return this->_timer.started;
}