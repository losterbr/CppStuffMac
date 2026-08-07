#include "terminalcolour.hpp"

Modifier::Modifier(ForegroundCode fg, BackgroundCode bg)
    : fgCode(fg), bgCode(bg) {}

ForegroundCode Modifier::foreground() const
{
    return fgCode;
}

BackgroundCode Modifier::background() const
{
    return bgCode;
}

std::ostream &operator<<(std::ostream &os, const Modifier &mod)
{
    return os << "\033[" << static_cast<int>(mod.foreground()) << "m"
              << "\033[" << static_cast<int>(mod.background()) << "m";
}