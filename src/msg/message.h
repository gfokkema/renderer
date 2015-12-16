#ifndef ACTION_H_
#define ACTION_H_

#include "common.h"

template<class T>
class Message
{
public:
    virtual ~Message() {};
    virtual void apply(T*) const = 0;
};

#endif /* ACTION_H_ */
