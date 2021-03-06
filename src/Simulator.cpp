#include "Simulator.h"

#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <Window/Event.hpp>

#include "HootFactory.h"

Simulator::Simulator(){
    this->height = 600;
    this->width = 800;
    window.create(sf::VideoMode(this->width,this->height), "Hoot Hoot Simulator Window");
    ticktime = 0;
}

Simulator::~Simulator(){}

void Simulator::sim(){
    
    sf::View currentView(sf::FloatRect(-(this->width/2), -(this->height/2), this->width, this->height));
    float currentZoom = 1;
    
    sf::Font font = sf::Font::getDefaultFont();
    
    // Overlay Strings
    std::string hootTitle("Hoot Hoot Simulation Alpha");
    std::string sim_status();
    std::string xyz_status();
    
    bool pause = false;
    while (window.isOpen()){
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                window.close();
                       
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                sf::Image Screen = window.capture();
                Screen.saveToFile("screenshot.jpg");
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
                if(!pause)
                    pause = true;
                else
                    pause = false;
            }
             
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                currentView.reset(sf::FloatRect(-400, -300, this->width, this->height));
                currentZoom = 1;
                this->ticktime = 0;
                this->stage.clear();
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N){
                //TODO Get current options and pass to SimulatableEntityFactory
                this->stage.addSimulatableEntity(HootFactory::construct(currentView.getCenter()));                
            }
            
            // Enable moving of view
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                currentView.move(-10, 0);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                currentView.move(10, 0);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                currentView.move(0, -10);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                currentView.move(0, 10);
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                currentView.zoom(0.99f);
                currentZoom *= 1.01;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
                currentView.zoom(1.01f);
                currentZoom *= 0.99;
            }
        }
        
        window.clear();
        window.setView(currentView);
        
        // Simulate tick if not paused
        if(!pause){
            this->ticktime++;
            this->stage.tick();
        }
        this->stage.draw(&window);
        
        // Return the default view
        window.setView(window.getDefaultView());
        
        // Simulation Information
        sf::Text simVersion(hootTitle, font, 12);
        sf::Text simTicker("Tick: "+std::to_string(this->ticktime)+" - Agents: "+std::to_string(this->stage.size())+" - Pause: "+std::to_string(pause), font, 12);
        sf::Text simXY("X: "+std::to_string(currentView.getCenter().x)+" - Y: "+std::to_string(-1* currentView.getCenter().y)+" - ZM: "+std::to_string(currentZoom), font, 12);
        simTicker.setPosition(1, this->height - simTicker.getGlobalBounds().height);
        simXY.setPosition(this->width - simXY.getGlobalBounds().width - 1, this->height - simXY.getGlobalBounds().height - 3);
        window.draw(simVersion);
        window.draw(simTicker);
        window.draw(simXY);

        window.display();
    }
}