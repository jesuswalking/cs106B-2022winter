#include "Plotter.h"
#include "Vector.h"
#include "strlib.h"
#include <iostream>
#include <string>
#include <cctype>
//using namespace std;

void runPlotterScript(std::istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    // initialize the pen.
    double currx = 0.0;
    double curry = 0.0;
    bool penDown = false;
    double width = 1.0;
    std::string color = "black";

    // preprocess the istream.
    for (std::string line; getline(input, line);) {
        Vector<std::string> tokens = stringSplit(line, " ");

        if (tokens.isEmpty()) continue;

        std::string command = toLowerCase(tokens[0]);

        if (command == "pendown") penDown = true;
        else if (command == "penup") penDown = false;
        else if (command == "pencolor") color = tokens[1];
        else if (command == "penwidth") width = stringToReal(tokens[1]);
        else if (command == "moveabs") {
            double newx = stringToReal(tokens[1]);
            double newy = stringToReal(tokens[2]);
            if (penDown) {
                PenStyle style = {width, color};
                drawLine(currx, curry, newx, newy, style);
            }
            currx = newx;
            curry = newy;
        } else if (command == "moverel") {
            double newx = currx + stringToReal(tokens[1]);
            double newy = curry + stringToReal(tokens[2]);
            if (penDown) {
                PenStyle style = {width, color};
                drawLine(currx, curry, newx, newy, style);
            }
            currx = newx;
            curry = newy;
        }
    }
}
