#include <vector>
#include <iostream>
#include <cmath>

using namespace std;


class Term { // 在這裡表示多項式一個一個的數值
public:
    float coef;  // 前方係數
    int exp;     // 次方數

    Term(float c = 0.0f, int e = 0) : coef(c), exp(e) {}

    void Print(){ // 列出單個的數值
        if (exp == 0) {
            cout << coef;
        } else {
            cout << coef << "x^" << exp;
        }
    }
};

// 表示多項式
class Polynomial {
private:
    vector<Term> terms;  // 存储多項式項的向量

public:
    // 默認
    Polynomial() {}

    // 建構成多項式
    Polynomial(vector<Term>& ts) : terms(ts) {}

    // 多项式加法
    Polynomial Add(Polynomial& poly){
        vector<Term> result = terms;

        for (auto& term : poly.terms) {
            bool found = false;
            for (auto& resTerm : result) {
                if (resTerm.exp == term.exp) { // 找次方倍數是否一樣，做相加
                    resTerm.coef += term.coef;
                    found = true;
                    break;
                }
            }
            if (!found) { // result層沒找到 => poly的值是新的次方倍數，所以新增進去
                result.push_back(term);
            }
        }

        return Polynomial(result);
    }

    // 多項式乘法
    Polynomial Mult(Polynomial& poly){
        vector<Term> result;

        for (auto& term1 : terms) {
            for (auto& term2 : poly.terms) {
                bool found = false;
                Term newTerm(term1.coef * term2.coef, term1.exp + term2.exp);  // 宣告一個兩個相乘後的項量數值

                for (auto& resTerm : result) { // 找次方倍數是否一樣，做乘法後相加
                    if (resTerm.exp == newTerm.exp) {
                        resTerm.coef += newTerm.coef;
                        found = true;
                        break;
                    }
                }
                if (!found) { // 沒找到=新的次方倍數，所以新增進去
                    result.push_back(newTerm);
                }
            }
        }

        return Polynomial(result);
    }

    // 輸入x=多少後計算出答案
    float Eval(float x)   {
        float result = 0.0f;
        for (auto& term : terms) {
            result += term.coef * pow(x, term.exp);
        }
        return result;
    }

    // 寫出多項式
    void Print(){
        for (size_t i = 0; i < terms.size(); ++i) {
            if (i > 0 && terms[i].coef >= 0) {
                cout << "+";
            }
            terms[i].Print();
            cout <<" ";
        }
        cout << endl;
    }
};

int main() {
    vector<Term> terms1 = {Term(3, 0), Term(2, 1), Term(2, 2),Term(2, 3), Term(1, 4),Term(3, 5), Term(2, 6)};
    vector<Term> terms2 = {Term(3, 0), Term(2, 1), Term(2, 2),Term(2, 3), Term(1, 4),Term(3, 5), Term(2, 6)};

    Polynomial p1(terms1); //3 + 2x + 1x^2
    Polynomial p2(terms2); //4 + 2x

    Polynomial p3 = p1.Add(p2);
    Polynomial p4 = p1.Mult(p2);

    p1.Print(); // 输出： 3 2x^1 +1x^2
    p2.Print(); // 输出： 4 2x^1
    p3.Print(); // 输出： 7 4x^1 +1x^2
    p4.Print(); // 输出： 12 14x^1 +8x^2 +2x^3

    cout << "p1 在 x = 2 的值：" << p1.Eval(2) << endl;

    return 0;
}
