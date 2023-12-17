using Magnitude = double;

Magnitude operator"" _mag(long double value) {
    return static_cast<Magnitude>(value);
}
