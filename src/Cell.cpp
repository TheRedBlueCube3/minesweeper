// SPDX-FileCopyrightText: 2025 thorium1256
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Cell.h"

Cell::Cell(int x, int y)
    : position(x, y)
{
}

Cell::Cell(Vector2 &initPos)
    : position(initPos)
{
}

Cell::State Cell::getState() const
{
    return state;
}

void Cell::reveal()
{
    if (state != State::Flagged)
        state = State::Revealed;
}

void Cell::toggleFlag()
{
    state = (state == State::Flagged) ? State::Hidden : State::Flagged;
}

Cell::Content Cell::getContent() const
{

    return content;
}

void Cell::setContent(Content newContent)
{
    content = newContent;
}

Vector2 Cell::getPosition() const
{
    return position;
}