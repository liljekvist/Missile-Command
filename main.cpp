#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Firework.hpp"
#include "Explosion.hpp"

// Before running, you have to install the SFML-libraries
// sudo apt-get install libsfml-dev

int main()
{
    // A window is a target to render to
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Demo");
    
    /**
     * When we want to move an object in the scene based on it's velocity, we
     * need to know how long time it has passed since the last time we moved
     * the objct.
     * 
     * A clock is needed to measure the time between two updates.
     */
    sf::Clock clock;

    // This is a pointer to something that will be rendered every frame.
    SceneObject* object = new Firework(sf::Vector2f(400, 600), sf::Vector2f(400, 200));

    /**
     * This is called a "main loop" (or sometimes "game loop"). The main loop is
     * the core loop that will run the application. This makes it possible to:
     * 
     *   1. Handle all input events from the user (mouse, keyboard, moved window...).
     *   2. Update all scene objects (move, create new ones, destroy them...).
     *   3. Clear the window.
     *   4. Draw all scene objects to the window.
     *   5. Display the newly drawn window to the user.
     *   6. Repeat from 1.
     * 
     * Repeat the loop until the user has pressed the space key or closed the window.
     */
    bool running = true;
    while (running && window.isOpen())
    {
        // 1. Handle all incoming events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                    running = false;
            }
        }

        /**
         * Find out the duration since the last time all scene objects was updated.
         * Why? If you have a velocity of 2 meters per second, we can calculate your
         * new position by:
         * 
         *     newPosition = oldPosition + velocity * time
         * 
         * If we know the direction, the calculation will instead be:
         * 
         *     newPosition = oldPosition + direction * velocity * time
         */ 
        sf::Time delta = clock.restart();

        /**
         * 2. Update all scene objects.
         * 
         * In this example we only have one scene object, or a pointer to one to be
         * specific. The object will start out as a firework rocket that will be
         * destroyed when it has reached it's destination.
         * 
         * The firework's update function will move the rockets position. The function
         * will return true until the destination is reached. See the return value as
         * an answer to the question "is this object still alive?". If it returns false,
         * we want to destroy the rocket and create an explosion at the destination.
         * 
         * The explosion is also a kind of game object, which the pointer 'object' will
         * point to instead when it's alive. This means that the pointer will at any
         * time point to either a firework rocket or an explosion.
         * 
         * The explosion is represented as a growing circle that has a target radius.
         * The explosions update function will increse the circle's radius, and only
         * return false when the target radius is reached meaning the explosion is
         * finished. When an explosion is finished, we destroy it and create a new
         * firework with a random starting position and destination.
         * 
         * This goes on, and on, and on, and on... :)
         */
        if (!object->update(delta))
        {
            // You can create a variable inside the if-condition from C++17, nice! :)
            if (Firework* pFirework = dynamic_cast<Firework*>(object); pFirework) // Is the object a firework rocket?
            {
                // Destroy the firework and create an explosion
                sf::Vector2f position = pFirework->getTarget();
                delete object,
                object = new Explosion(position, 20.f);
            }

            else // It's an explosion
            {   
                // Destroy the explosion
                delete object;

                // Create a new firework rocket with a random position and destination
                // somewhere within the window's boundaries.
                int windowWidth = window.getSize().x;
                int windowHeight = window.getSize().y;
                sf::Vector2f begin(rand() % windowWidth, rand() % windowHeight);
                sf::Vector2f end(rand() % windowWidth, rand() % windowHeight);
                
                object = new Firework(begin, end);
            }            
        }

        window.clear(); // Try to comment this line out to understand why it's needed. :)
        window.draw(*object);
        window.display();
    }

    return 0;
}