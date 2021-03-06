#ifndef POSITION_COMPONENT_H_
#define POSITION_COMPONENT_H_

#include "Component.h"
#include <System/Vector2.hpp>

class PositionComponent: public Component {
public:
    PositionComponent();
    virtual ~PositionComponent();
    
    void setPosition(sf::Vector2f newPosition);
    void movePosition(sf::Vector2f deltaPosition);

    void receive(class Message* m);
    
private:
    sf::Vector2f position;
};
#endif