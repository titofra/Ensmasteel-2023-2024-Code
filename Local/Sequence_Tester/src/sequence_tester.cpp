#include "sequence.hpp"
#include "action.hpp"
#include "action_functions.hpp"
#include <SFML/Graphics.hpp>

void Generate_Graph (sf::VertexArray* graph, std::vector<sf::CircleShape>* points, float mmToPxX, float mmToPxY, float pxOffsetX, float pxOffsetY, Sequence seq, unsigned long dt, Kinetic beginKinetic, float Rpoint = 3.0f);
void Display (sf::VertexArray graph, std::vector<sf::CircleShape> points, const int width, const int height);

int main (void) {

    const int width = 1200;
    const int height = 800;
    const int pxOffsetX = 10;
    const int pxOffsetY = 10;
    const float mmToPxX = (float) (width - pxOffsetY) / 3000.0f;
    const float mmToPxY = (float) (height - pxOffsetX) / 1500.0f;
    const unsigned long dt = 100;    // here dt has ne effect on the trajectory, however it has an effect in the number of sequence's call aka the number of dots on the graph

    // create the sequence
    Sequence seq;
    Kinetic kin1 (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Kinetic kin2 (2000.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Action aller (
        MOVEMENT_ACT,
        linear (0, 1500, dt),
        trapeze (0, 500, 1000, 1500, 0.7f, 0.7f),
        kin1, kin2, 1500
    );
    seq.add (aller);

    // run the game/generate the graph
    sf::VertexArray graph(sf::LinesStrip);
    std::vector<sf::CircleShape> points;
    Generate_Graph (&graph, &points, mmToPxX, mmToPxY, pxOffsetX, pxOffsetY, seq, dt, kin1);

    // display the grap
    Display (graph, points, width, height);

    return 0;
}


void Generate_Graph (sf::VertexArray* graph, std::vector<sf::CircleShape>* points, float mmToPxX, float mmToPxY, float pxOffsetX, float pxOffsetY, Sequence seq, unsigned long dt, Kinetic beginKinetic, float Rpoint) {
    unsigned long timer = 0;

    action_kind kind;
    Kinetic goal = beginKinetic;

    // add the first kinetic
    sf::Vector2f position(pxOffsetX + goal.getX () * mmToPxX, pxOffsetY + goal.getY () * mmToPxY);
    graph->append (position);
    sf::CircleShape point(Rpoint);
    point.setFillColor(sf::Color::Green);
    point.setPosition(position - sf::Vector2f (Rpoint, Rpoint));
    points->push_back(point);

    while (timer <= 2000) {
        // call the sequence
        seq.monitor (timer, dt, &kind, &goal);

        // set the point in graph and points
        position = sf::Vector2f (pxOffsetX + goal.getX () * mmToPxX, pxOffsetY + goal.getY () * mmToPxY);
        graph->append (position);
        point.setPosition(position - sf::Vector2f (Rpoint, Rpoint));    //- sf::Vector2f (Rpoint, Rpoint) is here center the dot on the position
        points->push_back(point);

        timer += dt;
    }
}

void Display (sf::VertexArray graph, std::vector<sf::CircleShape> points, const int width, const int height) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Sequence Tester - Ensmasteel");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(graph);
        // Draw the points
        for (const sf::CircleShape& point : points) {
            window.draw(point);
        }
        window.display();
    }
}