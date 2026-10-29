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

auto fafafaf() {
    return [](int x) -> WriterInt {
        int res;
        std::string entry;
        if (x%2==0) {
            res = x/2;
            entry = " -> (" + std::to_string(x) + "/2 = " + std::to_string(res) + ")"; 
        } else {
            res = 3*x+1;
            entry = " -> (3*" + std::to_string(x) + "+1 = " + std::to_string(res) + ")"; 
        }
        
        return {res, entry};
    };
}


int main() {
    WriterInt start = unit(5);
    
    WriterInt result = start | fafafaf() | fafafaf();
    
    std::cout << "wynik " << result.value << std::endl;
    std::cout << "slad " << result.log << std::endl;
    
    return 0;
}