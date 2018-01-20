#ifndef GLOBAL_DECLARATIONS_H
#define GLOBAL_DECLARATIONS_H

#define SINGLETON_CLASS(_CLASS)\
static _CLASS& getInstance()\
{\
	static _CLASS Instance;\
	return Instance;\
}\
_CLASS(const _CLASS&) = delete;\
_CLASS& operator=(const _CLASS&) = delete;

#endif