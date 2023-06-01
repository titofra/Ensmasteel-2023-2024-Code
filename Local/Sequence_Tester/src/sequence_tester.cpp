#include "sequence.hpp"
#include "action.hpp"
#include "action_functions.hpp"
#include <SFML/Graphics.hpp>

std::vector<Kinetic> Get_Kinetics_from_Sequence (Sequence seq, unsigned long dt, Kinetic beginKinetic);
void Display (std::vector<Kinetic> kinetics, const int width, const int height, float mmToPxX, float mmToPxY, float pxOffsetX, float pxOffsetY,  float Rpoint = 3.0f, float orient_line_sz = 20.0f);

const int width = 1600;
const int height = 800;
const int pxOffsetX = 10;
const int pxOffsetY = 10;
const float mmToPxX = (float) (width - 2 * pxOffsetY) / 3000.0f;
const float mmToPxY = (float) (height - 2 * pxOffsetX) / 1500.0f;
const unsigned long dt = 100;    // here dt has ne effect on the trajectory, however it has an effect in the number of sequence's call aka the number of dots on the graph


int main (void) {
    /* create the sequence */
    // kinetics
    Kinetic kin1 (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);    // pt1
    Kinetic kin2 (1000.0f, 0.0f, 0.0f, 0.0f, 0.0f); // pt2
    Kinetic kin3 (1000.0f, 0.0f, 0.0f, 0.0f, 0.0f); // pt2 (rotated, the theta is modified few lines further)
    Kinetic kin4 (200.0f, 800.0f, 0.0f, 0.0f, 0.0f);// pt3 (with the same rotation as we use a linear trajectory)
    const float theta34 = kin3.angleWith (kin4);
    kin3.setTheta (theta34);
    kin4.setTheta (theta34);

    // actions
    Action mvmt12 (
        MOVEMENT_ACT,
        linear (0, 1500),
        trapeze (0, 500, 1000, 1500, 0.7f, 0.7f),
        kin1, kin2, 1500
    );
    Action rota23 (
        MOVEMENT_ACT,
        linear (1500, 1700),
        linear (),
        kin2, kin3, 1700
    );
    Action mvmt34 (
        MOVEMENT_ACT,
        linear (1700, 4000),
        trapeze (1700, 2500, 3300, 4000, 0.5f, 0.8f),
        kin3, kin4, 4000
    );

    // sequence
    Sequence seq;
    seq.add (mvmt12);
    seq.add (rota23);
    seq.add (mvmt34);

    /* run the game to get kinetics over time */
    std::vector<Kinetic> kinetics = Get_Kinetics_from_Sequence (seq, dt, kin1);

    /* display the graph */
    Display (kinetics, width, height, mmToPxX, mmToPxY, pxOffsetX, pxOffsetY);

    return 0;
}


std::vector<Kinetic> Get_Kinetics_from_Sequence (Sequence seq, unsigned long dt, Kinetic beginKinetic) {
    std::vector<Kinetic> kinetics;

    unsigned long timer = 0;

    action_kind kind;
    Kinetic goal = beginKinetic;

    // add the first kinetic
    kinetics.push_back (goal);

    while (timer <= 100000) {
        // call the sequence
        seq.monitor (timer, dt, &kind, &goal);

        kinetics.push_back (goal);

        //Display (kinetics, width, height, mmToPxX, mmToPxY, pxOffsetX, pxOffsetY);

        timer += dt;
    }

    return kinetics;
}

void Display (std::vector<Kinetic> kinetics, const int width, const int height, float mmToPxX, float mmToPxY, float pxOffsetX, float pxOffsetY,  float Rpoint, float orient_line_sz) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Sequence Tester - Ensmasteel");
    window.setFramerateLimit(60);

    /* CREATE OBJECTS */
    // graph
    sf::VertexArray graph(sf::LinesStrip);

    //points
    std::vector<sf::CircleShape> points;
    sf::CircleShape point(Rpoint);
    point.setFillColor(sf::Color::Green);

    // orientation indicators
    std::vector<sf::VertexArray> orientations;

    sf::Vector2f position;
    for (const Kinetic& kin : kinetics) {
        position = sf::Vector2f (pxOffsetX + kin.getX () * mmToPxX, pxOffsetY + kin.getY () * mmToPxY);

        // graph
        graph.append (position);

        // point
        point.setPosition(position - sf::Vector2f (Rpoint, Rpoint));
        points.push_back (point);

        // orientation indicator
        sf::VertexArray line(sf::Lines, 2);
        line.append (sf::Vertex(position, sf::Color::Red));
        line.append (sf::Vertex(
            position
            + sf::Vector2f (orient_line_sz * cos (kin.getTheta ()), orient_line_sz * sin (kin.getTheta ()))
            , sf::Color::Red
        ));
        orientations.push_back (line);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // graph
        window.draw(graph);

        // points
        for (const sf::CircleShape& point : points) {
            window.draw(point);
        }

        // orientation indicators
        for (const sf::VertexArray& line : orientations) {
            window.draw(line);
        }

        window.display();
    }
}