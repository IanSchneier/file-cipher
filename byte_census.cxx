// Global module fragment where #includes can happen
module;

#include <array>
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

template<typename T>
// Allow any c-style array where element type is convertible to uint8_t
concept byte_arr = requires(T t, size_t idx) {
    {t[idx]} -> std::convertible_to<uint8_t>;
};

template<typename T>
// Allow any container with a size attribute and same properties as byte_arr
concept byte_container = byte_arr<T> && requires(T t) {
    {t.size()} -> std::same_as<size_t>;
};

// Number of ASCII characters
#define NUM_CHARS 256

export module byte_census;

export class ByteCensus
{
private:
    /* data */
    std::array<uint64_t, NUM_CHARS> m_arr;
    std::size_t m_cnt;
public:
    ByteCensus() : m_arr({0}), m_cnt(0) {}

    ByteCensus(byte_container auto val) : ByteCensus() {
        digest(val);
    }

    ByteCensus(byte_arr auto val) : ByteCensus() {
        digest(std::string(val));
    }

    ~ByteCensus() {}

    void digest(byte_container auto v) {
        digest(v.data(), v.size());
    }

    void digest(byte_arr auto v, size_t len) {
        // Reject data (for now) if not empty
        if (m_cnt) {
            std::cout << "Byte Census already filled\n";
            return;
        }

        size_t i = 0;
        while (i < len) {
            ++m_arr[v[i++]];
        }

        // Update count
        m_cnt = i;
    }


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
};