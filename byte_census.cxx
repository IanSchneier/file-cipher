// Global module fragment where #includes can happen
module;

#include <array>
#include <cstdint>
#include <string>
#include <iostream>

#define NUM_CHARS 256

export module byte_census;

export class ByteCensus
{
private:
    /* data */
    std::array<uint64_t, NUM_CHARS> m_arr;
    std::size_t m_cnt;
public:
    ByteCensus(std::string &str) : m_arr({0}), m_cnt(str.size()) {
        for (const uint8_t &c : str) {
            ++m_arr[c];
        }
    }

    ByteCensus(std::string &&str) : m_arr({0}), m_cnt(str.size()) {
        for (const uint8_t &c : str) {
            ++m_arr[c];
        }
    }

    ~ByteCensus() {}


    bool embeds_into (const ByteCensus &rhs) {
        // Check if ByteCensus of the thing to be embedded into is bigger than what's being embedded
        if (rhs.m_cnt < m_cnt) {
            return false;
        }

        for (size_t i = 0; i < m_arr.size(); ++i) {
            // Ignore special case where arrray element is zero for both things being compared
            if (m_arr[i] == 0 && rhs.m_arr[i] == 0) {
                continue;
            }

            if (m_arr[i] >= rhs.m_arr[i]) {
                return false;
            }
        }

        return true;
    }

    friend std::ostream &operator<< (std::ostream &os, const ByteCensus &bs) {
        os << "Total: " << bs.m_cnt << "\n";
        for (size_t i = 0; i < bs.m_arr.size(); ++i) {
            // Only print non-zero counts
            if (bs.m_arr[i]) {
                os << i << ": " << bs.m_arr[i] << "\n";
            }
        }

        return os;
    }

    int operator<=>(const ByteCensus &rhs) {
        return m_cnt - rhs.m_cnt;
    }

};