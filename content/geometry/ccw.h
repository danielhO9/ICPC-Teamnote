/**
 * Author: 
 * Date: 
 * License: 
 * Description: CCW
 * Status: stress-tested
 */

struct point {
    double x, y;
};

int ccw(point a, point b, point c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}