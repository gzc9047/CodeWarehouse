#include <sstream>
#include <string>
#include <vector>

struct Telltale
{
    int doNotTellTheTruth(int, std::vector<int> a, std::vector<std::string> parties) {
        unsigned long long truth_bit = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            truth_bit |= 1 << a[i];
        }
        std::vector<unsigned long long> parties_bit(parties.size(), 0);
        for (size_t i = 0; i < parties.size(); ++i) {
            std::istringstream iss(parties[i]);
            int people = 0;
            while (iss >> people) {
                parties_bit[i] |= 1 << people;
            }
        }
        unsigned long long old_truth_bit;
        int result;
        do {
            old_truth_bit = truth_bit;
            result = 0;
            for (size_t i = 0; i < parties_bit.size(); ++i) {
                if (truth_bit & parties_bit[i]) {
                    truth_bit |= parties_bit[i];
                } else {
                    ++result;
                }
            }
        } while (old_truth_bit != truth_bit);
        return result;
    }
};
