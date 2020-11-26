#include <SFML\Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
using namespace sf;
RenderWindow win(sf::VideoMode(600, 360), "Halo, ma duds !");

class Parabola{
public:
    Vertex focus;
    float line, finish_up = 0, finish_down = 360, p;
    float thickness=9;
    std::vector<sf::Vertex> figure_up, figure_down;

    Parabola(Vertex f, float line_x){
        focus = f;
        line = line_x;
        p = line - focus.position.x;
    }

    void set_line(float new_line_x){
        line = new_line_x;
        p = line - focus.position.x;
        (*this).update_figure();
    }

    void update_figure(){
        figure_down.clear();
        figure_up.clear();
        int f_u_size = 0, f_d_size = 0;
        Vertex vershina = Vertex(Vector2f(focus.position.x + p/2, focus.position.y));
        float current_y = focus.position.y;
        float shag = 1.0;
        while(current_y>=finish_up){
            figure_up.emplace_back(Vector2f(vershina.position.x - current_y*current_y/(2*p), vershina.position.y - current_y), Color::Red);
            current_y -=shag;
            figure_up.emplace_back(Vector2f(vershina.position.x - current_y*current_y/(2*p), vershina.position.y - current_y), Color::Red);
            f_u_size+=2;
            float a = figure_up[f_u_size-1].position.x-figure_up[f_u_size-2].position.x, b = figure_up[f_u_size-1].position.y-figure_up[f_u_size-2].position.y;
            float d = std::sqrt((thickness*a*a)/(b*b + a*a)), c = -b*d/a;

            figure_up.emplace_back(Vector2f(figure_up[f_u_size-1].position.x - c, figure_up[f_u_size-1].position.y + d), Color::Red);
            f_u_size+=1;
            figure_up.emplace_back(Vector2f(figure_up[f_u_size-1].position.x + a, figure_up[f_u_size-1].position.y - b), Color::Red);
            f_u_size+=1;
        }
        current_y = focus.position.y;
        while(current_y<=finish_down){
            figure_down.emplace_back(Vector2f(vershina.position.x - (current_y-vershina.position.y)*(current_y-vershina.position.y)/(2*p), current_y), Color::Red);
            current_y +=shag;
            figure_down.emplace_back(Vector2f(vershina.position.x - (current_y-vershina.position.y)*(current_y-vershina.position.y)/(2*p), current_y), Color::Red);
            f_d_size+=2;
            float a = figure_down[f_d_size-1].position.x-figure_down[f_d_size-2].position.x, b = figure_down[f_d_size-1].position.y-figure_down[f_d_size-2].position.y;
            float d = std::sqrt((thickness*a*a)/(b*b + a*a)), c = -b*d/a;

            figure_down.emplace_back(Vector2f(figure_down[f_d_size-1].position.x + c, figure_down[f_d_size-1].position.y + d), Color::Red);
            f_d_size+=1;
            figure_down.emplace_back(Vector2f(figure_down[f_d_size-1].position.x - a, figure_down[f_d_size-1].position.y - b), Color::Red);
            f_d_size+=1;
        }
    }

    void draw(){
        win.draw(&figure_up[0], figure_up.size(), sf::Quads);
        win.draw(&figure_down[0], figure_down.size(), sf::Quads);

        CircleShape foc;
        foc = CircleShape(1);
        foc.setPosition(focus.position);
        foc.setFillColor(focus.color);
        win.draw(foc);
    }
};

int main() {
    /*
    Font font;
    if (!font.loadFromFile("C:/WINDOWS/FONTS/ALGER.TTF")) {
        return -1;
    }
    Text message("Yoh!", font);
*/

    std::vector<Vertex> massiv_tochek;
    float line_x = 0;

    massiv_tochek.emplace_back(sf::Vector2f(200, 100), sf::Color::Green);
    massiv_tochek.emplace_back(sf::Vector2f(350, 168), sf::Color::Green);

    Parabola parabola1 = Parabola(massiv_tochek[0], line_x);
    Parabola parabola2 = Parabola(massiv_tochek[1], line_x);
    parabola1.update_figure();
    parabola2.update_figure();

    int counter = 0;

    while (win.isOpen()) {
        sf::Event e{};
        while (win.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::EventType::Closed:
                    win.close();
                    break;
                    /*
                case sf::Event::EventType::Resized:
                    message.setCharacterSize(int(win.getSize().x/20));
                    break;
                     */
            }
        }

        if (line_x<=700){
            if (!(counter%10)){
                line_x++;
                parabola1.set_line(line_x);
                parabola2.set_line(line_x);
            }
        }
        counter++;

        win.clear();
        parabola1.draw();
        parabola2.draw();

        Vertex line_points[2];
        line_points[0] = Vertex(sf::Vector2f(line_x, 0), sf::Color::Blue);
        line_points[1] = Vertex(sf::Vector2f(line_x, 360), sf::Color::Blue);
        win.draw(&line_points[0], 2, Lines);

        //win.draw(message);
        win.display();
    }
    return 0;
}
