#ifndef PHYSICS_BACKEND_DETAIL_MIXINS_HPP
#define PHYSICS_BACKEND_DETAIL_MIXINS_HPP

#include <memory>
#include <sstream>
#include <tuple>

namespace physics::detail
{

template <class Derived>
class ReprMixin {
public:
    std::string repr()
    {
        auto pDerived {std::make_unique<Derived>(static_cast<Derived const&>(*this))};

        std::stringstream stream;
        std::apply
        (
            [&stream](auto const&... tupleArgs)
            {
                stream << '[';
                std::size_t n{0};
                ((stream << tupleArgs << (++n != sizeof...(tupleArgs) ? ", " : "")), ...);
                stream << ']';
            }, pDerived->getElements()
        );

        return stream.str();
    }
};

} // namespace physics::detail

#endif // PHYSICS_BACKEND_DETAIL_MIXINS_HPP