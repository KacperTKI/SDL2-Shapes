#ifndef APPLICATION_H
#define APPLICATION_H

class Line2D;
class Screen;
class Star2D;

/**
 * @brief The Application class is storing the logic for the assignments from section 8 in static functions
 */
class Application {
public:
    /**
     * @brief Draw a line and rotate it counter clock-wise.
     * @param line The line which should be drawn and rotated.
     * @param screen The screen which draws the line.
     */
    static void CounterClockwiseLine(Line2D& line, Screen& screen, int dt);
    /**
     * @brief Draw a star and rotate it counter clock-wise.
     * @param star The star which should be drawn and rotated.
     * @param screen The screen which draws the star.
     */
    static void CounterClockwiseStar(Star2D& star, Screen& screen, int dt);
};

#endif
