#include "PyramidItemPathFactory.hpp"

QPainterPath PyramidItemPathFactory::getItemPath(ItemPathType itemPathType)
{
    QPainterPath painterPath;

    switch(itemPathType)
    {
    case firstItemPath:
        painterPath.moveTo(46 , 0);
        painterPath.lineTo(72 , 0);
        painterPath.lineTo(125, 125);
        painterPath.lineTo(125, 135);
        painterPath.lineTo(0  , 135);
        painterPath.lineTo(0  , 125);
        painterPath.lineTo(46 , 0);
        break;

    case secondItemPath:
        painterPath.moveTo(62 , 0);
        painterPath.lineTo(147, 0);
        painterPath.lineTo(147, 138);
        painterPath.lineTo(0  , 138);
        painterPath.lineTo(62 , 0);
        break;

    case thirdItemPath:
        painterPath.moveTo(0, 0);
        painterPath.lineTo(66, 0);
        painterPath.lineTo(139, 120);
        painterPath.lineTo(139 ,138);
        painterPath.lineTo(0, 138);
        painterPath.lineTo(0, 0);
        break;

    case fourthItemPath:
        painterPath.moveTo(64 , 0);
        painterPath.lineTo(230, 0);
        painterPath.lineTo(230, 151);
        painterPath.lineTo(0  , 151);
        painterPath.lineTo(0  , 100);
        painterPath.lineTo(64 , 0);
        break;

    case fivthItemPath:
        painterPath.moveTo(0, 0);
        painterPath.lineTo(150, 0);
        painterPath.lineTo(230, 100);
        painterPath.lineTo(230 ,151);
        painterPath.lineTo(0, 151);
        painterPath.lineTo(0, 0);
        break;

    case sixthItemPath:
        painterPath.moveTo(95 , 0);
        painterPath.lineTo(575, 0);
        painterPath.lineTo(665, 148);
        painterPath.lineTo(665, 170);
        painterPath.lineTo(0  , 170);
        painterPath.lineTo(0  , 144);
        painterPath.lineTo(95 , 0);
        break;
    }

    return painterPath;
}
