/**
 * @file HaroldFactory.h
 * @author Ben Zuke
 *
 * Factory class that builds the Harold character
 */

#ifndef CANADIANEXPERIENCE_HAROLDFACTORY_H
#define CANADIANEXPERIENCE_HAROLDFACTORY_H

class Actor;

/**
 * Class that makes a lotta harolds for us
 */
class HaroldFactory
{
private:

public:

    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_HAROLDFACTORY_H
