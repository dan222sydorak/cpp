#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

const double eps = 1e-10;

class Poly {
public:
    void set_interval(double left, double right) {
        left_interval = left;
        right_interval = right;
    }
    bool is_interval(const double &x) {
        return (x >= left_interval) && (right_interval >= x);
    }

    virtual double find_root() = 0;
    virtual double find_value(const double &x) = 0;
    virtual void input(std::istream &istream) = 0;
    virtual void output() = 0;

protected:
    double left_interval, right_interval;
};

// linear and cubic
class CoefPoly : protected Poly {
public:
    CoefPoly(const size_t &size) : m_size(size) {
        coef.resize(size);
    }

    double& operator[](const int &pos) {
        return coef[pos];
    }

    double find_value(const double &x) override {
        double res = 0;
        double tmp = 1;
        for(int i = 0; i < this->m_size; i++) {
            res = res + coef[i] * tmp;
            tmp *= x;
        }

        return res;
    }

    CoefPoly derivative() const {
        if(m_size <= 1) return CoefPoly(1);

        CoefPoly res(m_size - 1);

        for(int i = 1; i < this->m_size; i++) {
            res[i-1] = i * coef[i];
        }

        return res;
    }

    double find_root() override {
        double ans = (right_interval + left_interval) / 2, x_0;

        do {
            x_0 = ans;
            double tmp = this->derivative().find_value(x_0);
            ans = x_0 - this->find_value(x_0)/tmp;
        } while(std::fabs(ans - x_0) >= eps && is_interval(ans));

        return ans;
    }

    void input(std::istream &istream) override {
        //std::cout << "Enter amount of coefs: ";
        istream >> m_size;
        coef.resize(m_size);

        //std::cout << "Enter coefs with spaces: ";
        for(int i = 0; i < m_size; i++) {
            istream >> coef[i];
        }
    }

    void output() override {
        std::cout << "CoefPoly: ";
        for(int i = 0; i < m_size; i++) {
            std::cout << coef[i] << " ";
        }
    }

private:
    size_t m_size;
    std::vector<double> coef;
};

// f(x) = k * sin(alpha * x) + b
class SinusPoly : public Poly {
public:
    SinusPoly() = default;

    SinusPoly(const double &k_, const double &b_, const double &alpha_) :
    k(k_), b(b_), alpha(alpha_) { }

    double find_value(const double &x) override {
        return k * sin(alpha * x) + b;
    }


    double find_root() override {
        double left = left_interval, right = right_interval;
        double ans = (right + left) / 2, x_0 = left;

        int cycle = 0;
        do {
            if(std::fabs(find_value(x_0)) > std::fabs(find_value(ans))) {
                right = ans;
            } else {
                left = ans;
            }
            x_0 = ans;
            ans = (right + left) / 2;
            cycle++;
        } while(std::fabs(find_value(ans)) >= eps && is_interval(ans) && cycle < 20);

        return ans;
    }

    void input(std::istream &istream) override {
        //std::cout << "Enter coefs (k, b, alpha) with spaces: ";
        istream >> k >> b >> alpha;
    }

    void output() override {
        std::cout << "SinusPoly: ";
        std::cout << k << "*sin(" << alpha << "*x) + " << b;
    }

private:
    double k, b, alpha;
};

// f(x) = k * exp(alpha * x) + b
class ExpPoly : public Poly {
public:
    ExpPoly() = default;

    ExpPoly(const double &k_, const double &b_, const double &alpha_) :
            k(k_), b(b_), alpha(alpha_) { }

    double find_value(const double &x) override {
        return k * exp(alpha * x) + b;
    }

    double find_root() override {
        double left = left_interval, right = right_interval;
        double ans = (right + left) / 2, x_0 = right;

        int cycle = 0;
        do {
            if(std::fabs(find_value(x_0)) > std::fabs(find_value(ans))) {
                right = ans;
            } else {
                left = ans;
            }
            x_0 = ans;
            ans = (right + left) / 2;
            cycle++;
        } while(std::fabs(find_value(ans)) >= eps && is_interval(ans) && cycle < 20);

        return ans;
    }

    void input(std::istream &istream) override {
        //std::cout << "Enter coefs (k, b, alpha) with spaces: ";
        istream >> k >> b >> alpha;
    }

    void output() override {
        std::cout << "ExpPoly: ";
        std::cout << k << "*e^(" << alpha << "*x) + " << b;
    }

private:
    double k, b, alpha;
};

int main() {
//    int N;
//    std::cout << "How much polies: ";
//    std::cin >> N;
//
//    std::vector<Poly*> polies(N);
//    for(auto p : polies) p->input();

    std::stringstream ss;

    std::vector<Poly*> polies(4);
    ss.str("2\n-3 2");
    polies[0] = (Poly*) new CoefPoly(2);
    polies[0]->input(ss);

    ss.clear();
    ss.str("3\n-4.5 8 11");
    polies[1] = (Poly*) new CoefPoly(3);
    polies[1]->input(ss);

    ss.clear();
    ss.str("2 3 0.45");
    polies[2] = (Poly*) new SinusPoly();
    polies[2]->input(ss);

    ss.clear();
    ss.str("2 3 0.45");
    polies[3] = (Poly*) new ExpPoly();
    polies[3]->input(ss);

    double left = -1, right = 1;
    double max_res = left, sum = 0;
    int got_root = 0;
    for(auto p : polies) {
        p->set_interval(left, right);
        double res = p->find_root();
        if(fabs(p->find_value(res)) < eps) {
            if(res > max_res) {
                max_res = res;
            }
            sum += res;
            got_root++;
        } else {
            p->output();
            std::cout << std::endl;
        }
    }

    std::cout << "Max root: " << max_res << std::endl;
    std::cout << "Sum of roots: " << sum << std::endl;
    std::cout << "All polies have roots: " << (polies.size() == got_root) << std::endl;

    return 0;
}
