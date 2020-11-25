#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;
RenderWindow win(sf::VideoMode(600, 360), "Hello World SFML Window");

class Parabola{
public:
    Vertex focus;
    float line, finish_up = 0, finish_down = 360, p;
    std::vector<sf::Vertex> figure_up, figure_down;

    Parabola(Vertex f, float line_x){
        focus = f;
        line = line_x;
        p = line - focus.position.x;
    }

    void update_figure(){
        Vertex vershina = Vertex(Vector2f(focus.position.x + p/2, focus.position.y));
        float current_y = focus.position.y;
        float shag = 1.0;
        while(current_y>=finish_up){
            figure_up.emplace_back(Vector2f(vershina.position.x - current_y*current_y/(2*p), vershina.position.y - current_y), Color::Red);
            current_y -=shag;
        }
        current_y = focus.position.y;
        while(current_y<=finish_down){
            figure_down.emplace_back()
        }
    }

    void draw(){
        win.draw(&figure_up[0], figure_up.size(), sf::LinesStrip);
        Vertex line_points[2];
        line_points[0] = Vertex(sf::Vector2f(line, 0), sf::Color::Blue);
        line_points[1] = Vertex(sf::Vector2f(line, 360), sf::Color::Blue);
        win.draw(&line_points[0], 2, Lines);
    }
};

int main() {
    Font font;
    //You need to pass the font file location
    if (!font.loadFromFile(/*
                           Put the filename that identify the font file you want to load*/"C:/WINDOWS/FONTS/ALGER.TTF")) {
        return -1;
    }
    Text message("Hello, World !", font);

    std::vector<sf::Vertex> vertices;
    vertices.emplace_back(sf::Vector2f(10, 50), sf::Color::Red);
    vertices.emplace_back(sf::Vector2f(30, 70), sf::Color::Green);
    vertices.emplace_back(sf::Vector2f(20, 90), sf::Color::Blue);
    vertices.emplace_back(sf::Vector2f(10, 60), sf::Color::Red);

    Parabola parabola = Parabola(Vertex(sf::Vector2f(200, 100), sf::Color::Blue), 250.0);
    parabola.update_figure();

    while (win.isOpen()) {
        sf::Event e{};
        while (win.pollEvent(e)) {

            switch (e.type) {
                case sf::Event::EventType::Closed:
                    win.close();
                    break;
            }
        }

        win.clear();
        win.draw(&vertices[0], vertices.size(), sf::LineStrip);
        parabola.draw();
        win.draw(message);
        win.display();
    }
    return 0;
}
