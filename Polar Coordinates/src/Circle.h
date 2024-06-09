#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

class Circle {

public:
    Vector2 origin;
    Vector2 circle;
    int radius = 50;
    float angle = 0;

    Circle() {
        origin.x = 0;
        origin.y = 0;
    }

    void render() {
        renderWithLines();
    }

    void renderWithLines() {
        int x = radius*cos(0);
        int y = radius*sin(0);
        for(float i=0.1; i<2*PI; i+=0.5) {
            circle.x = radius*cos(i);
            circle.y = radius*sin(i);
            CV::line(x, y, circle.x, circle.y);
            x = circle.x;
            y = circle.y;
        }

        CV::line(x, y, radius*cos(0), radius*sin(0));
    }

    void renderWithPoints() {
        for(float i=0; i<2*PI; i+=0.1) {
            circle.x = radius*cos(i);
            circle.y = radius*sin(i);
            CV::point(circle);
        }
    }

};


#endif // CIRCLE_H_INCLUDED
