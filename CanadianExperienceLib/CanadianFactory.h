/**
 * @file CanadianFactory.h
 * @author Ben
 *
 * Factory class that builds canadian 2
 */

#ifndef CANADIANEXPERIENCE_CANADIANFACTORY_H
#define CANADIANEXPERIENCE_CANADIANFACTORY_H

class Actor;

/**
 * Factory class that makes a lotta canadians for us
 */
class CanadianFactory
{
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_CANADIANFACTORY_H
