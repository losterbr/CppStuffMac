#include "terminalcolour.hpp"

Modifier::Modifier(ForegroundCode fgCode, BackgroundCode bgCode)
    : fgCode(fgCode), bgCode(bgCode) {}

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