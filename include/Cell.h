#pragma once

#include "Vector2.h"

class Cell
{
public:
    enum class Content
    {
        Empty = 0,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Mine
    };

    enum class State
    {
        Hidden,
        Revealed,
        Flagged,
        NotAMine
    };

    friend class Board;

    Cell() = default;
    Cell(int x, int y);
    Cell(Vector2 &initPos);

    State getState() const;
    void reveal();
    void toggleFlag();
    Content getContent() const;
    void setContent(Content newContent);

private:
    State state = State::Hidden;
    Content content = Content::Empty;
    Vector2 position;
};