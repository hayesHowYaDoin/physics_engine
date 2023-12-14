#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <memory>

namespace example
{

    class TogglerImpl;

    class Toggler
    {
    public:
        Toggler(bool initialValue);
        ~Toggler();

        bool toggle();

    private:
        std::unique_ptr<TogglerImpl> m_impl;
    };
    
}

#endif // EXAMPLE_H
