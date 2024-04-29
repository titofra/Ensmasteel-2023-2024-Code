#include "sequence.hpp"
#include "action.hpp"
#include "action_functions.hpp"
#include <SFML/Graphics.hpp>
#include <nanosvg.h>
#include <nanosvgrast.h>

std::vector<Kinetic> Get_Kinetics_from_Sequence (Sequence seq, unsigned long dt, Kinetic beginKinetic);
void Display (std::vector<Kinetic> kinetics, float scale, float pxOffsetX, float pxOffsetY, unsigned long dt, float Rpoint = 4.0f, float orient_line_sz = 20.0f);
void BuildSequence (Sequence* seq);

int main (void) {
    const int pxOffsetX = 10;
    const int pxOffsetY = 10;
    const float scale = 0.13f;
    const unsigned long dt = 100;    // here dt has ne effect on the trajectory, however it has an effect in the number of sequence's call aka the number of dots on the graph

    /* create the sequence */
    Sequence seq;
    BuildSequence (&seq);

    /* run the game to get kinetics over time */
    Kinetic beginKinetic = Kinetic (2000.0f, 1000.0f, 3.14f / 2.0f);
    std::vector<Kinetic> kinetics = Get_Kinetics_from_Sequence (seq, dt, beginKinetic);

    /* display the graph */
    Display (kinetics, scale, pxOffsetX, pxOffsetY, dt);

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

void Display (std::vector<Kinetic> kinetics, float scale, float pxOffsetX, float pxOffsetY, unsigned long dt, float Rpoint, float orient_line_sz) {
    /* BACKGROUND */
    NSVGimage* bkg_svg = nsvgParseFromFile ("resources/table.svg", "px", 96);
    struct NSVGrasterizer* bkg_rast = nsvgCreateRasterizer ();
    const unsigned int width = (unsigned int) bkg_svg->width;
    const unsigned int height = (unsigned int) bkg_svg->height;
    unsigned char* bkg_img = (unsigned char*) malloc (width * height * 4);
    nsvgRasterize (bkg_rast, bkg_svg, 0, 0, 1, bkg_img, width, height, width * 4);
    nsvgDeleteRasterizer (bkg_rast);
    nsvgDelete (bkg_svg);
    sf::Texture backgroundTexture;
    backgroundTexture.create (width, height);
    backgroundTexture.update (reinterpret_cast<const sf::Uint8*> (bkg_img), width, height, 0, 0);
    sf::Sprite background;
    background.setTexture (backgroundTexture);
    background.setPosition (pxOffsetX, pxOffsetY);
    background.setScale (scale, scale);

    /* WINDOWS */
    sf::RenderWindow window (
        sf::VideoMode (
            (unsigned int) background.getGlobalBounds ().width + 2 * (unsigned int) pxOffsetX,
            (unsigned int) background.getGlobalBounds ().height + 2 * (unsigned int) pxOffsetY
        ),
        "Sequence Tester - Ensmasteel",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit ((unsigned int) (1000 / dt));

    /* CREATE OBJECTS */
    // graph
    sf::VertexArray graph (sf::LinesStrip);

    //points
    std::vector<sf::CircleShape> points;
    sf::CircleShape point (Rpoint);
    point.setFillColor (sf::Color::White);

    // orientation indicators
    std::vector<sf::VertexArray> orientations;

    const float mmToPxX = (float) (background.getGlobalBounds ().width - 2.0f * pxOffsetY) / 3000.0f;
    const float mmToPxY = (float) (background.getGlobalBounds ().height - 2.0f * pxOffsetX) / 1500.0f;

    sf::Vector2f position;
    for (const Kinetic& kin : kinetics) {
        position = sf::Vector2f (pxOffsetX + kin.getX () * mmToPxX, pxOffsetY + kin.getY () * mmToPxY);

        // graph
        graph.append (sf::Vertex (position, sf::Color::Black));

        // point
        point.setPosition (position - sf::Vector2f (Rpoint, Rpoint));
        points.push_back (point);

        // orientation indicator
        sf::VertexArray line (sf::Lines, 2);
        line.append (sf::Vertex (position, sf::Color::Blue));
        line.append (sf::Vertex (
            position
            + sf::Vector2f (orient_line_sz * cos (kin.getTheta ()), orient_line_sz * sin (kin.getTheta ()))
            , sf::Color::Blue
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

        window.clear();

        // background
        window.draw (background);

        // graph
        sf::VertexArray graphToDraw (sf::LinesStrip);
        for (int i = 0; i < frame; i++) {
            graphToDraw.append (graph [i]);
        } 
        window.draw (graphToDraw);

        // points
        for (int i = 0; i < frame; i++) {
            window.draw (points [i]);
        }

        // orientation indicators
        for (int i = 0; i < frame; i++) {
            window.draw (orientations [i]);
        }

        window.display ();

        frame ++;
        if (frame > (int) (100000 / dt)) frame = (int) (100000 / dt);
    }
}

void BuildSequence (Sequence* seq) {
    // kinetics
    VectorOriented P1 (2000.0f, 1000.0f, 3.14f / 2.0f);
    VectorOriented P2 (1650.0f, 1350.0f, 3.14f);
    VectorOriented P3 (1300.0f, 1000.0f, -3.14f / 2.0f);
    VectorOriented P4 (1650.0f, 650.0f, 0.0f);

    const float delta_curve = 200.0f;

    // actions
    Action mvmt12 (
        MOVEMENT_ACT,
        bezier_auto ({P1, P2}, delta_curve),
        trapeze (0, 500, 1500, 1500, 0.7f, 0.7f),
        1500
    );
    Action mvmt23 (
        MOVEMENT_ACT,
        bezier_auto ({P2, P3}, delta_curve),
        trapeze (1500, 1500, 2500, 2500, 0.5f, 0.8f),
        2500
    );
    Action mvmt34 (
        MOVEMENT_ACT,
        bezier_auto ({P3, P4}, delta_curve),
        trapeze (2500, 2500, 3500, 3500, 0.5f, 0.8f),
        3500
    );
    Action mvmt41 (
        MOVEMENT_ACT,
        bezier_auto ({P4, P1}, delta_curve),
        trapeze (3500, 3500, 4500, 5000, 0.5f, 0.8f),
        5000
    );

    // sequence
    seq->add (mvmt12);
    seq->add (mvmt23);
    seq->add (mvmt34);
    seq->add (mvmt41);
}
