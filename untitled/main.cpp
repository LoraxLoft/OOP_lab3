#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "geometry.h"
#include "jarvis.h"
#include "graham.h"
using namespace sf;
RenderWindow win(sf::VideoMode(1000, 600), "Halo, ma duds !");
String win_state = "Menu";


class CantLoadTextureException {};

class Menu {
private:
    sf::Texture texture1;
    sf::Sprite sprite1;

    sf::Texture texture2;
    sf::Sprite sprite2;
public:
    float x, y;

    Menu (float x, float y): x(x), y(y) {
        if (!texture1.loadFromFile("../images/algo1.png"))
            throw CantLoadTextureException();
        sprite1.setTexture(texture1);
        sprite1.setScale(1, 0.75);
        sprite1.setPosition(x, y);

        if (!texture2.loadFromFile("../images/algo2.png"))
            throw CantLoadTextureException();
        sprite2.setTexture(texture2);
        sprite2.setScale(1, 0.75);
        sprite2.setPosition(x, y+sprite1.getLocalBounds().height);
    }
    void draw(sf::RenderWindow &window) {
        window.draw(sprite1);
        window.draw(sprite2);
    }
    int testClick(float mouseX, float mouseY) {
        if (sprite1.getGlobalBounds().contains(mouseX, mouseY))  return 1;
        else if (sprite2.getGlobalBounds().contains(mouseX, mouseY)) return 2;
        return 0;

    }
};


int main(){
    std::vector<Vertex> massiv_tochek;
    massiv_tochek.emplace_back(Vector2f(200, 100));
    massiv_tochek.emplace_back(Vector2f(30, 250));
    massiv_tochek.emplace_back(Vector2f(500, 80));
    massiv_tochek.emplace_back(Vector2f(400, 200));
    massiv_tochek.emplace_back(Vector2f(415, 300));
    massiv_tochek.emplace_back(Vector2f(550, 360));
    massiv_tochek.emplace_back(Vector2f(220, 440));
    massiv_tochek.emplace_back(Vector2f(300, 330));
    massiv_tochek.emplace_back(Vector2f(50, 60));

    Menu menu = Menu(240, 80);
    Algorythm *algorythm;

    while (win.isOpen()) {
        //working out all events
        sf::Event e{};
        while (win.pollEvent(e)) {
            if (e.type == Event::EventType::Closed) {
                win.close();
            }
            if (win_state == "Menu") {
                if (e.type == Event::EventType::MouseButtonPressed) {
                    int algo = menu.testClick(e.mouseButton.x, e.mouseButton.y);
                    if (algo) {
                        win_state = "Algo";
                        switch (algo) {
                            case 1:
                                algorythm = new Jarvis(massiv_tochek);
                                break;
                            case 2:
                                algorythm = new Graham(massiv_tochek, Vertex(Vector2f(220, 180)));
                        }
                        algorythm->algo();
                    }
                }
            }
        }
        //drawing stuff
        win.clear();
        if (win_state == "Menu"){
            menu.draw(win);
        } else if (win_state == "Algo") {
            algorythm->draw(win);
        }
        win.display();
    }
    return 0;
}

