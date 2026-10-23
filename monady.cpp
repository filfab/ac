#include <iostream>
#include <string>
#include <functional>


struct WriterInt {
    int value;
    std::string log;
};

WriterInt unit(int x) { return {x, ""}; }

WriterInt tell(const std::string& message) { return {0, message}; }

WriterInt bind(const WriterInt& w, std::function<WriterInt(int)> f) {
    WriterInt result = f(w.value);
    return {result.value, w.log + result.log};
}

WriterInt operator|(const WriterInt& w, std::function<WriterInt(int)> f) { return bind(w, f); }


auto add(int k) {
    return [k](int x) -> WriterInt {
        int res = x + k;
        std::string entry = " -> (" + std::to_string(x) + " + " +
        std::to_string(k) + " = " + std::to_string(res) + ")";
        return {res, entry}; 
    }; 
}

auto multiply(int k) {
    return [k](int x) -> WriterInt {
        int res = x * k;
        std::string entry = " -> (" + std::to_string(x) + " * " + 
        std::to_string(k) + " = " + std::to_string(res) + ")";
        return {res, entry};
    };
}

auto square() {
    return [](int x) -> WriterInt {
        int res = x * x;
        std::string entry = " -> (" + std::to_string(x) + "^2 = " + std::to_string(res) + ")"; 
        return {res, entry};
    };
}

int main() {
    WriterInt start = {5, "5"};
    
    WriterInt result = start | add(2)
                             | multiply(3)
                             | square();
    
    std::cout << "wynik " << result.value << std::endl;
    std::cout << "slad " << result.log << std::endl;
    
    return 0;
}