#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "common.h"

template<class T>
class Sink {
public:
    virtual ~Sink() {};
    virtual void apply(const T*) = 0;
};

template <class T>
class Channel {
public:
    Channel();
    ~Channel();

    void emit(const T*);
    void listen(Sink<T> *);
private:
    std::vector<Sink<T>*> sinks;
};

#endif /* CHANNEL_H_ */
