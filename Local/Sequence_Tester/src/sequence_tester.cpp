#include "sequence.hpp"
#include "action.hpp"
#include "action_functions.hpp"
#include <SFML/Graphics.hpp>

std::vector<Kinetic> Get_Kinetics_from_Sequence (Sequence seq, unsigned long dt, Kinetic beginKinetic);
void Display (std::vector<Kinetic> kinetics, const int width, const int height, float mmToPxX, float mmToPxY, float pxOffsetX, float pxOffsetY, unsigned long dt, float Rpoint = 3.0f, float orient_line_sz = 20.0f);

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
    VectorOriented P1 (0.0f, 0.0f, 0.0f);    // pt1
    VectorOriented P2 (1000.0f, 0.0f, 0.0f); // pt2
    VectorOriented P3 (1000.0f, 0.0f, 0.0f); // pt3 (rotated, the theta is modified few lines further)
    VectorOriented P4 (200.0f, 800.0f, 0.0f);// pt4 (with the same rotation as we use a linear trajectory)
    const float theta34 = P3.angleWith (P4);
    P3.setTheta (theta34);
    P4.setTheta (theta34);
    VectorOriented P5 (900.0f, 1200.0f, 0.0f);// pt5
    VectorOriented P6 (2600.0f, 1400.0f, 0.0f);// pt6
    VectorOriented P7 (2200.0f, 800.0f, 0.0f);// pt7

    // actions
    Action mvmt12 (
        MOVEMENT_ACT,
        bezier ({P1, P2}),
        trapeze (0, 500, 1000, 1300, 0.7f, 0.7f),
        1300
    );
    Action rota23 (
        MOVEMENT_ACT,
        linear ({P2, P3}),
        linear (1300, 1700),
        1700
    );
    Action mvmt34 (
        MOVEMENT_ACT,
        bezier ({P3, P4}),
        trapeze (1700, 2500, 3300, 4000, 0.5f, 0.8f),
        4000
    );
    std::vector<VectorOriented> controlPoints45;
    controlPoints45.push_back (P4);
    controlPoints45.push_back (VectorOriented (10.0f, 900.0f, 0.0f));
    controlPoints45.push_back (VectorOriented (500.0f, 1300.0f, 0.0f));
    controlPoints45.push_back (VectorOriented (700.0f, 700.0f, 0.0f));
    controlPoints45.push_back (P5);
    std::vector<VectorOriented> controlPoints56;
    controlPoints56.push_back (P5);
    controlPoints56.push_back (VectorOriented (900.0f, 1200.0f, 0.0f));
    controlPoints56.push_back (VectorOriented (1000.0f, 1500.0f, 0.0f));
    controlPoints56.push_back (VectorOriented (1800.0f, 500.0f, 0.0f));
    controlPoints56.push_back (VectorOriented (2000.0f, 1500.0f, 0.0f));
    controlPoints56.push_back (P6);
    Action mvmt46 (
        MOVEMENT_ACT,
        combine (bezier (controlPoints45), bezier (controlPoints56), 0.5f),
        combine (linear (4000, 6000), trapeze (6000, 6000, 7000, 8000, 1.0f, 0.4f), 4000, 6000, 8000),
        8000
    );
    Action mvmt67 (
        MOVEMENT_ACT,
        bezier_auto ({P6, P7}, 300.0f),
        linear (8000, 10000),
        10000
    );

    // sequence
    Sequence seq;
    seq.add (mvmt12);
    seq.add (rota23);
    seq.add (mvmt34);
    seq.add (mvmt46);
    seq.add (mvmt67);

    /* run the game to get kinetics over time */
    Kinetic beginKinetic = Kinetic (0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    beginKinetic += P1;
    std::vector<Kinetic> kinetics = Get_Kinetics_from_Sequence (seq, dt, beginKinetic);

    /* display the graph */
    Display (kinetics, width, height, mmToPxX, mmToPxY, pxOffsetX, pxOffsetY, dt);

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

        timer += dt;
    }

    return kinetics;
}

void Display (std::vector<Kinetic> kinetics, const int width, const int height, float mmToPxX, float mmToPxY, float pxOffsetX, float pxOffsetY, unsigned long dt, float Rpoint, float orient_line_sz) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Sequence Tester - Ensmasteel");
    window.setFramerateLimit((unsigned int) (1000 / dt));

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

    int frame = 1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // graph
        sf::VertexArray graphToDraw(sf::LinesStrip);
        for (int i = 0; i < frame; i++) {
            graphToDraw.append (graph [i]);
        } 
        window.draw(graphToDraw);

        // points
        for (int i = 0; i < frame; i++) {
            window.draw(points [i]);
        }

        // orientation indicators
        for (int i = 0; i < frame; i++) {
            window.draw(orientations [i]);
        }

        window.display();

        frame ++;
        if (frame > (int) (100000 / dt)) frame = (int) (100000 / dt);
    }
}