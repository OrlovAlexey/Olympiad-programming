#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;
using std::ostream;
using std::istream;

class BigInteger{
private:
    static const int base = 10000;
    vector<int> num;
    bool is_positive = true;// is_positive
    //так sign понятнее
public:
    BigInteger() {
        num.clear();
        num.push_back(0);
        is_positive = true;
    }

    BigInteger(string s) {
        if (s.length() == 0) {
            num.clear(); // int не должен быть пустым, даже в таких условиях, 0 нужно добавить
            num.push_back(0);
            is_positive = true;
        } else {
            if (s[0] == '-') {
                is_positive = false;
                s = s.substr(1);
            } else {
                is_positive = true;
            }
            for (long long i = s.length(); i > 0; i -= 4) {
                if (i < 4)
                    num.push_back(atoi(s.substr(0, i).c_str()));
                else
                    num.push_back(atoi(s.substr(i - 4, 4).c_str()));
            }
        }
        this->clearzeros();
    }

    BigInteger(int x) {
        if (x < 0) {
            x = -x;
            is_positive = false;
        }
        if (x == 0) {
            num.push_back(x);
        }

        while (x > 0) {
            num.push_back(x % base);
            x /= base;
        }

        this->clearzeros();
    }

    BigInteger operator- () const {
        BigInteger copy = *this;
        copy.is_positive = !copy.is_positive;
        return copy;
    }
    BigInteger& operator+= (const BigInteger& b) {
        if (!this->is_positive) {
            if(!b.is_positive) {
                int over_digit = 0;
                size_t n1 = num.size();
                size_t n2 = b.num.size();
                for (size_t i = 0; i < max(n1, n2); ++i) {
                    if (n1 <= i && i < n2) {
                        num.push_back(0);
                    }// выравнивает число, к которому прибавляем

                    int copy = num[i];
                    if (n2 <= i && i < n1) {
                        num[i] = (num[i] + over_digit) % base;
                        over_digit = (copy + over_digit) / base;
                    } else {
                        num[i] = (num[i] + b.num[i] + over_digit) % base;
                        over_digit = (copy + b.num[i] + over_digit) / base;
                    }// прибавление

                    if (i == max(n1, n2) - 1 && over_digit != 0) {
                        num.push_back(over_digit);
                    }// конечный разряд
                }
                return *this;
            }
            else {
                return (this->changessign() -= b).changessign();
            }
        }// проверка на знаки
        else if (!b.is_positive) {
            //*this -= (-b);// И снова, копирование запрещено. Можно сделать sing=!is_positive, а потом *this -= b, в последствии изменив знак ещё раз (если останется отрицательный,
            // значит должен быть положительный и наоборот)
            is_positive = !is_positive;// поправил
            *this -= b;
            is_positive = !is_positive;
            return *this;
        }
        else {
            int over_digit = 0;
            size_t n1 = num.size();
            size_t n2 = b.num.size();
            for (size_t i = 0; i < max(n1, n2); ++i) {
                if (n1 <= i && i < n2) {
                    num.push_back(0);
                }// выравнивает число, к которому прибавляем

                int copy = num[i];
                if (n2 <= i && i < n1) {
                    num[i] = (num[i] + over_digit) % base;
                    over_digit = (copy + over_digit) / base;
                }
                else {
                    num[i] = (num[i] + b.num[i] + over_digit) % base;
                    over_digit = (copy + b.num[i] + over_digit) / base;
                }// прибавление

                if (i == max(n1, n2) - 1 && over_digit != 0) {
                    num.push_back(over_digit);
                }// конечный разряд
            }
            return *this;
        }
    }
    BigInteger& operator-= (const BigInteger& b) {
        if (!this->is_positive) {
            if(!b.is_positive) {
                if (*this > b) {
                    BigInteger temp = *this;
                    *this = b;
                    return (*this -= temp).changessign();
                }
                else {
                    bool over_digit = 0;
                    size_t n1 = num.size();
                    size_t n2 = b.num.size();
                    for (size_t i = 0; i < max(n1, n2); ++i) {
                        if (i < n2) {
                            num[i] -= static_cast<int>(over_digit) + b.num[i];
                        }
                        else {
                            num[i] -= static_cast<int>(over_digit);
                        }// уменьшение разряда

                        if (num[i] < 0) {
                            over_digit = true;
                            num[i] += base;
                        }
                        else {
                            over_digit = false;
                        }// проверка если разряд оказался отрицательным, прибавление к нему 10000 в этом случае®®
                    }
                    this->clearzeros();
                    return *this;
                }
            }
            else {
                return (this->changessign() += b).changessign();
            }
        }
        else if(!b.is_positive) {
            is_positive = !is_positive;
            *this += b;// И здесь так же
            is_positive = !is_positive;
            return *this;
        }
        else {
            if (*this < b) {
                BigInteger temp = *this;
                *this = b;
                return (*this -= temp).changessign();
            }
            else {
                bool over_digit = 0;
                size_t n1 = num.size();
                size_t n2 = b.num.size();
                for (size_t i = 0; i < max(n1, n2); ++i) {
                    if (i < n2) {
                        num[i] -= static_cast<int>(over_digit) + b.num[i];
                    }
                    else {
                        num[i] -= static_cast<int>(over_digit);
                    }// уменьшение разряда

                    if (num[i] < 0) {
                        over_digit = true;
                        num[i] += base;
                    }
                    else {
                        over_digit = false;
                    }// проверка если разряд оказался отрицательным, прибавление к нему 10000 в этом случае®®
                }
                this->clearzeros();
                return *this;
            }
        }
    }
    bool operator== (const BigInteger& b) const {
        if (b.num.size() != num.size()) return false;
        int sz = num.size();
        for (int i = 0; i < sz; ++i) {
            if (num[i] != b.num[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!= (const BigInteger& b) const {
        return !(*this == b);
    }
    bool operator<= (const BigInteger& b) const {
        return ((*this < b) || (*this == b));
    }
    bool operator>= (const BigInteger& b) const {
        return ((*this > b) || (*this == b));
    }
    BigInteger& operator++ () {
        *this += 1;
        return *this;
    }
    BigInteger operator++ (int) {
        BigInteger copy = *this;
        ++(*this);
        return copy;
    }
    BigInteger& operator-- () {
        *this -= 1;
        return *this;
    }
    BigInteger operator-- (int) {
        BigInteger copy = *this;
        --(*this);
        return copy;
    }
    BigInteger& operator*= (const BigInteger& b) {
        if ((is_positive && b.is_positive) || (!is_positive && !b.is_positive)) {
            is_positive = true;
        }
        else {
            is_positive = false;
        } // правильный знак

        BigInteger copy = *this;
        num.clear();
        num.resize(copy.num.size() + b.num.size() + 1);

        for(size_t i = 0; i < copy.num.size(); ++i){
            long long over_digit = 0;
            for (size_t j = 0; j < b.num.size() || over_digit != 0; ++j){
                long long result;
                if (j < b.num.size()) {
                    result = num[i+j] + copy.num[i] * b.num[j] + over_digit;
                }// умножение каждого разряда на каждый разряд
                else {
                    result = over_digit;
                }
                over_digit = result / base; // перенос разряда
                num[i+j] = result % base;
            }
        }
        clearzeros();
        return *this;
    }
    BigInteger& operator/= (const BigInteger& b) {
        if (b == 0) {
//            cout << "Divided by zero" << '\n';
            return *this;
        }//проверка на деление на ноль
        if (b.num.size() > num.size()) {
            *this = 0;
            is_positive = true;
            return *this;
        }
        if ((is_positive && b.is_positive) || (!is_positive && !b.is_positive)) {
            is_positive = true;
        }
        else {
            is_positive = false;
        }//проверка на знак
        BigInteger copy = *this;
        num.clear();
        BigInteger remainder = 0;
        remainder.is_positive = true;
        num.resize(copy.num.size());

        for (int i = copy.num.size() - 1; i >= 0; --i) {
            remainder.pwr_4();
            remainder.num[0] = copy.num[i];
            remainder.clearzeros();
            int find = 0;
            int left = 0;
            int right = base;
            while (left <= right) {
                int middle = (left + right) / 2;
                BigInteger temp = (b * middle);
                temp.is_positive = true;
                if (temp <= remainder) {
                    find = middle;
                    left = middle + 1;
                }
                else {
                    right = middle - 1;
                } // ищем число меньше или равно частичного остатка
            }
            num[i] = find % base;
            remainder -= (b >= 0 ? (b * (find)) : -(b * (find)));
        }// деление столбиком
        clearzeros();
        return *this;
    }
    BigInteger& operator%= (const BigInteger& b) {
        BigInteger copy = *this;
        num.clear();
        BigInteger remainder = 0;
        remainder.is_positive = true;
        num.resize(copy.num.size());

        for (int i = copy.num.size() - 1; i >= 0; --i) {
            remainder.pwr_4();
            remainder.num[0] = copy.num[i];
            remainder.clearzeros();
            int find = 0;
            int left = 0;
            int right = base;
            while (left <= right) {
                int middle = (left + right) / 2;
                BigInteger temp = (b * middle);
                temp.is_positive = true;
                if (temp <= remainder) {
                    find = middle;
                    left = middle + 1;
                }
                else {
                    right = middle - 1;
                } // ищем число меньше или равно частичного остатка
            }
            num[i] = find % base;
            remainder -= (b >= 0 ? (b * (find)) : -(b * (find)));
        }
        *this = remainder;
        clearzeros();
        return *this;
    }

    string toString() const {
        string s = "";
        if (!is_positive) {
            s += "-";
        }
        if (num.size() == 1 && num[0]== 0) {
            s.clear();
        }
        if (num.size() != 0) {
            s += std::to_string(num[num.size() - 1]);
        }
        if (num.size() > 1) {
            for (int i = num.size() - 2; i >= 0; --i) {
                if (num[i] < 10) {
                    s += "000";
                } else if (num[i] < 100) {
                    s += "00";
                } else if (num[i] < 1000) {
                    s += "0";
                }
                s += std::to_string(num[i]);
            }
        }
        if (num.size() == 0){
            s.clear();
        }
        return s;
    }
    explicit operator bool() {
        return (*this != (BigInteger)0);
    }
    //    explicit operator int() {}

    // Эти операторы при правильном написании не должны быть friend
    // у меня /=, %= написаны через -, *, /
    // но это можно пофиксить
    // но в <, >, >> используются знаки и не только
    friend bool operator< (const BigInteger&, const BigInteger&);
    friend bool operator> (const BigInteger&, const BigInteger&);
    friend istream& operator>> (istream&, BigInteger&);
    friend string asDecimal_helper(const BigInteger&, const BigInteger&, long long);
private:
    BigInteger& changessign() {
        is_positive = !is_positive;
        return *this;
    }// унарный минус без создания копии

    void clearzeros() {
        while (num.size() > 1 && num.back() == 0) {
            num.pop_back();
        }
        if (num.size() == 1 && num[0] == 0) {
            is_positive = true;
        }
    }// удаляет лишние нули в начале числа

    void pwr_4() {
        if (num.size() == 0) {
            num.push_back(0);
        }
        num.push_back(num[num.size()-1]);
        for (int j = num.size() - 2; j > 0; --j) {
            num[j] = num[j-1];
        }
        num[0] = 0;
    }// домножение на base bigInt'a(сдвиг влево)

    BigInteger operator* (int a) const {// добавил умножение bigint на int для /=
        BigInteger copy = *this;
        copy.num.clear();
        copy.num.resize(num.size() + 1);
        int over_digit = 0;
        for (int i = 0; i < (int)num.size() || over_digit != 0; ++i) {
            int temp;
            if (i < (int)num.size()) {
                temp = num[i] * a + over_digit;
            }
            else {
                temp = over_digit;
            }
            over_digit = temp / base;
            copy.num[i] = temp % base;
        }
        copy.clearzeros();
        return copy;
    }
public:
    bool sgn() const {// То же самое делает i<0
        return is_positive;//да, но это же быстрее
    } // возвращает знак

    BigInteger big_abs() const {
        BigInteger copy = *this;
        copy.is_positive = true;
        return copy;
    } // bigInteger модуль
};

istream& operator>> (istream& in, BigInteger& b) {
    string s;
    in >> s;//упростил
    b.num.clear();
    if (s.length() == 0) {
        b.is_positive = true;
    }
    else {
        if (s[0] == '-') {
            b.is_positive = false;
            s = s.substr(1);
        }
        else {
            b.is_positive = true;
        }
        for (long long i = s.length(); i > 0; i-=4) {
            if (i < 4) {
                b.num.push_back(std::stoi(s.substr(0, i)));
            }
            else {
                b.num.push_back(std::stoi(s.substr(i - 4, 4)));
            }
        }
    }
    b.clearzeros();
    return in;
}

ostream& operator<< (ostream& out, const BigInteger& b) {
    out << b.toString();
    return out;
}

bool operator< (const BigInteger& a, const BigInteger& b) {
    if (!a.is_positive && b.is_positive) {
        return true;
    }
    if (a.is_positive && !b.is_positive) {
        return false;
    }
    if (a.is_positive && b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() < b.num.size();
    }
    if (!a.is_positive && !b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() > b.num.size();
    }
    for (int i = a.num.size() - 1; i >= 0; --i) {
        if ((a.num[i] != b.num[i]) && (a.is_positive && b.is_positive)) {
            return a.num[i] < b.num[i];
        }
        else if ((a.num[i] != b.num[i]) && (!a.is_positive && !b.is_positive)) {
            return a.num[i] > b.num[i];
        }
    }
    return false;
}

bool operator> (const BigInteger& a, const BigInteger& b) {
    if (a.is_positive && !b.is_positive) {
        return true;
    }
    if (!a.is_positive && b.is_positive) {
        return false;
    }
    if (a.is_positive && b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() > b.num.size();
    }
    if (!a.is_positive && !b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() < b.num.size();
    }
    for (int i = a.num.size() - 1; i >= 0; --i) {
        if ((a.num[i] != b.num[i]) && (a.is_positive && b.is_positive)) {
            return a.num[i] > b.num[i];
        } else if ((a.num[i] != b.num[i]) && (!a.is_positive && !b.is_positive)) {
            return a.num[i] < b.num[i];
        }
    }
    return false;
}

BigInteger operator+ (const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy += b;
    return copy;
}

BigInteger operator- (const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy -= b;
    return copy;
}

BigInteger operator* (const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy *= b;
    return copy;
}

BigInteger operator/ (const BigInteger& a, const BigInteger& b){
    BigInteger copy = a;
    copy /= b;
    return copy;
}

BigInteger operator% (const BigInteger& a, const BigInteger& b){
    BigInteger copy = a;
    copy %= b;
    return copy;
}

BigInteger gcd(const BigInteger& a, const BigInteger& b) {
    if (a == 1) {
        return 1;
    }
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

BigInteger bin_pow(const BigInteger& a, const BigInteger& degree) {
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 != 0) {
        return bin_pow(a, degree - 1) * a;
    }
    else {
        BigInteger b = bin_pow(a, degree / 2);
        return (b * b);
    }
}

int main() {
    ll k;
    cin >> k;
    vector<ll> a(k);
    for (ll i = 0; i < k; ++i) {
        cin >> a[i];
    }
//    vector<vector<ll>> stolbik1{{0}, {1}, {0}};
//    vector<vector<ll>> stolbik2{{1}, {1}, {1}};
//    vector<vector<ll>> dp{{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
//    matrix startp(stolbik1);
//    matrix startq(stolbik2);
//    matrix step(dp);
//    matrix final;
    BigInteger pwr = 1;
    for (ll i = 0; i < k; ++i) {
//        final = bin_pow(step, a[i]);
        pwr *= a[i];
    }
    if (pwr % 2 == 0) {

    }
    return 0;
}
