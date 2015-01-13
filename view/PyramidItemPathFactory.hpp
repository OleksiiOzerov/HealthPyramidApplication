#ifndef PYRAMIDITEMFACTORY_HPP
#define PYRAMIDITEMFACTORY_HPP

#include <QPainterPath>

enum ItemPathType
{
    firstItemPath = 0,
    secondItemPath,
    thirdItemPath,
    fourthItemPath,
    fivthItemPath,
    sixthItemPath,
};

class PyramidItemPathFactory
{
public:

    static QPainterPath getItemPath(ItemPathType itemPathType);
};

#endif // PYRAMIDITEMFACTORY_HPP
