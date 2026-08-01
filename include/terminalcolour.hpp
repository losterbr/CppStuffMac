#pragma once

#include <ostream>

// https://en.wikipedia.org/wiki/ANSI_escape_code
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
    explicit Modifier(ForegroundCode fgCode = ForegroundCode::DEFAULT,
                      BackgroundCode bgCode = BackgroundCode::DEFAULT);

    ForegroundCode foreground() const;
    BackgroundCode background() const;
};

std::ostream &operator<<(std::ostream &os, const Modifier &mod);