#include "example/example.hpp"
#include "example/example_p.hpp"

#include <iostream>

namespace example
{
    
    Toggler::Toggler(bool initialValue)
        : m_impl { std::make_unique<TogglerImpl>(initialValue) }
    {
        // Intentionally blank
    }

    Toggler::~Toggler()
    {
        // Intentionally blank
    }

    bool Toggler::toggle()
    {
        m_impl->value = !m_impl->value;
        
        return m_impl->value;
    }

}
