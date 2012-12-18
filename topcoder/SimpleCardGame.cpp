#include <vector>

struct SimpleCardGame
{
    int whoIsTheWinner(std::vector<int> points) {
        int result = -1;
        int max_point = -1;
        for (size_t i = 0; i < points.size(); ++i) {
            if (points[i] <= 21) {
                if (points[i] > max_point) {
                    result = i;
                } else if (points[i] == max_point) {
                    result = -1;
                }
            }
        }
        return result;
    }
};
