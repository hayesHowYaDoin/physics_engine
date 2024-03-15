#ifndef PHYSICS_BACKEND_DETAIL_MIXINS_HPP
#define PHYSICS_BACKEND_DETAIL_MIXINS_HPP

#include <memory>
#include <sstream>
#include <tuple>

namespace physics::detail
{

namespace
{

template <typename T>
concept Stringable = requires(T t)
{
    std::cout << t;
};

} // namespace

template <typename T>
using Element = std::pair<std::string, T>;

template <class Derived>
class ReprMixin {
public:
    std::string repr() const
    {
        auto pDerived {std::make_unique<Derived>(static_cast<Derived const&>(*this))};

        std::stringstream stream;
        std::apply
        (
            [&stream](auto const&... tupleArgs)
            {
                stream << '<';
                std::size_t n{0};
                ((
                    stream << tupleArgs.first << ": ",
                    unpack(stream, tupleArgs.second),
                    stream << (++n != sizeof...(tupleArgs) ? ", " : "")
                ), ...);
                stream << '>';
            }, pDerived->getElements()
        );

        return stream.str();
    }

private:
    template <typename T>
    static void unpack(std::ostream& stream, T&&)
    {
        stream << "?";
    }

    template <Stringable T>
    static void unpack(std::ostream& stream, T&& element)
    {
        stream << element;
    }

    template <std::ranges::range T>
        requires (!Stringable<T>)
    static void unpack(std::ostream& stream, T&& elements)
    {
        stream << '[';
        std::size_t i{0};
        for (const auto& element : elements)
        {
            stream << element << (++i != elements.size() ? ", " : "");
        }
        stream << ']';
    }
};

} // namespace physics::detail

#endif // PHYSICS_BACKEND_DETAIL_MIXINS_HPP