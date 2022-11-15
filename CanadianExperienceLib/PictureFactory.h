/**
 * @file PictureFactory.h
 * @author Ben Zuke
 *
 * A factory class that builds our picture.
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;

/**
 * Builds the picture
 */
class PictureFactory
{
private:

public:

    std::shared_ptr<Picture> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
