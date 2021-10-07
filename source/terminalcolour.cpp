#include <ostream>
//https://en.wikipedia.org/wiki/ANSI_escape_code
enum class ForegroundCode
{
    RED = 31,
    GREEN = 32,
    BLUE = 34,
    DEFAULT = 39
};
enum class BackgroundCode
{
    RED = 41,
    GREEN = 42,
    BLUE = 44,
    DEFAULT = 49
};
class Modifier
{
    ForegroundCode fgCode;
    BackgroundCode bgCode;

public:
    Modifier(ForegroundCode fgCode = ForegroundCode::DEFAULT, BackgroundCode bgCode = BackgroundCode::DEFAULT) : fgCode(fgCode), bgCode(bgCode) {}
    friend std::ostream &
    operator<<(std::ostream &os, const Modifier &mod)
    {
        return os << "\033[" << int(mod.fgCode) << "m"
                  << "\033[" << int(mod.bgCode) << "m";
    }
};