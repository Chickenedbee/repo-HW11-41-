#include <iostream>
#include<math.h>
#include <stack> 
#include<vector>
using namespace std;

class Term {
private:
    float coef; // 系数
    int exp; // 指数

public:
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}

    float getCoef() const { return coef; }
    int getExp() const { return exp; }

    void setCoef(float c) { coef = c; }
    void setExp(int e) { exp = e; }
};

class Polynomial {
private:
    vector<Term> terms; // 存储多項式

public:
    void addTerm(const Term& term) {
        terms.push_back(term);
    }

    // 重载 >> 操作符输入一个多項式
    friend istream& operator>>(istream& in, Polynomial& poly) {
        int numTerms;
        cout << "输入項的數量: ";
        in >> numTerms;

        for (int i = 0; i < numTerms; i++) {
            float coef;
            int exp;
            cout << "输入第 " << i + 1 << " 項的次方和指數: ";
            in >> coef >> exp;
            poly.addTerm(Term(coef, exp));
        }

        return in;
    }

    // 重載入 << 操作输出一个多項式
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        for (size_t i = 0; i < poly.terms.size(); i++) {
            if (i != 0 && poly.terms[i].getCoef() >= 0) {
                out << " + ";
            }
            out << poly.terms[i].getCoef() << "x^" << poly.terms[i].getExp();
        }
        return out;
    }
};

int main() {
    Polynomial poly;

    cin >> poly;

    cout << "多項式: " << poly << endl;

    return 0;
}
