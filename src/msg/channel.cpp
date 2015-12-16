#include "channel.h"

class Movement;
template Channel<Movement>::Channel();
template Channel<Movement>::~Channel();
template void Channel<Movement>::emit(const Movement*);
template void Channel<Movement>::listen(Sink<Movement>*);

template<class T>
Channel<T>::Channel()
{
}

template<class T>
Channel<T>::~Channel ()
{
}

template<class T>
void
Channel<T>::emit(const T * msg)
{
    for (auto sink : this->sinks)
    {
        sink->send(msg);
    }
}

template<class T>
void
Channel<T>::listen(Sink<T>* sink)
{
    sinks.push_back(sink);
}
