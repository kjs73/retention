#ifndef LATTICE_STRIP_SQUARE_2D_HPP_KJS
#define LATTICE_STRIP_SQUARE_2D_HPP_KJS

#include <cassert>
#include <utility>
#include <vector>

class lattice_strip_square_2d {
public:
    typedef unsigned int ord_t;
    lattice_strip_square_2d(const unsigned int Lxin, const unsigned int Lyin)
        : lx(Lxin),
          ly(Lyin),
          N(Lxin * Lyin),
          N2(2 * Lxin * Lyin),
          NB(2 * Lxin * Lyin),
          NBF(2 * Lxin * Lyin - Lyin - Lxin),
          L_2(Lxin * Lyin),
          TopConst(Lxin * Lyin - Lxin)
    {}
    unsigned int Lx() const { return lx; }
    unsigned int Ly() const { return ly; }
    unsigned int NumberSites() const { return N; }
    unsigned int NumberNeighbors() const { return 4; }
    bool left(const unsigned int ste) const { return (ste % lx == 0); }
    bool right(const unsigned int ste) const { return (((ste + 1) % lx) == 0); }
    bool bottom(const unsigned int ste) const { return ste < lx; }
    bool top(const unsigned int ste) const { return ste >= TopConst; }
    unsigned int neighbor(const unsigned int ste, const unsigned int dir) const
    {
        int tmp = ste;
        if (dir == 0) {
            tmp -= lx;
            if (bottom(ste)) tmp += N;
            return tmp;
        }
        else if (dir == 1) {
            tmp += 1;
            if (right(ste)) tmp -= lx;
            return tmp;
        }
        else if (dir == 2) {
            tmp += lx;
            if (top(ste)) tmp -= N;
            return tmp;
        }
        else if (dir == 3) {
            int tmp = static_cast<int>(ste) - 1;
            if (left(ste)) {
                tmp += lx;
            }
            return tmp;
        }
        else throw std::runtime_error("lattice: illegal index");
    }
    bool BulkConnection(const unsigned int ste, const unsigned int dir) const
    {
        if (dir == 0) {
            if (bottom(ste)) return false;
            else return true;
        }
        else if (dir == 1) {
            if (right(ste)) return false;
            else return true;
        }
        else if (dir == 2) {
            if (top(ste)) return false;
            else return true;
        }
        else{
            assert(dir == 3);
            if (left(ste)) return false;
            else return true;
        }
    }
    bool site_at_boundary(const unsigned int site) const
    {
        if (bottom(site)) return true;
        if (top(site)) return true;
        if (left(site)) return true;
        if (right(site)) return true;
        return false;
    }
private:
    const ord_t lx;
    const ord_t ly;
    const ord_t N;
    const ord_t N2;
    const ord_t NB;
    const ord_t NBF;
    const ord_t L_2;
    const ord_t TopConst;
};

#endif // #ifndef LATTICE_STRIP_SQUARE_2D_HPP_KJS

