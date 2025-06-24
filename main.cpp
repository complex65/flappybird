#include <SFML/Graphics.hpp> //smflgraphics module
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "game");

    window.setFramerateLimit(60); //fps
//bird
    sf::CircleShape bird(20);
    bird.setFillColor(sf::Color::Yellow);
    bird.setPosition(200, 400); //start position tweak if bad

    float velocity = 0.0f;
    float gravity = 0.5f;
    float jumpStrength = -10.0f;
//pipe
std::vector<sf::RectangleShape> pipes;
float pipeSpeed = 3.0f;
float pipeWidth = 60.0f;
float gapHeight = 300.0f;
sf::Clock pipeClock; 


std::srand(std::time(nullptr));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                velocity = jumpStrength; 
            }
        }
        velocity += gravity;
        bird.move(0, velocity); //moves bird vertically 
        if (bird.getPosition().y > 780){ //so it dosent go of bottom
            bird.setPosition(bird.getPosition().x, 580);
            velocity = 0;
        }

        //chat gpt from here

       if (pipeClock.getElapsedTime().asSeconds() > 1.5f) {
            float topHeight = rand() % 250 + 50; 
            float bottomY = topHeight + gapHeight;
            float bottomHeight = 600 - bottomY;

            sf::RectangleShape topPipe(sf::Vector2f(pipeWidth, topHeight));
            sf::RectangleShape bottomPipe(sf::Vector2f(pipeWidth, bottomHeight));

            topPipe.setFillColor(sf::Color::Green);
            bottomPipe.setFillColor(sf::Color::Green);

            topPipe.setPosition(800, 0);
            bottomPipe.setPosition(800, bottomY);

            pipes.push_back(topPipe);
            pipes.push_back(bottomPipe);

            pipeClock.restart(); 
        }

        for (size_t i = 0; i < pipes.size(); ++i) {
            pipes[i].move(-pipeSpeed, 0); 
        }

         if (!pipes.empty() && pipes[0].getPosition().x + pipeWidth < 0) {
            pipes.erase(pipes.begin(), pipes.begin() + 2); 
        }

        // to here 


        window.clear(sf::Color::Cyan); 
        window.draw(bird);
        for(auto& pipe : pipes)
            window.draw(pipe);
        window.display();
    }
    return 0;
}